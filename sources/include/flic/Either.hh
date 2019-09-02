/**
 * @file Either.hh
 * @author MaxP (maxpag@gmail.com)
 * @brief Either base type
 * @version 0.1
 * @date 2019-07-21
 * 
 * @copyright Copyright (c) 2019
 */

#if !defined( FLIC_EITHER_HH )

#include <type_traits>
#include <variant>

/**
 * @brief Either class representing either a value or another.
 * 
 * Either type acts like a std::variant, providing a simple way to encapsulate
 * the result of an operation. Usually Left type holds an error, while the
 * Right type holds the result when the computation is successful.
 * 
 * @tparam L the Left type
 * @tparam R the Right type
 */
template<typename L,typename R>
class Either
{
    public:
        static Either Left( L const& left ) noexcept( noexcept( L(left) ));
        static Either Right( R const& right ) noexcept( noexcept( R(right)));
        static Either Left( L&& left ) noexcept;
        static Either Right( R&& right ) noexcept;

        R const& right() const;
        L const& left() const;

        template<typename FL,typename FR>
        std::invoke_result_t<FL,L> fold( FL fl, FR fr ) const;

        template<typename F>
        Either<L,std::invoke_result_t<F,R>> map( F f ) const;

        template<typename F>
        std::invoke_result_t<F,R> flatMap( F f ) const;

        bool isRight() const noexcept;
        bool isLeft() const noexcept;

        /**
         * @brief Gets the right value or a default value.
         * 
         * @param d the default value. Note that this value is returned to
         *          the caller, therefore this value lifetime has to be 
         *          adequate.
         * @return R const& 
         */
        R const& getOrElse( R const& d ) const noexcept;

        template<typename F>
        void foreach( F f ) const;

        Either<R,L> reverse() const noexcept;

        void swap( Either& other ) noexcept;
    private:
        explicit Either( std::variant<L,R>&& implementation );

        std::variant<L,R> m_variant;
};

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::: implementation :::
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

template<typename L,typename R>
Either<L,R>::Either( std::variant<L,R>&& implementation ) : m_variant{ implementation }
{}

template<typename L,typename R>
Either<L,R> 
Either<L,R>::Left( L const& left ) noexcept( noexcept( L(left)))
{
    return Either{ std::move( std::variant<L,R>{ std::in_place_index<0>, left } ) };
}

template<typename L,typename R>
Either<L,R> 
Either<L,R>::Right( R const& right ) noexcept( noexcept( R(right)))
{
    return Either{ std::move( std::variant<L,R>{ std::in_place_index<1>, left } ) };
}

template<typename L,typename R>
Either<L,R> 
Either<L,R>::Left( L&& left ) noexcept
{
    return Either{ std::move( std::variant<L,R>{ std::in_place_index<0>, std::move(left) } ) };
}

template<typename L,typename R>
Either<L,R> 
Either<L,R>::Right( R&& right ) noexcept
{
    return Either{ std::move( std::variant<L,R>{ std::in_place_index<1>, std::move(right) } ) };
}

template<typename L,typename R> inline
R const& Either<L,R>::right() const
{
    return std::get<1>(m_variant);
}

template<typename L,typename R> inline
L const& Either<L,R>::left() const
{
    return std::get<0>(m_variant);
}

template<typename L,typename R>
inline bool Either<L,R>::isRight() const noexcept
{
    return m_variant.index() == 1;
}

template<typename L,typename R>
inline bool Either<L,R>::isLeft() const noexcept
{
    return m_variant.index() == 0;
}

template<typename L,typename R>
template<typename FL,typename FR>
std::invoke_result_t<FL,L>
Either<L,R>::fold( FL fl, FR fr ) const
{
    return isLeft() ? fl(left()) : fr(right());
}

template<typename L,typename R>
template<typename F>
Either<L,std::invoke_result_t<F,R>> Either<L,R>::map( F f ) const
{
    return isRight() ? Right( f(right() )) : *this;
}

template<typename L,typename R>
template<typename F>
std::invoke_result_t<F,R> Either<L,R>::flatMap( F f ) const
{
    return isRight() ? f(right()) : *this;
}

template<typename L,typename R>
R const& Either<L,R>::getOrElse( R const& d ) const noexcept
{
    return isRight() ? right() : d;
}

template<typename L,typename R>
template<typename F>
void Either<L,R>::foreach( F f ) const
{
    if( isRight() ) f(right());
}

template<typename L,typename R>
Either<R,L> Either<L,R>::reverse() const noexcept
{
    return isRight() ? Left( right() ) : Right( left() );
}

template<typename L,typename R> inline
void Either<L,R>::swap( Either& other ) noexcept
{
    m_variant.swap( other.m_variant );
}


#endif  // defined( FLIC_EITHER_HH )