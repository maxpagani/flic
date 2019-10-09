/**
 * @file OptionIndex.hh
 * @author Massimiliano Pagani (maxpag@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-10-06
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#if !defined( FLIC_OPTION_INDEX_HH )
#define FLIC_OPTION_INDEX_HH

#include <flic/Option.hh>

/**
 * @brief Index for Option template.
 * 
 * By this index you can use the Applier with an Option.
 * 
 * @tparam T the type of the option.
 */

template<typename T>
class OptionIndex
{
    public:

        /**
         * @brief Construct a new Option Index object
         * Constructor and move Constructor.
         * 
         * @param source the source option.
         * 
         * @{
         */
        explicit OptionIndex( Option<T> const& source );
        explicit OptionIndex( Option<T>&& source );
        /** @} */

        typedef T IndexedType;

        /**
         * @brief Index advance function.
         * 
         * @return OptionIndex<T> 
         */
        constexpr OptionIndex<T> next() const;

        /**
         * @brief Retrieve the current referenced element.
         * 
         * 
         * @return Option<T> 
         */
        constexpr Option<T> get() const;

        /**
         * @brief Returns true if you can invoke next on this
         * index.
         * 
         * @return true you can invoke next (because this indexed value is 
         *         valid).
         * @return false no more elements in the sequence.
         */
        bool constexpr isDefined() const;
    private:
        Option<T> m_option;
};


// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// :::::::::::::::::::::::::::::::::::::::::::::::::::::::: inline methods :::
// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

template<typename T>
OptionIndex<T>::OptionIndex( Option<T> const& source ) : m_option{source}
{
}

template<typename T>
OptionIndex<T>::OptionIndex( Option<T>&& source ) : m_option{ std::move( source )}
{
}

template<typename T> constexpr OptionIndex<T>
OptionIndex<T>::next() const
{
    return OptionIndex{ None<T>() };
}

template<typename T>
inline constexpr Option<T>
OptionIndex<T>::get() const
{
    return m_option;
}

template<typename T>
inline constexpr bool
OptionIndex<T>::isDefined() const
{
    return m_option.isDefined();
}

#endif