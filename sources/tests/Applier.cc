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
#include <flic/IntegralIndex.hh>
#include <flic/ContainerIndex.hh>
#include <cassert>
#include <iostream>
#include <iterator>
#include <vector>
#include <experimental/array>
using namespace std::literals;

void
basic_applier()
{
    typedef std::array<int,5> TestArray;
    auto v = std::array<int,5>{ 0, 1, 2, 3, 4 };
    Applier<Index<TestArray::const_iterator>> a{ makeIndex(v) };
    auto r = a.toVector();
    assert( std::equal( std::begin(v), std::end(v), std::begin(r)));
}

void
filter_applier()
{
    typedef std::array<int,5> TestArray;
    auto v = std::array<int,5>{ 0, 1, 2, 3, 4 };
    Applier<Index<TestArray::const_iterator>> a{ makeIndex(v) };
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
    Applier<Index<TestArray::const_iterator>> a{ makeIndex(v) };
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
    auto data = std::experimental::make_array(2,3,5,7);
    Applier<Index<int const*>> a{ makeIndex(data) };

    auto result = a.fold( 1, [](int r, int s){return r*s;});
    assert( result == 1*2*3*5*7 );
}

void foldLeft_applier()
{
    auto data = std::experimental::make_array(1,2,3);
    Applier<Index<int const*>> a{ makeIndex(data) };

    auto result = a.foldLeft<std::string>( "x"s, [](auto& r, auto& s){return r+std::to_string(s);});
    assert( result == "x123" );
}

void foldRight_applier()
{
    auto data = std::experimental::make_array(1,2,3);
    Applier<Index<int const*>> a{ makeIndex(data) };

    auto result = a.foldRight<std::string>( "x"s, [](auto& r, auto& s){return r+std::to_string(s);});
    assert( result == "x321" );
}

void exists_applier()
{
    auto data = std::experimental::make_array(1,2,3);
    Applier<Index<int const*>> a{ makeIndex(data) };

    for( int n : data )
    {
        assert( a.exists( [n]( int x ){ return x == n ; }));
    }
    assert( !a.exists( []( int x ){ return x == 42 ; }));
}

void forAll_applier()
{
    auto data = std::experimental::make_array(1,2,3);
    Applier<Index<int const*>> a{ makeIndex(data) };

    auto min = *std::min_element( std::begin(data), std::end(data));
    auto max = *std::max_element( std::begin(data), std::end(data));

    assert( a.forAll( [min,max]( int x ){ return x >= min && x <= max ; }));
    assert( !a.forAll( []( int x ){ return x == 1 ; }));
    assert( !a.forAll( []( int x ){ return x == 3 ; }));
}

void forEach_applier()
{
    auto data = std::experimental::make_array(1,2,3);
    int result = 0;
    Applier<Index<int const*>> a{ makeIndex(data) };

    a.foreach( [&result](int n){ result = result*10 + n; });
    assert( result == 123 );
}

void
demo_applier()
{
    auto source = IntegralIndex{0,10};
    auto a = Applier{ source };
    auto r = a
        .filter( Lambda(x,x>3) )
        .map<std::string>( Lambda(x,std::to_string(x)))
        .fold( "seq:", []( std::string const& r, std::string const& x ){ return r+x; } );
    std::cout << "r=" << r << "\n";
    assert( r == "seq:456789" );
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
    forEach_applier();
    demo_applier();

    return 0;
}