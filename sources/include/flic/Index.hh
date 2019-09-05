/**
 * @file include/Index.hh
 * @author Massimiliano Pagani
 * @date 2019-04-16
 */

#if !defined( FLIC_INDEX_HH )
#define FLIC_INDEX_HH

#include <flic/Option.hh>
#include <type_traits>

template<typename It>
class Index
{
        It m_current;
        It m_end;
        typedef decltype(*m_current) BaseIndexedType;
        typedef typename std::remove_reference<BaseIndexedType>::type ConstIndexedType;
    public:
        typedef It Iterator;
        /**
         * Indexed type. This is the type in the collection.
         */
        typedef typename std::remove_const<ConstIndexedType>::type IndexedType;

        /**
         * Constructor.
         * 
         * @param current an iterator to the currently indexed element in the
         *        container.
         * @param end an iterator to the end of the container.
         */
        Index( It current, It end );

        /**
         * Creates an index pointing to the next item in the collection. If the
         * collection has been completely indexed, then the returned index will
         * be not valid.
         * 
         * @return an index to the next item in the collection.
         */
        Index<It> next() const;

        /**
         * Returns true if the next index is valid.
         * 
         * @retval true when next() yields a #isValid() index.
         * @retval false when next() yields an invalid index.
         */
        bool hasNext() const;

        /**
         * Attempts to retrieve the indexed element from the collection.
         * 
         * @retval Some<IndexedType>(x) when the index is valid, x is the value
         *                              of the indexed item in the collection.
         * @retval None<IndexedType>() when the index is not valid.
         */
        Option<IndexedType> get() const;

        /**
         * Checks if the index references a valid item in the collection.
         * 
         * @retval true the indexed item is valid.
         * @retval false the indexed item is invalid.
         */
        bool isValid() const;

        /**
         * Creates an invalid copy of this index. invalid().isValid() is
         * always false.
         * 
         * @return an invalid copy of this index. 
         */
        Index invalid() const;
    private:
};

// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// ::::::::::::::::::::::::::::::::::::::::::::::: Inline & Implementation :::
// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

template<typename It> inline bool 
Index<It>::isValid() const
{
    return m_current != m_end;
}

template<typename It>
Index<It>::Index( It current, It end ) :
           m_current{current},
           m_end{end}
{
}

template<typename It>
Index<It> Index<It>::next() const
{
    if( m_current == m_end )
    {
        return *this;
    }
    else
    {
        auto current = m_current;
        ++current; 
        return Index{ current, m_end };
    }
}

template<typename It> inline bool
Index<It>::hasNext() const
{
    return m_current != m_end;
}

template<typename It>
auto Index<It>::get() const -> Option<IndexedType>
{
    if( m_current != m_end )
    {
        return Some<IndexedType>( *m_current );
    }
    else
    {
        return None<IndexedType>();
    }
}

template<typename It>
Index<It> 
Index<It>::invalid() const
{
    return Index<It>{m_end,m_end};
}

#endif