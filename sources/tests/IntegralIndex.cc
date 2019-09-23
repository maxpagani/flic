/**
 * @file IntegralIndex.cc
 * @author Massimiliano Pagani (maxpag@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-09-23
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <flic/IntegralIndex.hh>
#include <cassert>

namespace 
{
    void test_integral()
    {
        IntegralIndex index{ 3, 7 };

        for( int i=3; i<7; ++i )
        {
            assert( index.isValid() );
            auto next = index.next();
            assert( index.get().get() == i );
            index = next;
        }
        assert( !index.isValid() );
    }

    void
    test_limit()
    {
        IntegralIndex index{ 3, 3 };
        assert( !index.isValid() );
        auto next = index.next();
        assert( next == index );

        IntegralIndex invalid{ 3, 2 };
        assert( !index.isValid() );
    }

    void
    test_step(int b, int e)
    {
        IntegralIndex index{ b, e, 3 };
        for( int i=b; i<e; i += 3 )
        {
            assert( index.isValid() );
            assert( index.get().get() == i );
            index = index.next();
        }
        assert( !index.isValid() );
    }

    void test_negative_step()
    {
        IntegralIndex index{ 3, 0, -1 };
        for( int i=3; i>0; --i )
        {
            assert( index.isValid() );
            auto next = index.next();
            assert( index.get().get() == i );
            index = next;
        }
        assert( !index.isValid() );

    }
}

int main()
{
    test_integral();
    test_limit();
    test_step(0,9);
    test_step(0,10);
    test_step(0,11);
    test_negative_step();
    return 0;
}