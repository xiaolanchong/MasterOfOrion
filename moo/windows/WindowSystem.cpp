#include "WindowSystem.h"
#include "../interfaces/Utils.h"
#include <cassert>

namespace windows
{

   void WindowSystem::OnMouseMove(int x, int y)
   {
      BaseWindowPtr hoveredWindow;
      deepFirstSearch([&](const BaseWindowPtr& window)
         {
            auto rc = window->GetRect();
            if (graphics::IsInRect(x, y, rc))
            {
// if(!hoveredWindow)
                  hoveredWindow = window;
               if (window->OnMouseMove(x, y) == BaseWindow::HandleResult::Handled)
                  return VisitResult::Quit;
            }
            return VisitResult::Continue;
         });

      auto currentHoveredWindow = m_currentHoveredWindow.lock();
      if (currentHoveredWindow)
      {
         if (currentHoveredWindow != hoveredWindow)
         {
            currentHoveredWindow->OnMouseHover(BaseWindow::HoverState::Away);
            if (hoveredWindow)
               hoveredWindow->OnMouseHover(BaseWindow::HoverState::Above);
            m_currentHoveredWindow = hoveredWindow;
         }
      }
      else if (hoveredWindow)
      {
         hoveredWindow->OnMouseHover(BaseWindow::HoverState::Above);
         m_currentHoveredWindow = hoveredWindow;
      }
   }

   void WindowSystem::OnMouseButtonPressed(Pressed pressed, Button button, int x, int y)
   {
      deepFirstSearch([&](const BaseWindowPtr& window)
         {
            auto rc = window->GetRect();
            if (graphics::IsInRect(x, y, rc))
            {
               if (window->OnMouseButtonPressed(pressed, button, x, y) == BaseWindow::HandleResult::Handled)
                  return VisitResult::Quit;
            }
            return VisitResult::Continue;
         });
   }

   void WindowSystem::SetClientSize(int width, int height)
   {
      m_screenWidth = width;
      m_screenHeight = height;
   }

   void WindowSystem::Draw()
   {
      breadthFirstSearch([](const BaseWindowPtr& window)
         {
            window->Draw();
            return VisitResult::Continue;
         });
   }

   void WindowSystem::breadthFirstSearch(const Visitor& visitor)
   {
      assert(m_enumerateQueue.empty());

      for (auto topWindowWeak : m_topWindows)
         if (auto topWindow = topWindowWeak.lock())
            m_enumerateQueue.push(topWindow);
      while (!m_enumerateQueue.empty())
      {
         auto window = m_enumerateQueue.front();
         m_enumerateQueue.pop();
         if (visitor(window) == VisitResult::Quit)
            break;
         window->EnumerateChildWindows([this](const BaseWindowPtr& window) { m_enumerateQueue.push(window); });
      }

      while (!m_enumerateQueue.empty())
         m_enumerateQueue.pop();
   }

   void WindowSystem::deepFirstSearch(const Visitor& visitor)
   {
      assert(m_enumerateStack.empty());
      for (auto topWindowWeak : m_topWindows)
         if (auto topWindow = topWindowWeak.lock())
            m_enumerateStack.push(topWindow);
      while (!m_enumerateStack.empty())
      {
         auto window = m_enumerateStack.top();
         m_enumerateStack.pop();
         if (visitor(window) == VisitResult::Quit)
            break;
         window->EnumerateChildWindows([this](const BaseWindowPtr& window) { m_enumerateStack.push(window); });
      }

      while (!m_enumerateStack.empty())
         m_enumerateStack.pop();
   }
}