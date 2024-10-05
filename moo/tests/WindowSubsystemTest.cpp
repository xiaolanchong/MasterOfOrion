
#include <gtest/gtest.h>

#include "../windows/WindowSystem.h"
#include "../windows/Window.h"

using namespace windows;

namespace
{
   class TestWindow : public BaseWindow
   {
      friend class WindowSystem;
      friend class BaseWindow;
   public:

      TestWindow(graphics::Rect rc) : m_rc(std::move(rc)) {}

      void Draw() override {}
      graphics::Rect GetRect() const override { return m_rc; }
      HandleResult OnMouseHover(HoverState state) override
      {
         m_state = state;
         return HandleResult::Handled;
      }

      bool IsHovered() const { return m_state == HoverState::Above; }

   private:
      graphics::Rect m_rc;
      HoverState m_state = HoverState::Away;
   };
}

TEST(WindowSubsystem, HoverOneWindow)
{
   WindowSystem ws;
   ws.SetClientSize(800, 600);

   auto wnd1 = ws.Create<TestWindow>(graphics::Rect{ .x = 100, .y = 100, .w = 200, .h = 100 });
   auto& inputCb = static_cast<input::IInputCallback&>(ws);

   EXPECT_FALSE(wnd1->IsHovered());

   inputCb.OnMouseMove(50, 50);
   EXPECT_FALSE(wnd1->IsHovered());

   inputCb.OnMouseMove(150, 150);
   EXPECT_TRUE(wnd1->IsHovered());

   inputCb.OnMouseMove(200, 170);
   EXPECT_TRUE(wnd1->IsHovered());

   inputCb.OnMouseMove(400, 170);
   EXPECT_FALSE(wnd1->IsHovered());
}

TEST(WindowSubsystem, HoverOverlappedWindow)
{
   WindowSystem ws;
   ws.SetClientSize(800, 600);

   auto wnd1 = ws.Create<TestWindow>(graphics::Rect{ .x = 100, .y =100, .w = 200, .h = 100 });
   auto wnd2 = ws.Create<TestWindow>(graphics::Rect{ .x = 150, .y = 150, .w = 200, .h = 100 });

   auto& inputCb = static_cast<input::IInputCallback&>(ws);

   inputCb.OnMouseMove(125, 125);
   EXPECT_TRUE(wnd1->IsHovered());
   EXPECT_FALSE(wnd2->IsHovered());

   inputCb.OnMouseMove(160, 160);
   EXPECT_FALSE(wnd1->IsHovered());
   EXPECT_TRUE(wnd2->IsHovered());
}

TEST(WindowSubsystem, HoverChildWindow)
{
   WindowSystem ws;
   ws.SetClientSize(800, 600);

   auto parent = ws.Create<TestWindow>(graphics::Rect{ .x = 0, .y = 0, .w = 700, .h = 500 });
   auto child = parent->Create<TestWindow>(graphics::Rect{ .x = 150, .y = 150, .w = 200, .h = 100 });

   auto& inputCb = static_cast<input::IInputCallback&>(ws);

   inputCb.OnMouseMove(125, 125);
   EXPECT_TRUE(parent->IsHovered());
   EXPECT_FALSE(child->IsHovered());

   inputCb.OnMouseMove(160, 160);
   EXPECT_FALSE(parent->IsHovered());
   EXPECT_TRUE(child->IsHovered());
}
