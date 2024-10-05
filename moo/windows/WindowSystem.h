#pragma once

#include "../interfaces/IInput.h"
#include "../interfaces/IGraphics.h"
#include "Window.h"
#include "TimerFactory.h"

#include <queue>
#include <stack>

namespace windows
{

class WindowSystem: public input::IInputCallback
                  , public IWindowEnvironment
{
public:
   explicit WindowSystem(zeit::ITimeServicePtr timeService = nullptr);

   void SetClientSize(int width, int height);
   void Draw();
   void PreDraw();

   //void DestroyWindows() { m_topWindows.clear(); }

   template<typename WindowType, typename... Args>
   std::shared_ptr<WindowType> Create(Args&&... args);

private:
   void OnMouseMove(int x, int y) override;
   void OnMouseButtonPressed(Pressed pressed, Button button, int x, int y) override;

   graphics::Rect GetClientRect() const override
      { return { .x = 0, .y = 0, .w = m_screenWidth, .h = m_screenHeight }; }
   TimerHandle CreateTimer(std::chrono::milliseconds period, OnTimer&& onTimer) override;

   enum class VisitResult
   {
      Continue,
      Quit,
   };
   using Visitor = std::function<VisitResult(const BaseWindowPtr& window)>;
   void breadthFirstSearch(const Visitor& visitor);
   void deepFirstSearch(const Visitor& visitor);
private:
   int m_screenWidth = 0;
   int m_screenHeight = 0;

   BaseWindowWeakPtr m_currentHoveredWindow;

   std::list<BaseWindowWeakPtr> m_topWindows;
   std::queue<BaseWindowPtr> m_enumerateQueue;
   enum class ChildrenAdded
   {
      Yes,
      NotYet
   };
   std::stack<std::pair<BaseWindowPtr, ChildrenAdded>> m_enumerateStack;

   TimerFactory m_timerFactory;
};

template<typename WindowType, typename... Args>
inline std::shared_ptr<WindowType> WindowSystem::Create(Args&&... args)
{
   std::shared_ptr<WindowType> newWindow(new WindowType(std::forward<Args>(args)...));
   m_topWindows.push_back(newWindow);
   return newWindow;
}

}