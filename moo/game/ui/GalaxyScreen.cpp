#include "GalaxyScreen.h"
#include "../../windows/Pane.h"
#include "../../windows/Button.h"

namespace game::ui
{
   GalaxyScreen::GalaxyScreen(ScreenContext context)
      : ScreenContext(std::move(context))
   {
      using namespace graphics;
      using namespace windows;

      m_windowSystem = std::make_shared<WindowSystem>();
      input->RegisterCallback(m_windowSystem);
      Rect rect = graphics->GetClientRect();
      m_windowSystem->SetClientSize(rect.w, rect.h);

      graphics->SetCursor("cursors/pointing_hand.png");
      auto mainPain = m_windowSystem->Create<Pane>(graphics, graphics->GetClientRect(), "images/galaxy_screen/background.png");
      m_windows.push_back(mainPain);

      WindowContext windowContext{ m_windowSystem, graphics };
      const int marginX = 10;
      const int marginY = 10;
      const int gapY = 5;
      const int imageWidth = 64;
      const int imageHeight = 64;

      {
         ImageButton::Theme theme =
         {
            .hoveredImageName = "images/galaxy_screen/earth_hover_64x64.png",
            .enabledImageName = "images/galaxy_screen/earth_64x64.png",
            .disabledImageName = "images/galaxy_screen/earth_64x64.png",
         };

         auto onPlanets = []() {};

         m_windows.push_back(mainPain->Create<ImageButton>(windowContext, BaseButton::State::Enabled, theme,
            Point(marginX + 0 * (imageWidth + gapY), rect.h - imageHeight - marginY), std::move(onPlanets)));
      }

      {

         ImageButton::Theme theme =
         {
            .hoveredImageName = "images/galaxy_screen/city_hover_64x64.png",
            .enabledImageName = "images/galaxy_screen/city_64x64.png",
            .disabledImageName = "images/galaxy_screen/city_64x64.png",
         };

         auto onColonies = []() {};

         m_windows.push_back(mainPain->Create<ImageButton>(windowContext, BaseButton::State::Enabled, theme,
            Point(marginX + 1 * (imageWidth + gapY), rect.h - imageHeight - marginY), std::move(onColonies)));
      }

      {
         ImageButton::Theme theme =
         {
            .hoveredImageName = "images/galaxy_screen/fleet_hover_64x64.png",
            .enabledImageName = "images/galaxy_screen/fleet_64x64.png",
            .disabledImageName = "images/galaxy_screen/fleet_64x64.png",
         };

         auto onFleets = []() {};

         m_windows.push_back(mainPain->Create<ImageButton>(windowContext, BaseButton::State::Enabled, theme,
            Point(marginX + 2 * (imageWidth + gapY), rect.h - imageHeight - marginY), std::move(onFleets)));
      }
   }

   void GalaxyScreen::Draw()
   {
      m_windowSystem->Draw();
   }

}