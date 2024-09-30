#pragma once

#include "Types.h"

namespace graphics
{

struct Rect;

class ITexture
{
public:
   virtual ~ITexture() = default;

   virtual bool Draw(const Rect& area) = 0;
   virtual bool Draw(int x, int y) = 0;
   virtual Size GetSize() const = 0;
};

}