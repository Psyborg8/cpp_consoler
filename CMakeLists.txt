cmake_minimum_required( VERSION 3.9 )
project( cpp_consoler )

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )


file( GLOB_RECURSE SRC src/*.cpp )
add_library( cpp_consoler ${SRC} )

target_include_directories( cpp_consoler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src )

find_package( fmt )
target_link_libraries( cpp_consoler fmt::fmt )

target_compile_options( cpp_consoler
    PRIVATE
        -std=c++20
        -Wall
        -Wextra
        -Wno-unused-parameter
)

if( CMAKE_BUILD_TYPE STREQUAL "DEBUG" )
    target_compile_options( cpp_consoler PUBLIC -ggdb3 -Og )
    target_compile_definitions( cpp_consoler PRIVATE _DEBUG=1 )
elseif( CMAKE_BUILD_TYPE STREQUAL "RELEASE" )
    target_compile_options( cpp_consoler PUBLIC -O2 )
endif()

if( BUILD_TESTS )
    add_executable( cpp_consoler_tests tests/tests.cpp )
    target_include_directories( cpp_consoler_tests PUBLIC ${CMAKE_CURRENT_LIST_DIR} )
    target_link_libraries( cpp_consoler_tests cpp_consoler )
endif()

