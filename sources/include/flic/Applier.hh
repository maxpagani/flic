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

template<typename Index>
class Applier {
    public:
        typedef typename Index::Iterator Iter;
        typedef typename std::iterator_traits<Iter>::value_type T;


        Applier( Iter begin, Iter end );

        explicit Applier( Index index );

        template<typename B>
        Applier<Index> map(std::function<B(T)> fn);

        Applier<Index> filter(std::function<bool(T const&)> fn);

        template<typename B>
        Applier<Index> flatMap(std::function<B(T const&)> fn);

        std::vector<T> toVector() const;
        std::list<T> toList() const;

        // fold, foldRight, foldLeft
        // foreach
        // exists

    private:

        Index m_source;
};

template<typename Index>
Applier<Index>::Applier( Iter begin, Iter end ) :
            m_source{ begin, end }
{}

template<typename Index>
Applier<Index>::Applier( Index index ) :
            m_source{ index }
{
}

template<typename Index> template<typename B> 
Applier<Index> Applier<Index>::map(std::function<B(T)> fn)
{
    return Applier<Index>{
        MappedIndex{
            m_source,
            fn
        }
    };
}

template<typename Index> 
Applier<Index> Applier<Index>::filter(std::function<bool(T const&)> fn)
{
    return Applier<Index>{
        FilteredIndex{
            m_source,
            fn
        }
    };
}

template<typename Index> template<typename B> 
Applier<Index> Applier<Index>::flatMap(std::function<B(T const&)> fn)
{

}

namespace {
    template<typename Index, typename C> void
    filler( C& container, Index scan )
    {
        while( scan.hasNext() )
        {
            container.push_back( scan.get().get() );
            scan = scan.next();
        }
    }
}

template<typename Index> 
auto Applier<Index>::toVector() const -> std::vector<T>
{
    std::vector<T> result;
    filler( result, m_source );
    return result;
}

template<typename Index> 
auto Applier<Index>::toList() const -> std::list<T>
{
    std::list<T> result;
    filler( result, m_source );
    return result;
}

#endif