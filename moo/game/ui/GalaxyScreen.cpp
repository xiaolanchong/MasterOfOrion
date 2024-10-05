#include "GalaxyScreen.h"
#include "StarSystemWindow.h"

#include "../../windows/Pane.h"
#include "../../windows/Button.h"

#include <numbers>
#include <cmath>
#include <array>
#include <random>

namespace game::ui
{
   using namespace graphics;
   using namespace windows;

   GalaxyScreen::GalaxyScreen(ScreenContext context)
      : ScreenContext(std::move(context))
   {
      m_windowSystem = std::make_shared<WindowSystem>();
      input->RegisterCallback(m_windowSystem);
      Rect clientRect = graphics->GetClientRect();
      m_windowSystem->SetClientSize(clientRect.w, clientRect.h);

      graphics->SetCursor("cursors/pointing_hand.png");
      auto mainPain = m_windowSystem->Create<Pane>(graphics, graphics->GetClientRect(), "images/galaxy_screen/background.png");
      m_windows.push_back(mainPain);

      createCommandPanel(mainPain, clientRect);
      createMenuAndStats(mainPain);
      createStars(mainPain, clientRect);

      m_starSystemWindow = std::make_shared<StarSystemWindow>(WindowContext{ m_windowSystem, graphics }, mainPain);
      m_starSystemWindow->Hide();
   }

   void GalaxyScreen::createCommandPanel(const BaseWindowPtr& mainPain, const graphics::Rect& clientRect)
   {
      WindowContext windowContext{ m_windowSystem, graphics };
      const int marginX = 10;
      const int marginY = 10;
      const int gapY = 5;
      const int imageWidth = 64;
      const int imageHeight = 64;

      {
         ImageButton::Theme theme =
         {
            .hoveredImageName = "images/galaxy_screen/command_panel/earth_hover_64x64.png",
            .enabledImageName = "images/galaxy_screen/command_panel/earth_64x64.png",
         };

         auto onPlanets = []() {};

         m_windows.push_back(mainPain->Create<ImageButton>(windowContext, BaseButton::State::Enabled, theme,
            Point(marginX + 0 * (imageWidth + gapY), clientRect.h - imageHeight - marginY), std::move(onPlanets)));
      }

      {

         ImageButton::Theme theme =
         {
            .hoveredImageName = "images/galaxy_screen/command_panel/city_hover_64x64.png",
            .enabledImageName = "images/galaxy_screen/command_panel/city_64x64.png",
         };

         auto onColonies = []() {};

         m_windows.push_back(mainPain->Create<ImageButton>(windowContext, BaseButton::State::Enabled, theme,
            Point(marginX + 1 * (imageWidth + gapY), clientRect.h - imageHeight - marginY), std::move(onColonies)));
      }

      {
         ImageButton::Theme theme =
         {
            .hoveredImageName = "images/galaxy_screen/command_panel/fleet_hover_64x64.png",
            .enabledImageName = "images/galaxy_screen/command_panel/fleet_64x64.png",
            .disabledImageName = "images/galaxy_screen/command_panel/fleet_64x64.png",
         };

         auto onFleets = []() {};

         m_windows.push_back(mainPain->Create<ImageButton>(windowContext, BaseButton::State::Enabled, theme,
            Point(marginX + 2 * (imageWidth + gapY), clientRect.h - imageHeight - marginY), std::move(onFleets)));
      }
   }

   void GalaxyScreen::createMenuAndStats(const BaseWindowPtr& mainPain)
   {
      WindowContext windowContext{ m_windowSystem, graphics };
      const int marginX = 10;
      const int marginY = 10;
      const int gapX = 10;
      const int imageWidth = 32;
      const int imageHeight = 32;

      int offsetX = marginX;
      {
         windows::TextButton::Theme theme{
            .fontMetrics = { "Days Sans Black", 16 },
            .hovered = {.r = 0xf0, .g = 0xf0, .b = 0xf0, .a = 255 },
            .enabled = {.r = 0xcc, .g = 0xcc, .b = 0xcc, .a = 255 },
            .disabled = {.r = 0x66, .g = 0x66, .b = 0x66, .a = 255 },
         };

         auto onGamePressed = []() {};

         auto menu = mainPain->Create<TextButton>(windowContext, u8"Game",
            BaseButton::State::Enabled, theme, Point{ offsetX, marginY }, std::move(onGamePressed));

         offsetX += menu->GetRect().w;
         m_windows.push_back(menu);
      }

      FontMetrics statFontMetrics = { "Roboto-Regular", 16 };
      const int statsGap = 100;
      {
         offsetX += statsGap;
         auto imageName = "images/galaxy_screen/menu_stats/gold_coins_32x32.png";
         auto moneyImage = mainPain->Create<Image>(windowContext,
            Point(offsetX, marginY), std::nullopt, imageName);
         m_windows.push_back(moneyImage);

         offsetX += moneyImage->GetRect().w;

         offsetX += gapX;
         auto moneyText = u8"150 BC (+8)";

         auto moneyTextWnd = mainPain->Create<Static>(windowContext.graphics,
            Point(offsetX, marginY), moneyText, statFontMetrics, Color{.g = 0xb3 });
         m_windows.push_back(moneyTextWnd);

         offsetX += moneyTextWnd->GetRect().w;
      }
   }

   void GalaxyScreen::createStars(const BaseWindowPtr& mainPain, const graphics::Rect& clientRect)
   {
      WindowContext windowContext{ m_windowSystem, graphics };

      const int radiusX = 400;
      const int radiusY = 300;
      const size_t total = 20;

      std::array<const char*, 3> allStarColors =
      {
         "blue",
         "red",
         "orange",
      };
      std::random_device rd;  // a seed source for the random number engine
      std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
      std::uniform_int_distribution<> distribX(50, clientRect.w - 50);
      std::uniform_int_distribution<> distribY(50, clientRect.h - 50);

      for (size_t i = 0; i < total; ++i)
      {
         auto angle = 2 * std::numbers::pi / total * i;
         double x = radiusX * std::cos(angle);
         double y = radiusY * std::sin(angle);
    
        // auto topLeft = Point{ clientRect.w / 2 + int(x), clientRect.h/2 + int(y) };
         auto topLeft = Point{ distribX(gen), distribY(gen)};

         ImageButton::Theme theme =
         {
            .hoveredImageName = std::string("images/stars/") + "blue_hovered" + ".png",
            .enabledImageName = std::string("images/stars/") + allStarColors[i % allStarColors.size()] + ".png",
         };

         auto onStar = [this]() { m_starSystemWindow->Show(); };

         m_windows.push_back(mainPain->Create<ImageButton>(windowContext, BaseButton::State::Enabled, theme,
            topLeft, std::move(onStar)));
      }
   }

   void GalaxyScreen::Draw()
   {
      m_windowSystem->Draw();
   }

   void GalaxyScreen::PreDraw()
   {
      m_windowSystem->PreDraw();
   }
}