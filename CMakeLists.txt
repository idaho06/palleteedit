cmake_policy(SET CMP0048 NEW) # For using VERSION in "project"
project(pedit VERSION 1.0 DESCRIPTION "Pallete Editor GUI and lib")
cmake_minimum_required(VERSION 3.16.3)

# include files
include_directories( 
    ./src 
    )

# pkg-config calls
find_package(PkgConfig REQUIRED) 

pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)
#pkg_check_modules(SDL2_MIXER REQUIRED IMPORTED_TARGET SDL2_mixer)
pkg_check_modules(SDL2_GFX REQUIRED IMPORTED_TARGET SDL2_gfx)

# We expect the pallete library project to be outside here
# https://stackoverflow.com/questions/10004134/add-a-dependency-not-in-a-subdirectory-using-cmake
add_subdirectory( "../akinopallete" "${CMAKE_CURRENT_BINARY_DIR}/akinopallete_build")

#file(GLOB_RECURSE pedit_SOURCES "./src/*.c*")
#add_executable(pedit ${pedit_SOURCES})
# apparently, GLOB is evil

# Easy way to get list of files in vim
# :read ! ls src/*.cpp

add_executable(pedit
    src/main.cpp
    src/actions.cpp
    src/redrawscreen.cpp
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
