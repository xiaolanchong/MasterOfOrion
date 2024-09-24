// moo.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <memory>
// TODO: Reference additional headers your program requires here.

struct SDL_Surface;
using SDL_SurfacePtr = std::shared_ptr<SDL_Surface>;
