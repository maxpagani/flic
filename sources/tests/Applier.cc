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
    auto v = std::array<int>{ 0, 1, 2, 3, 4 };
    Applier<int> a{ std::begin(v), std::end(v) };
    auto r = a.toVector();
    assert( std::equal( std::begin(v), std::end(v), std::begin(r)));
}

int main( int argc, char** argv )
{
    basic_applier();
    return 0;
}