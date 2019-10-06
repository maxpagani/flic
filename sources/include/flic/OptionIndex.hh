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

template<typename T>
class OptionIndex
{
    public:
        explicit OptionIndex( Option<T> const& source );
        explicit OptionIndex( Option<T>&& source );

        typedef T IndexedType;

        OptionIndex<T> next() const;
        Option<T> get() const;
        bool isValid() const;
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

template<typename T> OptionIndex<T>
OptionIndex<T>::next() const
{
    OptionIndex{ None<T>() };
}

template<typename T>
inline Option<T>
OptionIndex<T>::get() const
{
    return m_option;
}

template<typename T>
inline bool
OptionIndex<T>::isValid() const
{
    return m_option.isDefined();
}

#endif