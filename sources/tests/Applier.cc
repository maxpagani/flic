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
#include <iostream>
#include <iterator>
#include <vector>

using namespace std::literals;

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
filter_applier()
{
    typedef std::array<int,5> TestArray;
    auto v = std::array<int,5>{ 0, 1, 2, 3, 4 };
    Applier<Index<TestArray::const_iterator>> a{ std::begin(v), std::end(v) };
    auto r = a.
        filter( [](int const & x){return (x % 2) == 0;} ).
        toVector();
    int expected[] = {0,2,4};
    assert(
        std::equal(
            std::begin(r), std::end(r),
            std::begin( expected ), std::end(expected) 
        )
    );

}

void
filtered_mapped_applier()
{
    typedef std::array<int,5> TestArray;
    auto v = std::array<int,5>{ 0, 1, 2, 3, 4 };
    Applier<Index<TestArray::const_iterator>> a{ std::begin(v), std::end(v) };
    auto r = a.
        filter( [](int const & x){return x % 2 == 0;} ).
        map<std::string>( [](int x) { return std::to_string(x); } ).
        toVector();
    char const* expected[] = {"0","2","4"};
    assert(
        std::equal(
            std::begin(r), std::end(r),
            std::begin( expected ), std::end(expected) 
        )
    );
}

void
fold_applier()
{
    int data[] = {2,3,5,7};
    Applier<Index<int const*>> a{ std::begin(data), std::end(data) };

    auto result = a.fold( 1, [](int r, int s){return r*s;});
    assert( result == 1*2*3*5*7 );
}

void foldLeft_applier()
{
    int data[] = {1,2,3};
    Applier<Index<int const*>> a{ std::begin(data), std::end(data) };

    auto result = a.foldLeft<std::string>( "x"s, [](auto& r, auto& s){return r+std::to_string(s);});
    assert( result == "x123" );
}

void foldRight_applier()
{
    int data[] = {1,2,3};
    Applier<Index<int const*>> a{ std::begin(data), std::end(data) };

    auto result = a.foldLeft<std::string>( "x"s, [](auto& r, auto& s){return r+std::to_string(s);});
    assert( result == "x321" );
}

void exists_applier()
{

}

void forAll_applier()
{

}


int main( int argc, char** argv )
{
    basic_applier();
    filter_applier();
    filtered_mapped_applier();
    fold_applier();
    foldLeft_applier();
    foldRight_applier();
    exists_applier();
    forAll_applier();

    return 0;
}