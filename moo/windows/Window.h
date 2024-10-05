#pragma once

#include "../interfaces/Types.h"
#include "../interfaces/IInput.h"
#include "../interfaces/InterfaceFwd.h"

#include <memory>
#include <list>
#include <functional>
#include <chrono>

namespace windows
{

class IWindow;
using IWindowPtr = std::shared_ptr<IWindow>;
using IWindowWeakPtr = std::weak_ptr<IWindow>;

class IWindow
{
public:
   virtual ~IWindow() = default;

   virtual void Draw() = 0;
};

class IWindowEnvironment
{
public:
   virtual ~IWindowEnvironment() = default;
   virtual graphics::Rect GetClientRect() const = 0;

   using TimerHandle = std::shared_ptr<void>;
   using OnTimer = std::function<void()>;
   virtual TimerHandle CreateTimer(std::chrono::milliseconds period, OnTimer&& onTimer) = 0;
};

using IWindowEnvironmentPtr = std::shared_ptr<IWindowEnvironment>;

struct WindowContext
{
   IWindowEnvironmentPtr environment;
   graphics::IGraphicsPtr graphics;
};

class BaseWindow;
using BaseWindowPtr = std::shared_ptr<BaseWindow>;
using BaseWindowWeakPtr = std::weak_ptr<BaseWindow>;

class BaseWindow: public IWindow
                , public std::enable_shared_from_this<BaseWindow>
{
public:
   template<typename WindowType, typename... Args>
   std::shared_ptr<WindowType> Create(Args&&... args);

   using WindowVisitor = std::function<void(const BaseWindowPtr&)>;
   void EnumerateChildWindows(const WindowVisitor& visitor);

   virtual graphics::Rect GetRect() const = 0;

   virtual void MoveTo(const graphics::Point& /*topLeft*/) {}
   void Show() { m_isVisible = true; }
   void Hide() { m_isVisible = false; }
   bool IsVisible() const { return m_isVisible;  }

   enum class HandleResult
   {
      Handled,
      Continue,
   };

   virtual HandleResult OnMouseMove(int /*x*/, int /*y*/)
      { return HandleResult::Continue; }

   virtual HandleResult OnMouseButtonPressed(input::IInputCallback::Pressed /*pressed*/,
      input::IInputCallback::Button /*button*/, int /*x*/, int /*y*/)
      { return HandleResult::Continue; }

   enum class HoverState
   {
      Away,
      Above
   };

   virtual HandleResult OnMouseHover(HoverState /*state*/)
   {
      return HandleResult::Continue;
   }

protected:
   void addChild(const BaseWindowWeakPtr& child);
   void setParent(const BaseWindowWeakPtr& child) { m_parent = child; }

private:
   BaseWindowWeakPtr m_parent;
   std::list<BaseWindowWeakPtr> m_childWindows;
   std::vector<BaseWindowPtr> m_enumeratedWindows;
   bool m_isVisible = true;
};

template<typename WindowType, typename... Args>
inline std::shared_ptr<WindowType> BaseWindow::Create(Args&&... args)
{
   std::shared_ptr<WindowType> newWindow(new WindowType(std::forward<Args>(args)...));
   addChild(newWindow);
   newWindow->setParent(this->weak_from_this());
   return newWindow;
}

}
