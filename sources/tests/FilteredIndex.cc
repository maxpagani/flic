/**
 * @file tests/FilteredIndex.cc
 * @author Massimiliano Pagani
 * @date 2019-06-11
 */

#include <flic/FilteredIndex.hh>
#include <cassert>
#include <array>
#include <iterator>
#include <iostream>

void test_base()
{
    std::array<int,6> set{0,1,2,3,4,5};
    auto index = Index{ std::cbegin(set), std::cend(set) };
    auto filtered = FilteredIndex<decltype(index)>{ index, []( int x ){ return x >=3; } };
    for( int i=3; i<6; ++i )
    {
        std::cout << i << "\n";
        assert( filtered.isValid() );
        Option<int> first = filtered.get();
        assert( first.isDefined() );
        assert( first.get() == i );
        filtered = filtered.next();
        if( i < 5 ) 
        {
            assert( filtered.isValid() );
        }
        else
        {
            assert( !filtered.isValid());
        }
    }
}

int main()
{
    test_base();
    return 0;
}