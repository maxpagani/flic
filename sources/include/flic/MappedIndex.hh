/**
 * @file flic/MappedIndex.hh
 * @author Massimiliano Pagani
 * @date 2019-04-16
 */

#if !defined( FLIC_MAPPED_INDEX_HH )
#define FLIC_MAPPED_INDEX_HH

#include <flic/Index.hh>
#include <functional>

/**
 * @tparam B the type you are mapping to.
 * @tparam Idx the index you want to map.
 */
template<typename B,typename Idx>
class MappedIndex
{
    public:
        typedef typename Idx::Iterator Iterator;

        typedef B IndexedType;
        typedef typename Idx::IndexedType SourceType;
        //typedef B (MapFn)( SourceType const& );
        MappedIndex( Idx base, std::function<B(SourceType)> map );
        MappedIndex& operator=( MappedIndex const& ) = default;

        bool hasNext() const;
        Option<MappedIndex<B,Idx>> next() const;
        bool isValid() const;
        Option<IndexedType> get() const;
    private:
        Idx m_base;
        std::function<B(SourceType)> m_map;
};

template<typename B,typename Idx>
MappedIndex<B,Idx>::MappedIndex( Idx base, std::function<B(SourceType)> map ) :
                    m_base{base},
                    m_map{std::move(map)}
{
}

template<typename B,typename Idx> 
inline bool
MappedIndex<B,Idx>::hasNext() const
{
    return m_base.hasNext();
}

template<typename B,typename Idx> Option<MappedIndex<B,Idx>>
MappedIndex<B,Idx>::next() const
{
    Option<Idx> result = m_base.next();
    return result.map( [this]( Idx const& x ){ return MappedIndex( x, m_map ); });
}

template<typename B,typename Idx> bool
MappedIndex<B,Idx>::isValid() const
{
    return m_base.isValid();
}

template<typename B,typename Idx> auto 
MappedIndex<B,Idx>::get() const -> Option<IndexedType>
{
    Option<SourceType> base = m_base.get(); 
    auto mapFn = [this]( SourceType const& x ){ return this->m_map(x); };
    return base.map( mapFn );
}

#endif