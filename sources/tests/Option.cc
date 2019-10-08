/**
 * @file tests/option.cc
 * @author Massimiliano Pagani
 * @date 2019-04-28
 */

#include <flic/Option.hh>
#include <cassert>

namespace
{
    void
    test_base()
    {
        auto a = Some( 3 );
        assert( a.isDefined() );
        assert( !a.isEmpty());
        assert( a.get() == 3 );

        assert( a == Some(3) );

        auto b = None<int>();
        assert( b.isEmpty() );
        try
        {
            int noValue = b.get();
            assert( false );
            (void) noValue;
        }
        catch(const std::invalid_argument& e)
        {
            // ok!
        }
        catch( ... )
        {
            assert( false );
        }

        assert( a != b );
        assert( b == None<int>() );
    }

    void
    test_map()
    {
        auto a = Some( 3 );
        auto b = a.map( []( const int& x ){ return std::to_string(x); } );
        assert( b.isDefined() );
        assert( b.get() == "3" );

        auto c = None<int>();
        auto d = c.map( []( const int& x ){ return std::to_string(x); } );
        assert( d.isEmpty() );
    }

    void
    test_flatMap()
    {
        auto a = Some( 3 );
        auto b = a.flatMap( []( const int& x ){ return Some( std::to_string(x)); });
        assert( b.isDefined() );
        assert( b.get() == "3" );

        auto c = a.flatMap( []( const int& x ){return None<std::string>(); } );
        assert( !c.isDefined() );

        auto d = None<int>();
        auto e = d.flatMap( []( const int& x ){return Some(std::to_string(x)); } );
        assert( !e.isDefined() );
    }
}

int
main( int argc, char** argv )
{
    test_base();
    test_map();
    test_flatMap();
    return 0;
}