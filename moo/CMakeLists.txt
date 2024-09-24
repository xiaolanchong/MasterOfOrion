# CMakeList.txt : CMake project for moo, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (moo "moo.cpp" "moo.h")


if (MSVC)
    # warning level 4
    add_compile_options(/W4)
else()
    # additional warnings
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set_property(TARGET moo PROPERTY CXX_STANDARD 20)
target_link_libraries(moo PRIVATE SDL3::SDL3)
target_link_libraries(moo PRIVATE SDL3_image::SDL3_image)

# TODO: Add tests and install targets if needed.
include_directories("../SDL/include")
include_directories("../SDL_image/include")


