# CMakeList.txt : CMake project for moo, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (moo 
"interfaces/IGraphics.h"
"interfaces/ITexture.h"
"interfaces/InterfaceFwd.h"
"interfaces/Types.h"

"graphics/SdlTypes.h"
"graphics/Graphics.h"
"graphics/Graphics.cpp"
"graphics/Texture.h"
"graphics/Texture.cpp"

"windows/WindowSystem.h"
"windows/WindowSystem.h"

"math/Vector.h"
"math/Vector.cpp"

"moo.cpp" 
"moo.h"
)


if (MSVC)
    # warning level 4
    add_compile_options(/W4)
else()
    # additional warnings
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set_property(TARGET moo PROPERTY CXX_STANDARD 20)
target_link_libraries(moo PRIVATE 
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_ttf::SDL3_ttf
)

include_directories("../SDL/include")
include_directories("../SDL_image/include")
include_directories("../SDL_ttf/include")

