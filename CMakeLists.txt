# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("moo")

# Include sub-projects.
add_subdirectory("moo")
add_subdirectory("SDL")

# only bmp and png
set(SDLIMAGE_GIF OFF)
set(SDLIMAGE_JPG OFF)
set(SDLIMAGE_JXL OFF)
set(SDLIMAGE_LBM OFF)
set(SDLIMAGE_TGA OFF)
set(SDLIMAGE_PNM OFF)
set(SDLIMAGE_PCX OFF)

set(SDLIMAGE_AVIF OFF)
set(SDLIMAGE_TIF OFF)
set(SDLIMAGE_QOI OFF)
set(SDLIMAGE_SVG OFF)
set(SDLIMAGE_XCF OFF)
set(SDLIMAGE_XPM OFF)
set(SDLIMAGE_XV OFF)
set(SDLIMAGE_WEBP OFF)

add_subdirectory("SDL_image")

set(SDLTTF_BUILD_SHARED_LIBS ON)
set(SDLTTF_VENDORED ON)
add_subdirectory("SDL_ttf")

add_subdirectory("glog")
add_subdirectory("googletest")