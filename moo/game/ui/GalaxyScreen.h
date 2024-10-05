#pragma once

#include "../../windows/WindowSystem.h"
#include "IScreen.h"
#include "ScreenContext.h"

namespace game::ui
{
   class StarSystemWindow;

   class GalaxyScreen: public IScreen
                     , private ScreenContext
   {
   public:
      explicit GalaxyScreen(ScreenContext context);

      void PreDraw() override;
      void Draw() override;

   private:
      void createCommandPanel(const windows::BaseWindowPtr& mainPain, const graphics::Rect& clientRect);
      void createMenuAndStats(const windows::BaseWindowPtr& mainPain);

      void createStars(const windows::BaseWindowPtr& mainPain, const graphics::Rect& clientRect);
   private:
      std::shared_ptr<windows::WindowSystem> m_windowSystem;
      std::list<windows::IWindowPtr> m_windows;
      std::shared_ptr< StarSystemWindow> m_starSystemWindow;
   };

}
