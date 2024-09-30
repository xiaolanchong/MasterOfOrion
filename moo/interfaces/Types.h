#pragma once

#include <cstdint>

namespace graphics
{

struct Rect
{
   int x, y, w, h;
};

struct Color
{
   uint8_t r, g, b, a;
};

struct Point
{
   int x, y;
};

struct Size
{
   int w, h;
};

}