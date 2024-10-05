#include "StarSystemWindow.h"

#include "../../windows/Button.h"
#include "../../windows/Pane.h"

namespace game::ui
{
   using namespace windows;
   using namespace graphics;

   const int leftX = 100;
   const int topY = 100;
   const int width = 1000;
   const int height = 750;

   StarSystemWindow::StarSystemWindow(WindowContext context, BaseWindowPtr parentWnd)
   {
      m_mainPain = parentWnd->Create<Pane>(context.graphics, graphics::Rect{ leftX, topY, width, height },
         "images/galaxy_screen/frame/metal_frame.png");
      m_windows.push_back(m_mainPain);

      ImageButton::Theme theme =
      {
         .hoveredImageName = "images/galaxy_screen/frame/close_hovered.png",
         .enabledImageName = "images/galaxy_screen/frame/close_enabled.png",
      };

      auto onPressed = [this]() { m_mainPain->Hide(); };
      auto closeButton = m_mainPain->Create<ImageButton>(context, ImageButton::State::Enabled, std::move(theme),
         graphics::Point{ leftX + width - 24 - 7, topY + 7 }, onPressed);
      m_windows.push_back(closeButton);

      createOrbits(context);
      createPlanets(context);
   }

   bool StarSystemWindow::IsVisible() const
   {
      return m_mainPain->IsVisible();
   }

   namespace
   {
      const auto size1 = Size{ 150, 75 };
      const auto size2 = Size{ 300, 150 };
      const auto size3 = Size{ 450, 225 };
      const auto size4 = Size{ 600, 300 };
      const auto size5 = Size{ 750, 375 };
      const auto size6 = Size{ 900, 450 };
      const Point center{ leftX + width / 2, topY + height / 2 };
   }

   void StarSystemWindow::createOrbits(const WindowContext& context)
   {

      auto imageName1 = "images/galaxy_screen/orbits/orbit1.png";
      auto imageName2 = "images/galaxy_screen/orbits/orbit2.png";
      auto imageName3 = "images/galaxy_screen/orbits/orbit3.png";
      auto imageName4 = "images/galaxy_screen/orbits/orbit3.png";
      auto imageName5 = "images/galaxy_screen/orbits/orbit3.png";
      auto imageName6 = "images/galaxy_screen/orbits/orbit3.png";

      auto orbit6 = m_mainPain->Create<Image>(context,
         Point(center.x - size6.w / 2, center.y - size6.h / 2), size6, imageName6);
      m_windows.push_back(orbit6);

      auto orbit5 = m_mainPain->Create<Image>(context,
         Point(center.x - size5.w / 2, center.y - size5.h / 2), size5, imageName5);
      m_windows.push_back(orbit5);

      auto orbit4 = m_mainPain->Create<Image>(context,
         Point(center.x - size4.w / 2, center.y - size4.h / 2), size4, imageName4);
      m_windows.push_back(orbit4);

      auto orbit3 = m_mainPain->Create<Image>(context,
         Point(center.x - size3.w / 2, center.y - size3.h / 2), size3, imageName3);
      m_windows.push_back(orbit3);

      auto orbit2 = m_mainPain->Create<Image>(context,
         Point(center.x - size2.w/2, center.y - size2.h/2), size2, imageName2);
      m_windows.push_back(orbit2);

      auto orbit1 = m_mainPain->Create<Image>(context,
         Point(center.x - size1.w / 2, center.y - size1.h/2), size1, imageName1);
      m_windows.push_back(orbit1);

      auto starImageName = "images/stars/blue.png";

      auto starImage = m_mainPain->Create<Image>(context,
         Point(center.x - 16, center.y - 16), std::nullopt, starImageName);
      m_windows.push_back(starImage);
   }

   void StarSystemWindow::createPlanets(const windows::WindowContext& context)
   {
      auto planetImageName = "images/planets/gas_giant1.png";

      auto planet1 = m_mainPain->Create<Image>(context,
         Point(center.x - 16 - size1.w/2, center.y - 16), Size{ 32, 32 }, planetImageName);
      m_windows.push_back(planet1);

      auto planet2 = m_mainPain->Create<Image>(context,
         Point(center.x - 24 - size2.w / 2, center.y - 24), Size{48, 48}, planetImageName);
      m_windows.push_back(planet2);

      auto planet3 = m_mainPain->Create<Image>(context,
         Point(center.x - 32 - size3.w / 2, center.y - 32), Size{ 64, 64 }, planetImageName);
      m_windows.push_back(planet3);

      auto planet4 = m_mainPain->Create<Image>(context,
         Point(center.x - 12 - size4.w / 2, center.y - 12), Size{ 24, 24 }, planetImageName);
      m_windows.push_back(planet4);

      auto planet5 = m_mainPain->Create<Image>(context,
         Point(center.x - 9 - size5.w / 2, center.y - 9), Size{ 18, 18 }, planetImageName);
      m_windows.push_back(planet5);
   }

   void StarSystemWindow::Show() { m_mainPain->Show(); }
   void StarSystemWindow::Hide() { m_mainPain->Hide(); }

}