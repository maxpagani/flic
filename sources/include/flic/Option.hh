/**
 * @file flic/Option.hh
 * @author Massimiliano Pagani
 * @date 2019-04-16
 */

#if !defined( FLIC_OPTION_HH )
#define FLIC_OPTION_HH

#include <stdexcept>

template<typename A>
class Option
{
    public:
        typedef A BaseType;

        explicit constexpr Option( A const& a ) noexcept( noexcept( A(a)));
        explicit constexpr Option( A&& a ) noexcept;
        constexpr Option();

        template<typename Fn> constexpr
        Option<std::invoke_result_t<Fn,A>> map( Fn f ) const;

        template<typename Fn> constexpr
        std::invoke_result_t<Fn,A> flatMap( Fn f ) const;

        [[nodiscard]] constexpr bool isDefined() const;
        [[nodiscard]] constexpr bool isEmpty() const;
        
        constexpr A const& get() const;
    private:
        bool m_isValid;
        char m_storage[sizeof(A)];

        constexpr A& ref();
        constexpr A const& constRef() const;
};

template<typename A,typename B> constexpr bool
operator==( Option<A> const& lhs, Option<B> const& rhs );

template<typename A,typename B> constexpr bool
operator!=( Option<A> const& lhs, Option<B> const& rhs );

// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// :::::::::::::::::::::::::::::::::::::::::::::::::::::::: implementation :::
// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


template<typename A>
constexpr inline bool Option<A>::isDefined() const
{
    return m_isValid;
}

template<typename A>
constexpr inline bool Option<A>::isEmpty() const
{
    return !m_isValid;
}

template<typename A,typename B> inline constexpr bool
operator==( Option<A> const& lhs, Option<B> const& rhs )
{
    return (lhs.isDefined() && rhs.isDefined() && lhs.get() == rhs.get()) ||
           (lhs.isEmpty() && rhs.isEmpty());
}

template<typename A,typename B> inline constexpr bool
operator!=( Option<A> const& lhs, Option<B> const& rhs )
{
    return !(lhs == rhs);
}

template<typename A>
constexpr inline A& Option<A>::ref()
{
    return *reinterpret_cast<A*>(m_storage);
}

template<typename A>
constexpr inline A const& Option<A>::constRef() const
{
    return *reinterpret_cast<A const*>(m_storage);
}

template<typename A> inline
Option<A> None()
{
    return Option<A>{};
}

template<typename A> inline
Option<A> Some( A const& a )
{
    return Option<A>{ a };
}

template<typename A> inline constexpr
Option<A>::Option( A const& a ) noexcept(noexcept( A(a))): 
           m_isValid{true}
{
    new( m_storage ) A{a};
}

template<typename A> inline constexpr
Option<A>::Option( A&& a ) noexcept :
           m_isValid{true}
{
    new( m_storage ) A{std::move(a)};
}

template<typename A> inline constexpr
Option<A>::Option() : m_isValid{false}
{}

template<typename A>
template<typename Fn> inline constexpr
Option<std::invoke_result_t<Fn,A>>
Option<A>::map( Fn f ) const
{
    typedef std::invoke_result_t<Fn,A> B;
    return m_isValid ? Some<B>( f( constRef() ) ) : None<B>();
}

template<typename A>
template<typename Fn>
std::invoke_result_t<Fn,A> inline constexpr
Option<A>::flatMap( Fn f ) const
{
    typedef typename std::invoke_result_t<Fn,A>::BaseType B;
    return m_isValid ? f( constRef() ) : None<B>();
}

template<typename A> inline constexpr A const&
Option<A>::get() const
{
    if( !m_isValid ) throw std::invalid_argument{"invalid option get"};
    return constRef();
}

#endif