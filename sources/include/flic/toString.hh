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
#include <sstream>

template<typename T, typename = std::enable_if_t<std::is_class<T>::value>>
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

template<> inline
std::string toString( std::string const& x )
{
    return x;
}

template<> std::string toString(const int& t) { return std::to_string(t); }
template<> std::string toString(const long& t) { return std::to_string(t); }
template<> std::string toString(const long long& t) { return std::to_string(t); }
template<> std::string toString(const unsigned& t) { return std::to_string(t); }
template<> std::string toString(const unsigned long& t) { return std::to_string(t); }
template<> std::string toString(const unsigned long long& t) { return std::to_string(t); }
template<> std::string toString(const float& t) { return std::to_string(t); }
template<> std::string toString(const double& t) { return std::to_string(t); }

#endif