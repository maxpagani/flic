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
#include <algorithm>
#include <flic/Index.hh>
#include <flic/MappedIndex.hh>
#include <flic/FilteredIndex.hh>
#include <flic/ZippedIndex.hh>
#include <flic/toString.hh>

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
        //typedef typename Idx::Iterator Iter;
        typedef typename Idx::IndexedType T;

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

        /**
         * @brief Fold is about reducing a sequence by repeatedly applying a
         *        binary function to all the items in the sequence.
         * THe result is obtained by invoking the binary function to the 
         * partial result from the previous step and the current sequence item.
         * The first partial result, used at the first invocation of the 
         * provided function along with the first sequence element is provided
         * as an argument (zero) to this function.
         * 
         * @param zero the initial result (also the result for an empty 
         *             sequence)
         * @return T the result of the fold operation. Given a sequence of 3
         *           elements (e0,e1,e2) of type T and z as the argument zero
         *           of type T, too. The result of the function will be:
         * @code
         *      f(f(f(z,e0),e1),e2)
         * @endcode
         * 
         * @see #foldRight, #foldLeft
         */
        T
        fold( T const& zero, std::function<T(T const&,T const&)> ) const;

        /**
         * @brief Like #fold but with the zero element of a type different from
         *        the type of the elements in the sequence.
         *        This is a generalization of #fold().
         * 
         * @tparam R the type of the result and the zero argument.
         * @param zero the first argument to accompany the first item in the
         *             sequence.
         * @return R the result of the fold from left to right. Given a 
         *           sequence of 3 elements (e0,e1,e2) of type T and z as the
         *           argument zero of type R, too. The result of the foldRight
         *           will be:
         * @code
         *      f(f(f(z,e0),e1),e2)
         * @endcode
         */
        template<typename R> R
        foldLeft( R const& zero, std::function<R(R const&,T const&)> ) const;

        /**
         * @brief Like #foldLeft, but performed from right to left.
         * 
         * @tparam R the type of the result and the zero argument.
         * @param zero the first argument to accompany the last item in the
         *             sequence.
         * @return R the result of the fold from right to left. Given a 
         *           sequence of 3 elements (e0,e1,e2) of type T and z as the
         *           argument zero of type R, too. The result of the foldRight
         *           will be:
         * @code
         *      f(e0,f(e1,f(e2,z)))
         * @endcode
         */
        template<typename R> R
        foldRight( R const& zero, std::function<R(R const&,T const&)> ) const;

        /**
         * @brief Applies a void function to each item in the sequence.
         * 
         * @param f the function to apply to each single item in the sequence.
         *          f is invoked sequentially from left to right.
         */
        void
        foreach( std::function<void(T const&)> f ) const;

        /**
         * @brief Determines if at least one item in the sequence satisfies a
         *        given condition.
         * 
         * @param p the predicate to evaluate. The evaluation stops at the 
         *          first item that satisfies the condition.
         * @return true exists at least one item i in the sequence for which 
         *              p(i) is true.
         * @return false p(i) is always false for each item i in the sequence.
         */
        bool
        exists( std::function<bool(T const&)> p ) const;

        /**
         * @brief Determines whether all items in the sequence satisfy a given
         *        condition.
         * 
         * @param p the predicate to evaluate. The evaluation stops at the 
         *          first item that doesn't satisfy the condition.
         * @return true when for each item i in the sequence p(i) is true.
         * @return false when exists at least one item i for which p(i) is
         *               false.
         */
        bool
        forAll( std::function<bool(T const&)> p ) const;

        /**
         * @brief Converts the sequence into a string.
         * Items in the sequence must have a valid toString implementation (or,
         * if they are classes, the toString method).
         * 
         * @param separator the optional character you want to use to separate
         *                  item. By default this is a comma (',').
         * @param leftDelimiter the optional left delimiter (the character at
         *                      the left of the sequence). By default no 
         *                      left delimiter is produced.
         * @param rightDeIlimiter the optional right delimiter (the character
         *                       at the right end of the sequence). By default
         *                       no right delimiter is produced.
         * 
         * @note separators and delimiters are not produced in the output when
         *       their value is '\0'.
         * @return std::string a textual representation of the sequence.
         */
        std::string
        makeString( char separator=',', char leftDelimiter='\0', char rightDelimiter='\0' ) const;

        Applier<ZippedIndex<T,int>> zipWithIndex() const;

        template<typename Other>
        Applier<ZippedIndex<T,typename Other::IndexedType>>
        zip( Index<Other>& other ) const;
    private:
        Idx m_source;
};

/*
template<typename Idx>
Applier<Idx>::Applier( Iter begin, Iter end ) :
            m_source{ begin, end }
{}
*/

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
    // This code is not constexpr since the sequence data is copied into a
    // std::vector in order to go through backwards.
    // If you want a constexpr implementation then you need to use the 
    // recursion to sweep the data.
    R result{zero};
    auto data = toVector();
    for( auto scan = data.rbegin(); scan != data.rend(); ++scan )
    {
        result = fn( result, *scan );
    }
    return result;
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

template<typename Idx> 
std::string
Applier<Idx>::makeString( char separator, char leftDelimiter, char rightDelimiter ) const
{
    std::string result;
    if( leftDelimiter )
    {
        result.append(1,leftDelimiter);
    }
    auto scan = m_source;
    if( scan.isValid() )
    {
        result.append( toString( scan.get().get() ));
        scan = scan.next();
    }
    for( ; scan.isValid(); scan = scan.next() )
    {
        if( separator )
        {
            result.append(1, separator);
        }
        result.append( toString( scan.get().get() ));
    }
    if( rightDelimiter )
    {
        result.append( 1, rightDelimiter );
    }
    return result;
}


#endif