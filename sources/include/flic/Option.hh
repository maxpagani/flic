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
        explicit Option( A );
        Option();

        template<typename Fn>
        Option<std::invoke_result_t<Fn,A>> map( Fn f ) const;


        bool isDefined() const;
        bool isEmpty() const;
        
        A const& get() const;
    private:
        bool m_isValid;
        char m_storage[sizeof(A)];

        constexpr A& ref();
        constexpr A const& constRef() const;
};

template<typename A,typename B> bool
operator==( Option<A> const& lhs, Option<B> const& rhs );

template<typename A,typename B> bool
operator!=( Option<A> const& lhs, Option<B> const& rhs );

// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// :::::::::::::::::::::::::::::::::::::::::::::::::::::::: implementation :::
// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


template<typename A>
inline bool Option<A>::isDefined() const
{
    return m_isValid;
}

template<typename A>
inline bool Option<A>::isEmpty() const
{
    return !m_isValid;
}

template<typename A,typename B> bool
operator==( Option<A> const& lhs, Option<B> const& rhs )
{
    return (lhs.isDefined() && rhs.isDefined() && lhs.get() == rhs.get()) ||
           (lhs.isEmpty() && rhs.isEmpty());
}

template<typename A,typename B> inline bool
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

template<typename A>
Option<A> None()
{
    return Option<A>{};
}

template<typename A>
Option<A> Some( A a )
{
    return Option<A>{ a };
}

template<typename A>
Option<A>::Option( A a ) : 
           m_isValid{true}
{
    new( m_storage ) A{a};
}

template<typename A>
Option<A>::Option() : m_isValid{false}
{}

template<typename A>
template<typename Fn>
Option<std::invoke_result_t<Fn,A>>
Option<A>::map( Fn f ) const
{
    typedef std::invoke_result_t<Fn,A> B;
    return m_isValid ? Some<B>( f( constRef() ) ) : None<B>();
}

template<typename A> A const&
Option<A>::get() const
{
    if( !m_isValid ) throw std::invalid_argument{"invalid option get"};
    return constRef();
}

#endif