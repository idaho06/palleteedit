cmake_policy(SET CMP0048 NEW) # For using VERSION in "project"
project(pedit VERSION 1.0 DESCRIPTION "Pallete Editor GUI and lib")
cmake_minimum_required(VERSION 3.16.3)

# flags

# include files
include_directories( 
    ./src 
    ../akinopallete/include
    )

# pkg-config calls
find_package(PkgConfig REQUIRED) 

pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)
#pkg_check_modules(SDL2_MIXER REQUIRED IMPORTED_TARGET SDL2_mixer)
pkg_check_modules(SDL2_GFX REQUIRED IMPORTED_TARGET SDL2_gfx)

#add_subdirectory(src)

#file(GLOB_RECURSE pedit_SOURCES "./src/*.c*")
#add_executable(pedit ${pedit_SOURCES})
# apparently, GLOB is evil

# Easy way to get list of files in vim
# :read ! ls src/*.cpp

add_executable(pedit
    src/main.cpp
    src/actions.cpp
    src/redrawscreen.cpp
    # src/pallete.cpp
    )

add_library(akinopallete STATIC
    ../akinopallete/src/pallete.cpp
    )

add_dependencies(pedit
    akinopallete
    )

target_link_libraries(pedit PUBLIC
    PkgConfig::SDL2
    PkgConfig::SDL2_GFX
    akinopallete
    )

# compile options
if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()
