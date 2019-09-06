/**
 * @file Applier.hh
 * @author Massimiliano Pagani (maxpag@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-08-31
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#if !defined( FLIC_APPLIER_HH )
#define FLIC_APPLIER_HH

#include <vector>
#include <list>
#include <functional>
#include <flic/Index.hh>
#include <flic/MappedIndex.hh>
#include <flic/FilteredIndex.hh>

template<typename Idx>
class Applier {
    public:
        typedef typename Idx::Iterator Iter;
        typedef typename std::iterator_traits<Iter>::value_type T;


        Applier( Iter begin, Iter end );

        explicit Applier( Idx index );

        template<typename B>
        Applier<MappedIndex<B,Idx>> map(std::function<B(T)> fn);

        Applier<FilteredIndex<Idx>> filter(std::function<bool(T const&)> fn);

        template<typename B>
        Applier<Idx> flatMap(std::function<B(T const&)> fn);

        std::vector<T> toVector() const;
        std::list<T> toList() const;

        // fold, foldRight, foldLeft
        // foreach
        // exists

    private:

        Idx m_source;
};

template<typename Idx>
Applier<Idx>::Applier( Iter begin, Iter end ) :
            m_source{ begin, end }
{}

template<typename Idx>
Applier<Idx>::Applier( Idx index ) :
            m_source{ index }
{
}

template<typename Idx> template<typename B> 
Applier<MappedIndex<B,Idx>> Applier<Idx>::map(std::function<B(T)> fn)
{
    return Applier<MappedIndex<B,Idx>>{
        MappedIndex{
            m_source,
            fn
        }
    };
}

template<typename Idx> 
Applier<FilteredIndex<Idx>> Applier<Idx>::filter(std::function<bool(T const&)> fn)
{
    return Applier<FilteredIndex<Idx>>{
        FilteredIndex{
            m_source,
            fn
        }
    };
}

template<typename Idx> template<typename B> 
Applier<Idx> Applier<Idx>::flatMap(std::function<B(T const&)> fn)
{

}

namespace {
    template<typename Idx, typename C> void
    filler( C& container, Idx scan )
    {
        while( scan.hasNext() )
        {
            container.push_back( scan.get().get() );
            scan = scan.next();
        }
    }
}

template<typename Idx> 
auto Applier<Idx>::toVector() const -> std::vector<T>
{
    std::vector<T> result;
    filler( result, m_source );
    return result;
}

template<typename Idx> 
auto Applier<Idx>::toList() const -> std::list<T>
{
    std::list<T> result;
    filler( result, m_source );
    return result;
}

#endif