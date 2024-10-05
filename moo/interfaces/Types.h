#pragma once

#include <cstdint>
#include <compare>

namespace graphics
{

struct Rect
{
   int x, y, w, h;
};

struct Color
{
   uint8_t r, g, b, a;

   friend std::strong_ordering operator<=>(const Color& lhs, const Color& rhs) = default;
};

struct Point
{
   int x, y;

   friend std::strong_ordering operator<=>(const Point& lhs, const Point& rhs) = default;
};

struct Size
{
   int w, h;

   friend std::strong_ordering operator<=>(const Size& lhs, const Size& rhs) = default;
};

}