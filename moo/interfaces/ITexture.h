#pragma once

namespace graphics
{

class ITexture
{
public:
   virtual ~ITexture() = default;

   virtual bool Draw(const Rect& area) = 0;
   virtual bool Draw(int x, int y) = 0;
};

}