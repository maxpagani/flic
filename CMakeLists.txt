cmake_minimum_required(VERSION 3.14)
project(flic)

set(CMAKE_CXX_STANDARD 17)

include_directories(sources/include)
include_directories(sources/include/flic)

add_executable(flic
        sources/include/flic/Either.hh
        sources/include/flic/FilteredIndex.hh
        sources/include/flic/Index.hh
        sources/include/flic/lambda.hh
        sources/include/flic/MappedIndex.hh
        sources/include/flic/Option.hh
        sources/tests/FilteredIndex.cc
        sources/tests/Index.cc
        sources/tests/MappedIndex.cc
        sources/tests/Option.cc)
