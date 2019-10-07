/**
 * @file flic/FilteredIndex.hh
 * @author Massimiliano Pagani
 * @date 2019-04-17
 */

#if !defined( FLIC_FILTERED_INDEX_HH )
#define FLIC_FILTERED_INDEX_HH

#include <flic/Index.hh>
#include <flic/lambda.hh>
#include <functional>

template<typename Idx>
class FilteredIndex
{
    public:
        typedef typename Idx::IndexedType IndexedType;
        typedef typename Idx::IndexedType SourceType;

        typedef bool (FilterFn)( SourceType const& );
        FilteredIndex( Idx base, std::function<bool(SourceType)> filter );

        FilteredIndex<Idx> next() const;
        bool isDefined() const;
        Option<IndexedType> get() const;

        FilteredIndex invalid() const;
    private:
        static constexpr Idx findFirst( Idx index, std::function<bool(SourceType)> filter );

        Idx m_base;
        std::function<bool(SourceType)> m_filter;
};

// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// ::::::::::::::::::::::::::::::::::::::::::::::: Inline & Implementation :::
// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

template<typename Idx> inline bool
FilteredIndex<Idx>::isDefined() const
{
    return m_base.isDefined();
}

template<typename Idx> inline auto 
FilteredIndex<Idx>::get() const -> Option<IndexedType>
{
    return m_base.get();
}

template<typename Idx>
constexpr Idx FilteredIndex<Idx>::findFirst( Idx index, std::function<bool(SourceType)> filter )
{
    bool isIgnored = true;
    while( index.isDefined() && (isIgnored = !filter(index.get().get())) )
    {
        index = index.next();
    }
    if( isIgnored )
    {
        return index.invalid();
    }    
    else
    {
        return index;
    }
}

template<typename Idx>
FilteredIndex<Idx>::FilteredIndex( Idx base, std::function<bool(SourceType)> filter ) :
                    m_base{ findFirst(base,filter)},
                    m_filter{std::move(filter)}
{
}

template<typename Idx> FilteredIndex<Idx>
FilteredIndex<Idx>::next() const
{
    if( !isDefined() )
    {
        return *this;
    }
    auto index = m_base.next();
    return FilteredIndex<Idx>{ index, m_filter};
    #if 0
    if( m_base.isEmpty() )
    {
        return None<FilteredIndex<Idx>>();
    }
    auto result = m_base.get().next();
    if( result.isEmpty() )
    {
        return None<FilteredIndex<Idx>>();
    }
    return findFirst( result.get(), m_filter )
        .map( [this]( auto x) { return FilteredIndex<Idx>(x,m_filter); });
    #endif
}

template<typename Idx>
FilteredIndex<Idx> FilteredIndex<Idx>::invalid() const
{
    return FilteredIndex<Idx>{m_base.invalid(),m_filter};
}


#endif
