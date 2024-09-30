# CMakeList.txt : CMake project for moo, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (moo 
"interfaces/IGraphics.h"
"interfaces/ITexture.h"
"interfaces/IInput.h"
"interfaces/IEnvironment.h"
"interfaces/InterfaceFwd.h"
"interfaces/Types.h"

"graphics/SdlTypes.h"
"graphics/Graphics.h"
"graphics/Graphics.cpp"
"graphics/Texture.h"
"graphics/Texture.cpp"

"graphics/Input.h"
"graphics/Input.cpp"
"graphics/Environment.h"
"graphics/Environment.cpp"

"windows/WindowSystem.h"
"windows/WindowSystem.cpp"
"windows/Window.h"
"windows/Window.cpp"
"windows/Pane.h"
"windows/Pane.cpp"
"windows/MenuWindow.h"
"windows/MenuWindow.cpp"
"windows/Button.h"
"windows/Button.cpp"

"game/ui/StartScreen.h"
"game/ui/StartScreen.cpp"
"game/ui/GalaxyScreen.h"
"game/ui/GalaxyScreen.cpp"

"game/Game.h"
"game/Game.cpp"

"math/Vector.h"
"math/Vector.cpp"

"moo.cpp" 
"moo.h"
)

if (MSVC)
    # warning level 4
    add_compile_options(/W4)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)  # glog
else()
    # additional warnings
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set_property(TARGET moo PROPERTY CXX_STANDARD 20)
target_link_libraries(moo PRIVATE 
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_ttf::SDL3_ttf
    glog::glog
)

include_directories("../SDL/include")
include_directories("../SDL_image/include")
include_directories("../SDL_ttf/include")
include_directories("../glog/src")

add_subdirectory("tests")