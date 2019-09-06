/**
 * @file Applier.cc
 * @author Massimiliano Pagani (maxpag@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-08-31
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <flic/Applier.hh>
#include <cassert>

void
basic_applier()
{
    typedef std::array<int,5> TestArray;
    auto v = std::array<int,5>{ 0, 1, 2, 3, 4 };
    Applier<Index<TestArray::const_iterator>> a{ std::begin(v), std::end(v) };
    auto r = a.toVector();
    assert( std::equal( std::begin(v), std::end(v), std::begin(r)));
}

void
filtered_mapped_applier()
{
    typedef std::array<int,5> TestArray;
    auto v = std::array<int,5>{ 0, 1, 2, 3, 4 };
    Applier<Index<TestArray::const_iterator>> a{ std::begin(v), std::end(v) };
    auto r = a.
        filter( [](int const & x){return x % 2 == 0;} ).
        map( [](int x) -> std::string { return std::to_string(x); } ).
        toVector();
    char const* expected[] = {"0","2","4"};
    assert(
        std::equal(
            std::begin(r), std::end(r),
            std::begin( expected ), std::end(expected) 
        )
    );
}


int main( int argc, char** argv )
{
    basic_applier();
    filtered_mapped_applier();
    return 0;
}