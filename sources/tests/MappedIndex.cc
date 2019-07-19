/**
 * @file tests/MappedIndex.cc
 * @author Massimiliano Pagani
 * @date 2019-04-19
 */

#include <flic/MappedIndex.hh>
#include <cassert>
#include <array>
#include <iterator>

void test_base()
{
    std::array<int,4> set{0,1,2,3};
    auto index = Index{ std::cbegin(set), std::cend(set) };
    auto mapped = MappedIndex<std::string,decltype(index)>{ index, []( int n ){ return std::to_string(n);} };
    std::array<std::string,4> check{"0","1","2","3"};
    for( int i=0; i<4; ++i )
    {
        assert( mapped.isValid() );
        Option<std::string> first = mapped.get();
        assert( first.isDefined() );
        assert( first.get() == check[i] );
        auto oi = mapped.next();
        if( i==4 )
        {
            assert( oi.isEmpty() );
        }
        else
        {
            assert( oi.isDefined() );
            mapped = oi.get();
        }
    }
}

int main()
{
    test_base();
    return 0;
}