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

/**
 * ZippedIndex creates a new index by zipping together two source indexes.
 * Given sequence (0,1,2,3) and sequence ('a','b','c','d') the zipped
 * sequence is ( (0,'a'), (1,'b'), (2,'c'), (3,'d')) where type of elements in
 * the sequence is std::pair.
 *
 * The zipped sequence is long as the shortest source sequence.
 */

template<typename IL,typename IR>
class ZippedIndex
{
    public:
        typedef typename IL::IndexedType L;
        typedef typename IR::IndexedType R;
        typedef std::pair<L,R> IndexedType;

        ZippedIndex( IL indexLeft, IR indexRight );
        ZippedIndex<IL,IR> next() const;
        Option<IndexedType> get() const;
        bool isDefined() const;
    private:
        IL m_indexLeft;
        IR m_indexRight;
};

// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// :::::::::::::::::::::::::::::::::::::::::::::::::::::::: implementation :::
// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

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
    auto oLeft = m_indexLeft.get();
    auto oRight = m_indexRight.get();
    auto oItem = oLeft.flatMap(
        [&oRight]( auto left ){
            return oRight.map(
                [&left](auto right) {
                    return std::pair(left,right);
                }
            );
        }
    );

    return oItem;
}

template<typename IL,typename IR>
inline bool ZippedIndex<IL,IR>::isDefined() const
{
    return m_indexLeft.isDefined() && m_indexRight.isDefined();
}

#endif