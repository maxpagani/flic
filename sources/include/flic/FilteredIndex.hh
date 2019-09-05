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
        typedef typename Idx::Iterator Iterator;

        typedef bool (FilterFn)( SourceType const& );
        FilteredIndex( Idx base, std::function<bool(SourceType)> filter );
        FilteredIndex<Idx> next() const;
        bool isValid() const;
        Option<IndexedType> get() const;
    private:
        static constexpr Idx findFirst( Idx index, std::function<bool(SourceType)> filter );

        Idx m_base;
        std::function<bool(SourceType)> m_filter;
};

// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// ::::::::::::::::::::::::::::::::::::::::::::::: Inline & Implementation :::
// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

template<typename Idx> inline bool
FilteredIndex<Idx>::isValid() const
{
    return m_base.isValid();
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
    while( index.isValid() && (isIgnored = !filter(index.get().get())) )
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
    #if 0
    while( true )
    {
        auto oValue = index.get();
        if( oValue.isEmpty() )
        {
            return None<Idx>();
        }
        if( filter( oValue.get() ))
        {
            return Some( index );
        }
        auto oIndex = index.next();
        if( oIndex.isEmpty() )
        {
            return None<Idx>();
        }
        index = oIndex.get();
    }
    #endif
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
    if( !isValid() )
    {
        return *this;
    }
    auto index = m_base.next();
    return FilteredIndex<Idx>{findFirst( index, m_filter ), m_filter};
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

#endif