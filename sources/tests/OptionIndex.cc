/**
 * @file OptionIndex.cc
 * @author Massimiliano Pagani (maxpag@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-10-06
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <flic/OptionIndex.hh>
#include <cassert>

namespace
{
    void test_validOption()
    {
        auto a = Some( 3 );
        auto i = OptionIndex( a );
        assert( i.isValid() );
        assert( i.get() == a );
        i = i.next();
        assert( !i.isValid() );
        assert( i.get() == None<int>() );
    }

    void test_emptyOption()
    {
        auto a = None<int>();
        auto i = OptionIndex( a );
        assert( !i.isValid() );
        assert( i.get() == None<int>() );
    }
}

int main()
{
    test_validOption();
    test_emptyOption();

    return 0;
}