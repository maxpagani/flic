/**
 * @author Massimiliano Pagani
 * @file tests/Either.cc
 * @date 2019-07-23
 */

#include <flic/Either.hh>
#include <cassert>

namespace {
    void test_base()
    {
        auto l = Either<int,std::string>::Left( 3 );
        assert( l.isLeft() );
        assert( !l.isRight() );
        assert( l.left() == 3 );
        try
        {
            auto x = l.right();
            assert( false );
        }
        catch( std::bad_variant_access const& )
        {
            // ok!
        }
        catch( ... )
        {
            assert( false );
        }

        auto r = Either<int,std::string>::Right( 3 );
        assert( l.isRight() );
        assert( !l.isLeft() );
        assert( l.right() == 3 );
        try
        {
            auto x = l.left();
            assert( false );
        }
        catch( std::bad_variant_access const& )
        {
            // ok.
        }
        catch( ... )
        {
            assert( false );
        }
    }
}

int main()
{
    test_base();
}
