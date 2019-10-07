/**
 * @file ZippedIndex.cc
 * @author Massimiliano Pagani (maxpag@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-09-23
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <flic/ZippedIndex.hh>
#include <flic/IntegralIndex.hh>
#include <cassert>
#include <iostream>

namespace 
{
    void test_zipped_base()
    {
        IntegralIndex left{0,3,1};
        IntegralIndex right{3,0,-1};

        ZippedIndex<IntegralIndex<int>,IntegralIndex<int>> index{left,right};
        int count = 0;

        for( ; index.isDefined(); index = index.next() )
        {
            assert( index.get().get() == std::make_pair( count, 3-count ) );
            ++count;
        }
        assert( !index.isDefined() );
    }

    void test_shorter_left()
    {
        IntegralIndex left{0,3,1};
        IntegralIndex right{3,-1,-1};

        ZippedIndex<IntegralIndex<int>,IntegralIndex<int>> index{left,right};
        int count = 0;

        for( ; index.isDefined(); index = index.next() )
        {
            assert( index.get().get() == std::make_pair( count, 3-count ) );
            ++count;
        }
        assert( !index.isDefined() );
    }

    void test_shorter_right()
    {
        IntegralIndex left{0,4,1};
        IntegralIndex right{3,0,-1};

        ZippedIndex<IntegralIndex<int>,IntegralIndex<int>> index{left,right};
        int count = 0;

        for( ; index.isDefined(); index = index.next() )
        {
            assert( index.get().get() == std::make_pair( count, 3-count ) );
            ++count;
        }
        assert( !index.isDefined() );
    }
}

int main()
{
    test_zipped_base();
    test_shorter_left();
    test_shorter_right();
    return 0;
}