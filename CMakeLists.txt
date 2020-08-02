project(demo01)
cmake_minimum_required(VERSION 3.17.2)

# flags

# include files
include_directories( ./src )

# pkg-config calls
find_package(PkgConfig REQUIRED) 

pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)
#pkg_check_modules(SDL2_MIXER REQUIRED IMPORTED_TARGET SDL2_mixer)
pkg_check_modules(SDL2_GFX REQUIRED IMPORTED_TARGET SDL2_gfx)

add_subdirectory(src)
file(GLOB_RECURSE pedit_SOURCES "./src/*.c*")

add_executable(pedit ${pedit_SOURCES})

target_link_libraries(pedit PUBLIC
    PkgConfig::SDL2
    PkgConfig::SDL2_GFX)

# compile options
if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()
