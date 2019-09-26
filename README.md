# flic
Functional Library for C++

The goal of this library is to let the programmer write functional code in much the same way it is written using functional languages.

E.g. in Scala you can write something like:

```scala
(1 to 10).
  filter( _ > 3).
  map( _.toString ).
  fold( "seq:" )( _+_ )
```

to get the (meaningless) string "seq:456789".

By using flic, you can write something that comes close enough, if you are not too picky:

```c++
1_i.to(10).
  filter( Lambda(x,x>3) ).
  map<std::string>( Lambda(x,std::to_string(x))).
  fold( "seq:", []( std::string const& r, std::string const& x ){ return r+x; } );
```

Of course C++ will never be as concise and expressive as Scala is, but at least it could provide you some tools you are used to when coming from other languages. Also code written using functional approach tends to be more robust and with less bug.

Moreover by proper use of metaprogramming and constexpr, the expression could, at least in line of principle, be compiled as:

```c++
std::string result{"seq"};
for( int i=0; i<10; ++i )
{
    if( x > 3 )
    {
      result.append( std::to_string( x ));
    }
}
// result in result;
```

Or even better (though I don't think optimizers could do this right now):
```c++
  std::string{ "seq:456789" };
```
