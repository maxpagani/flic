/**
 * @file include/flic/IntegralIndex.hh
 * @author Massimiliano Pagani (maxpag@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-09-21
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#if !defined( FLIC_INTEGRAL_INDEX_HH )
#define FLIC_INTEGRAL_INDEX_HH

template<typename T>
class IntegralIndex
{
    public:
        typedef T IndexedType;

        IntegralIndex( T begin, T end, T step=1 )

        IntegralIndex<T> next() const;
        bool isValid() const;
        Option<T> get() const;
    private:
        T m_current;
        T m_end;
        T m_step;
};

#endif