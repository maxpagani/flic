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
        assert( filtered.isValid() );
        Option<int> first = filtered.get();
        assert( first.isDefined() );
        assert( first.get() == i );
        filtered = filtered.next();
    }
    assert( !filtered.isValid() );
}

void test_edge()
{
    std::array<int,7> set{0,1,2,3,4,5,6};
    auto index = Index{ std::cbegin(set), std::cend(set) };
    auto filtered = FilteredIndex<decltype(index)>{ index, []( int x ){ return (x % 2) == 0; } };
    for( int i=0; i<=6; i+=2 )
    {
        assert( filtered.isValid() );
        Option<int> first = filtered.get();
        assert( first.isDefined() );
        assert( first.get() == i );
        filtered = filtered.next();
    }
    assert( !filtered.isValid() );
}

int main()
{
    test_base();
    test_edge();
    return 0;
}