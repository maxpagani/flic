/**
 * @file flic/IteratorIndex.hh
 * @author Massimiliano Pagani (maxpag@gmail.com)
 * @brief An index specialized for C++ iterators.
 * @version 0.1
 * @date 2019-09-25
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#if !defined( FLIC_CONTAINER_INDEX_HH )
#define FLIC_CONTAINER_INDEX_HH

#include <flic/Index.hh>

/**
 * @brief Builds an Index for a given container.
 * 
 * @tparam T the container type. This can be usually safely omitted.
 * @param container the container instance
 * @return Index<typename T::const_iterator> the index that can be used to 
 *                                           iterate over the container.
 */
template<class T>
Index<typename T::const_iterator> makeIndex( T const& container );


template<class T>
Index<typename T::const_iterator> makeIndex( T const& container )
{
    return Index{ std::cbegin(container), std::cend(container) };
}


#endif  // defined( FLIC_CONTAINER_INDEX_HH )