/**
 * @file include/flic/IntegralIndex.hh
 * @author Massimiliano Pagani (maxpag@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-09-21
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#if !defined( FLIC_INTEGRAL_INDEX_HH )
#define FLIC_INTEGRAL_INDEX_HH

#include <flic/Option.hh>
#include <cassert>

template<typename T>
class IntegralIndex;

template<typename T>
bool operator==( IntegralIndex<T> const& lhs, IntegralIndex<T> const& rhs );

template<typename T>
class IntegralIndex
{
    public:
        typedef T IndexedType;

        IntegralIndex( T begin, T end, T step=static_cast<T>(1) );

        IntegralIndex<T> next() const;
        bool isValid() const;
        Option<T> get() const;
    private:
        friend bool operator==<>( IntegralIndex<T> const&, IntegralIndex<T> const& );

        T m_current;
        T m_end;
        T m_step;
};

template<typename T>
IntegralIndex<T>::IntegralIndex( T begin, T end, T step ) :
                  m_current{begin},
                  m_end{ end },
                  m_step{ step }
{
    assert( m_step != 0 );
}

template<typename T>
IntegralIndex<T> IntegralIndex<T>::next() const
{
    if( isValid() )
    {
        return IntegralIndex<T>{ m_current+m_step, m_end, m_step };
    }
    else
    {
        return *this;
    }
}

template<typename T> inline 
bool IntegralIndex<T>::isValid() const
{
    if( m_step > 0 )
    {
        return m_current < m_end;
    }
    else
    {
        return m_current > m_end;
    }
    
}

template<typename T>
Option<T> IntegralIndex<T>::get() const
{
    if( isValid() ) 
    {
        return Some( m_current );
    }
    else 
    {
        return None<T>();
    }
}

template<typename T>
bool operator==( IntegralIndex<T> const& lhs, IntegralIndex<T> const& rhs )
{
    return lhs.m_current == rhs.m_current &&
           lhs.m_end && rhs.m_end &&
           lhs.m_step && rhs.m_step;
}

#endif