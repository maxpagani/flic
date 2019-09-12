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

/**
 * @brief Class used to apply functional functors/operators.
 * 
 * By using this class you'll be able to apply map, filter, fold and all the 
 * other functional constructs to your data sequence. Once you are done you
 * can get back a C++ collection by invoking the toVector method.
 * 
 * @tparam Idx the index used to iterate over source data.
 */

template<typename Idx>
class Applier {
    public:
        typedef typename Idx::Iterator Iter;
        typedef typename Idx::IndexedType T;

        /** Constructs an applier given a pair of iterators.
         * 
         * @param begin the iterator to the beginning of the container to 
         *              iterate.
         * @param end the iterator to the end of the container to iterate.
         */
        Applier( Iter begin, Iter end );

        /** Constructs an applier from an index.
         * 
         * @param index the index to iterate.
         */
        explicit Applier( Idx index );

        /**
         * @brief maps from a sequence of one type into a sequence of another
         *        type given a function that transforms types.
         * 
         * @tparam B the target type.
         * @param fn the function that transforms types of this applier into B.
         * @return Applier<MappedIndex<B,Idx>> a new applier capable of doing 
         *                                     the mapping.
         */
        template<typename B>
        Applier<MappedIndex<B,Idx>> map(std::function<B(T)> fn);

        /**
         * @brief filters the sequence given a function that sets a rule to 
         *        chose which elements are filtered.
         * 
         * @param fn the filtering function. If this function returns true for
         *           x then x is part of the resulting sequence.
         * @return Applier<FilteredIndex<Idx>> a new applier capable of 
         *                                     performing the filtering.
         */
        Applier<FilteredIndex<Idx>> filter(std::function<bool(T const&)> fn);

        template<typename B>
        Applier<Idx> flatMap(std::function<B(T const&)> fn);

        /**
         * @brief transform the sequence defined by the applier into a C++
         *        std::vector.
         * 
         * @return std::vector<T> 
         */
        std::vector<T> toVector() const;
        std::list<T> toList() const;

        T
        fold( T const& zero, std::function<T(T const&,T const&)> ) const;

        template<typename R> R
        foldLeft( R const& zero, std::function<R(R const&,T const&)> ) const;

        template<typename R> R
        foldRight( R const& zero, std::function<R(R const&,T const&)> ) const;

        void
        foreach( std::function<void(T const&)> ) const;

        bool
        exists( std::function<bool(T const&)> ) const;

        bool
        forAll( std::function<bool(T const&)> ) const;

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
        for( ; scan.isValid(); scan = scan.next() )
        {
            container.push_back( scan.get().get() );
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

template<typename Idx> 
auto Applier<Idx>::fold( T const& zero, std::function<T(T const&,T const&)> fn ) const -> T
{
    T result{ zero };
    for( auto scan = m_source; scan.isValid(); scan = scan.next() )
    {
        result = fn( result, scan.get().get() );
    }
    return result;
}

template<typename Idx> 
template<typename R> R
Applier<Idx>::foldLeft( R const& zero, std::function<R(R const&,T const&)> fn ) const
{
    R result{ zero };
    for( auto scan = m_source; scan.isValid(); scan = scan.next() )
    {
        result = fn( result, scan.get().get() );
    }
    return result;
}

template<typename Idx> 
template<typename R> R
Applier<Idx>::foldRight( R const& zero, std::function<R(R const&,T const&)> fn ) const
{
    // Here we have to reverse the sequence or perform some recursion that
    // does the same.
    // on Scala, foldRight just creates a new reversed sequence
}

template<typename Idx> 
void
Applier<Idx>::foreach( std::function<void(T const&)> fn ) const
{
    for( auto scan = m_source; scan.isValid(); scan = scan.next() )
    {
        fn( scan.get().get() );
    }
}

template<typename Idx> 
bool
Applier<Idx>::exists( std::function<bool(T const&)> fn ) const
{
    for( auto scan = m_source; scan.isValid(); scan = scan.next() )
    {
        if( fn( scan.get().get() ) )
        {
            return true;
        }
    }
    return false;
}

template<typename Idx> 
bool
Applier<Idx>::forAll( std::function<bool(T const&)> fn ) const
{
    // this can be defined in terms of exists, but I would have to build
    // another std::function.
    for( auto scan = m_source; scan.isValid(); scan = scan.next() )
    {
        if( !fn( scan.get().get() ) )
        {
            return false;
        }
    }
    return true;
}

#endif