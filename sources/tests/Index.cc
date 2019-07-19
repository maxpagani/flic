/**
 * @file tests/Index.cc
 * @author Massimiliano Pagani
 * @date 2019-04-19
 */

#include <flic/Index.hh>
#include <cassert>
#include <array>
#include <iterator>

void test_base()
{
    std::array<int,4> set{0,1,2,3};
    auto index = Index<std::array<int,4>::const_iterator>( std::cbegin(set), std::cend(set) );
    for( int i=0; i<4; ++i )
    {
        assert( index.isValid() );
        Option<int> first = index.get();
        assert( first.isDefined() );
        assert( first.get() == i );
        auto oi = index.next();
        if( i==4 )
        {
            assert( oi.isEmpty() );
        }
        else
        {
            assert( oi.isDefined() );
            index = oi.get();
        }
    }
}

int main()
{
    test_base();
    return 0;
}