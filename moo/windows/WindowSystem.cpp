#include "WindowSystem.h"
#include "StdTimeService.h"
#include "../interfaces/Utils.h"
#include <cassert>

namespace windows
{
   WindowSystem::WindowSystem(zeit::ITimeServicePtr timeService)
      : m_timerFactory(timeService ? std::move(timeService) : zeit::ITimeServicePtr(std::make_shared<zeit::StdTimeService>()))
   {
   }

   void WindowSystem::OnMouseMove(int x, int y)
   {
      BaseWindowPtr hoveredWindow;
      deepFirstSearch([&](const BaseWindowPtr& window, const graphics::Point& parentOffsetFromScreen, const graphics::Rect& windowRect)
         {
            const graphics::Point pt{ x - parentOffsetFromScreen.x, y - parentOffsetFromScreen.y };
            if (graphics::IsInRect(pt.x, pt.y, windowRect))
            {
               hoveredWindow = window;
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
      deepFirstSearch([&](const BaseWindowPtr& window, const graphics::Point& parentOffsetFromScreen, const graphics::Rect& windowRect)
         {
            const graphics::Point pt{ x - parentOffsetFromScreen.x, y - parentOffsetFromScreen.y };
            if (graphics::IsInRect(pt.x, pt.y, windowRect))
            {
               if (window->OnMouseButtonPressed(pressed, button, pt.x - windowRect.x, pt.y - windowRect.y) == BaseWindow::HandleResult::Handled)
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
      breadthFirstSearch([](const BaseWindowPtr& window, const graphics::Point& offsetFromScreen, const graphics::Rect&)
         {
            window->Draw(offsetFromScreen);
            return VisitResult::Continue;
         });
   }

   void WindowSystem::PreDraw()
   {
      m_timerFactory.OnTick();
   }

   IWindowEnvironment::TimerHandle WindowSystem::CreateTimer(std::chrono::milliseconds period, OnTimer&& onTimer)
   {
      return m_timerFactory.CreateTimer(period, std::move(onTimer));
   }

   void WindowSystem::breadthFirstSearch(const Visitor& visitor)
   {
      assert(m_enumerateQueue.empty());

      for (auto topWindowWeak : m_topWindows)
         if (auto topWindow = topWindowWeak.lock())
            m_enumerateQueue.push({ topWindow, {0, 0}, topWindow->GetRect()});
      while (!m_enumerateQueue.empty())
      {
         auto item = m_enumerateQueue.front();
         m_enumerateQueue.pop();
         if (!item.window->IsVisible())
         {
            continue;
         }
         if (visitor(item.window, item.offsetFromScreen, item.windowRect) == VisitResult::Quit)
            break;
         const graphics::Rect rect = item.windowRect;
         const graphics::Point offsetForChild = { rect.x + item.offsetFromScreen.x, rect.y + item.offsetFromScreen.y };
         item.window->EnumerateChildWindows([&](const BaseWindowPtr& childWindow)
            {
               if (childWindow->IsVisible())
                  m_enumerateQueue.push({ childWindow, offsetForChild, childWindow->GetRect() });
            });
      }

      while (!m_enumerateQueue.empty())
         m_enumerateQueue.pop();
   }

   void WindowSystem::deepFirstSearch(const Visitor& visitor)
   {
      assert(m_enumerateStack.empty());
      for (auto topWindowWeak : m_topWindows)
         if (auto topWindow = topWindowWeak.lock())
            m_enumerateStack.push({ topWindow, ChildrenAdded::NotYet, {0, 0}, topWindow->GetRect()});
      while (!m_enumerateStack.empty())
      {
         auto& [window, childrenAdded, offsetFromScreen, windowRect] = m_enumerateStack.top();
         if (!window->IsVisible())
         {
            m_enumerateStack.pop();
         }
         else if (childrenAdded == ChildrenAdded::Yes)
         {
            m_enumerateStack.pop();
            if (visitor(window, offsetFromScreen, windowRect) == VisitResult::Quit)
               break;
         }
         else
         {
            childrenAdded = ChildrenAdded::Yes;
            const graphics::Point offsetForChild = { windowRect.x + offsetFromScreen.x, windowRect.y + offsetFromScreen.y };
            BaseWindowPtr(window)->EnumerateChildWindows([&](const BaseWindowPtr& childWindow)
            {
               if (childWindow->IsVisible())
                  m_enumerateStack.push({ childWindow, ChildrenAdded::NotYet, offsetForChild, childWindow->GetRect()});
            });
         }
      }

      while (!m_enumerateStack.empty())
         m_enumerateStack.pop();
   }


}