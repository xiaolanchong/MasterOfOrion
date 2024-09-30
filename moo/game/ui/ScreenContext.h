#pragma once

#include "../../interfaces/InterfaceFwd.h"
#include "IScreen.h"

namespace game::ui
{
   struct ScreenContext
   {
      graphics::IGraphicsPtr graphics;
      input::IInputPtr input;
      IScreenCallbackWeakPtr callback;
   };
}