/**
 * @file include/flic/toString.hh
 * @author Massimiliano Pagani (maxpag@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-09-21
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#if !defined( FLIC_TO_STRING_HH )
#define FLIC_TO_STRING_HH

#include <string>

template<class T> // T has a valid std::to_string( T const& ) function
std::string toString( T const& x )
{
    return std::to_string( x );
}

template<class T> // T is a class && T::toString exists
std::string toString( T const& t )
{
    return t.toString();
}

template<class T> // T has a valid ostream& operator<<( ostream&, T const& )
std::string toString( T const& t )
{
    std::ostringstream buffer;
    buffer << t;
    return buffer.str();
}

#endif