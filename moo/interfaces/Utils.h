#pragma once

#include "Types.h"

namespace graphics
{
   inline bool IsInRect(int x, int y, const Rect& rect)
   {
      return rect.x <= x && x < (rect.x + rect.w) &&
         rect.y <= y && y < (rect.y + rect.h);
   }


}
