/**
 * @file MakeIndex.hh
 * @author Massimiliano Pagani (maxpag@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-08-11
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#if !defined( FLIC_MAKE_INDEX_HH )
#  define FLIC_MAKE_INDEX_HH

#include <flic/Index.hh>

template<typename T>
Index<> makeIndex( T const& container )
{
    return Index<>( std::begin( container ), std::end( container ));
}


#endif