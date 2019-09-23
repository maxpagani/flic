/**
 * @file include/flic/ZippedIndex.hh
 * @author Massimiliano Pagani (maxpag@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-09-21
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#if !defined( FLIC_ZIPPED_INDEX_HH )
#define FLIC_ZIPPED_INDEX_HH

#include <flic/Option.hh>

template<typename IL,typename IR>
class ZippedIndex
{
    public:
        typename IL::IndexedType;
        typename IR::IndexedType;
        typedef IL::IndexedType L;
        typedef IR::IndexedType R;
        typedef std::pair<L,R> IndexedType;

        ZippedIndex( IL indexLeft, IR indexRight );
        ZippedIndex<IL,IR> next() const;
        Option<IndexedType> get() const;
        bool isValid() const;
    private:
        IL m_indexLeft;
        IR m_indexRight;
};

template<typename IL,typename IR>
ZippedIndex<IL,IR>::ZippedIndex( IL indexLeft, IR indexRight ) :
                    m_indexLeft{ indexLeft },
                    m_indexRight{ indexRight }
{
}

template<typename IL,typename IR>
ZippedIndex<IL,IR> ZippedIndex<IL,IR>::next() const
{
    auto nextLeft = m_indexLeft.next();
    auto nextRight = m_indexRight.next();
    return ZippedIndex(nextLeft,nextRight);
}

template<typename IL,typename IR>
auto ZippedIndex<IL,IR>::get() const -> Option<IndexedType>
{
    oLeft = m_indexLeft.get();
    oRight = m_indexRight.get();
    auto oItem = oLeft.flatMap(
        []( auto left ){
            return oRight.map(
                [left](auto right) {
                    return std::pair(left,right);
                }
            )
        }
    );

    return oItem;
}

template<typename IL,typename IR>
bool ZippedIndex<IL,IR>::isValid() const
{
    return m_indexLeft.isValid() && m_indexRight.isValid();
}

#endif