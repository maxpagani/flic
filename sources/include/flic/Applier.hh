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

template<typename T>
class Applier {
    public:
        template<class Iter>
        Applier( Iter begin, Iter end );

        Applier( Index<T> index );

        template<typename B>
        Applier<T> map(std::function<B(T const&)> fn);

        Applier<T> filter(std::function<bool(T const&)> fn);

        template<typename B>
        Applier<T> flatMap(std::function<B(T const&)> fn);

        std::vector<T> toVector() const;
        std::list<T> toList() const;

        // fold, foldRight, foldLeft
        // foreach
        // exists
        
    private:

        Index<T> m_source;
};

template<typename T> template<typename Iter>
Applier<T>::Applier( Iter begin, Iter end ) :
            m_source{ begin, end }
{}

template<typename T> 
Applier<T>::Applier( Index<T> index ) :
            m_source{ index }
{
}

template<typename T> template<typename B> 
Applier<T> Applier<T>::map(std::function<B(T const&)> fn)
{
    return Applier<T>{
        MappedIndex{
            m_source,
            fn
        }
    };
}

template<typename T> 
Applier Applier<T>::filter(std::function<bool(T const&) fn)
{
    return Applier<T>{
        FilteredIndex{
            m_source,
            fn
        }
    };
}

template<typename T> template<typename B> 
Applier Applier<T>::flatMap(std::function<B(T const&)> fn)
{

}

namespace {
    template<T,C> void
    filler( C& container, Index<T> scan )
    {
        while( scan.hasNext() )
        {
            container.push_back( scan.get() );
            scan = scan.next();
        }
    }
}

template<typename T> 
std::vector<T> Applier<T>::toVector() const
{
    std::vector<T> result;
    filler( result, m_source );
    return result;
}

template<typename T> 
std::list<T> Applier<T>::toList() const
{
    std::list<T> result;
    filler( result, m_index );
    return result;
}

#endif