#pragma once

#include "../../windows/Window.h"
#include <vector>

namespace game::ui
{

   class StarSystemWindow
   {
   public:
      StarSystemWindow(windows::WindowContext context, windows::BaseWindowPtr parentWnd);

      bool IsVisible() const;
      void Show();
      void Hide();

   private:
      void createOrbits(const windows::WindowContext& context);
      void createPlanets(const windows::WindowContext& context);
   private:
      std::vector<windows::BaseWindowPtr> m_windows;
      windows::BaseWindowPtr m_mainPain;
   };

}