#pragma once

#include "../../windows/WindowSystem.h"
#include "IScreen.h"
#include "ScreenContext.h"

namespace game::ui
{

   class GalaxyScreen: public IScreen
                     , private ScreenContext
   {
   public:
      explicit GalaxyScreen(ScreenContext context);

      void Draw() override;

   private:
      std::shared_ptr<windows::WindowSystem> m_windowSystem;
      std::list<windows::IWindowPtr> m_windows;
   };

}
