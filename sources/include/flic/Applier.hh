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

template<typename Iter>
class Applier {
    public:
        typedef typename std::iterator_traits<Iter>::value_type T;

        Applier( Iter begin, Iter end );

        Applier( Index<Iter> index );

        template<typename B>
        Applier<Iter> map(std::function<B(T const&)> fn);

        Applier<Iter> filter(std::function<bool(T const&)> fn);

        template<typename B>
        Applier<Iter> flatMap(std::function<B(T const&)> fn);

        std::vector<T> toVector() const;
        std::list<T> toList() const;

        // fold, foldRight, foldLeft
        // foreach
        // exists

    private:

        Index<Iter> m_source;
};

template<typename Iter>
Applier<Iter>::Applier( Iter begin, Iter end ) :
            m_source{ begin, end }
{}

template<typename Iter>
Applier<Iter>::Applier( Index<Iter> index ) :
            m_source{ index }
{
}

template<typename Iter> template<typename B> 
Applier<Iter> Applier<Iter>::map(std::function<B(T const&)> fn)
{
    return Applier<Iter>{
        MappedIndex{
            m_source,
            fn
        }
    };
}

template<typename Iter> 
Applier<Iter> Applier<Iter>::filter(std::function<bool(T const&)> fn)
{
    return Applier<Iter>{
        FilteredIndex{
            m_source,
            fn
        }
    };
}

template<typename Iter> template<typename B> 
Applier<Iter> Applier<Iter>::flatMap(std::function<B(T const&)> fn)
{

}

namespace {
    template<typename T, typename C> void
    filler( C& container, Index<T> scan )
    {
        while( scan.hasNext() )
        {
            container.push_back( scan.get().get() );
            scan = scan.next();
        }
    }
}

template<typename Iter> 
auto Applier<Iter>::toVector() const -> std::vector<T>
{
    std::vector<T> result;
    filler( result, m_source );
    return result;
}

template<typename Iter> 
auto Applier<Iter>::toList() const -> std::list<T>
{
    std::list<T> result;
    filler( result, m_source );
    return result;
}

#endif