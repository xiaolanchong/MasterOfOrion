#pragma once

#include "../../windows/WindowSystem.h"
#include "IScreen.h"
#include "ScreenContext.h"

namespace game::ui
{

   class StartScreen: public IScreen
                    , private ScreenContext
   {
   public:
      explicit StartScreen(ScreenContext context);

      void PreDraw() override;
      void Draw() override;

   private:
      std::shared_ptr<windows::WindowSystem> m_windowSystem;
      std::list<windows::IWindowPtr> m_windows;
   };

}
