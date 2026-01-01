
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../windows/WindowSystem.h"
#include "../windows/Window.h"
#include "MockWindow.h"

using namespace windows;
using namespace graphics;
using namespace ::testing;

TEST(WindowSubsystem, HoverOneWindow)
{
   WindowSystem ws;
   ws.SetClientSize(800, 600);

   auto wnd1 = ws.Create<StrictMock<MockWindow>>();
   auto& inputCb = static_cast<input::IInputCallback&>(ws);

   const graphics::Rect rect{ .x = 100, .y = 100, .w = 200, .h = 100 };

   InSequence s;
   EXPECT_CALL(*wnd1, GetRect())
      .Times(1)
      .WillRepeatedly(Return(rect));
   inputCb.OnMouseMove(50, 50);

   EXPECT_CALL(*wnd1, GetRect())
      .Times(1)
      .WillRepeatedly(Return(rect));
   EXPECT_CALL(*wnd1, OnMouseHover(BaseWindow::HoverState::Above))
      .Times(1)
      .WillOnce(Return(BaseWindow::HandleResult::Handled));
   inputCb.OnMouseMove(150, 150);

   EXPECT_CALL(*wnd1, GetRect())
      .Times(1)
      .WillRepeatedly(Return(rect));
   inputCb.OnMouseMove(200, 170);

   EXPECT_CALL(*wnd1, GetRect())
      .Times(1)
      .WillRepeatedly(Return(rect));
   EXPECT_CALL(*wnd1, OnMouseHover(BaseWindow::HoverState::Away))
      .Times(1)
      .WillRepeatedly(Return(BaseWindow::HandleResult::Handled));
   inputCb.OnMouseMove(400, 170);
}

TEST(WindowSubsystem, HoverOverlappedWindow)
{
   WindowSystem ws;
   auto& inputCb = static_cast<input::IInputCallback&>(ws);
   ws.SetClientSize(800, 600);

   const graphics::Rect wndRect1{ .x = 100, .y = 100, .w = 200, .h = 100 };
   const graphics::Rect wndRect2{ .x = 150, .y = 150, .w = 200, .h = 100 };
   auto wnd1 = ws.Create<StrictMock<MockWindow>>();
   auto wnd2 = ws.Create<StrictMock<MockWindow>>();

   EXPECT_CALL(*wnd1, GetRect())
      .Times(1)
      .WillRepeatedly(Return(wndRect1));
   EXPECT_CALL(*wnd2, GetRect())
      .Times(1)
      .WillRepeatedly(Return(wndRect2));
 
   EXPECT_CALL(*wnd1, OnMouseHover(BaseWindow::HoverState::Above))
      .Times(1)
      .WillOnce(Return(BaseWindow::HandleResult::Handled));
   inputCb.OnMouseMove(125, 125);

   EXPECT_CALL(*wnd1, GetRect())
      .Times(1)
      .WillRepeatedly(Return(wndRect1));
   EXPECT_CALL(*wnd2, GetRect())
      .Times(1)
      .WillRepeatedly(Return(wndRect2));

   EXPECT_CALL(*wnd1, OnMouseHover(BaseWindow::HoverState::Away))
      .Times(1)
      .WillOnce(Return(BaseWindow::HandleResult::Handled));
   EXPECT_CALL(*wnd2, OnMouseHover(BaseWindow::HoverState::Above))
      .Times(1)
      .WillOnce(Return(BaseWindow::HandleResult::Handled));
   inputCb.OnMouseMove(160, 160);
}

TEST(WindowSubsystem, HoverChildWindow)
{
   WindowSystem ws;
   ws.SetClientSize(800, 600);
   auto& inputCb = static_cast<input::IInputCallback&>(ws);

   const graphics::Rect wndRect1{ .x = 0, .y = 0, .w = 700, .h = 500 };
   const graphics::Rect wndRect2{ .x = 150, .y = 150, .w = 200, .h = 100 };

   auto parent = ws.Create<StrictMock<MockWindow>>();
   auto child = parent->Create<StrictMock<MockWindow>>();

   EXPECT_CALL(*parent, GetRect())
      .Times(1)
      .WillRepeatedly(Return(wndRect1));
   EXPECT_CALL(*child, GetRect())
      .Times(1)
      .WillRepeatedly(Return(wndRect2));
   EXPECT_CALL(*parent, OnMouseHover(BaseWindow::HoverState::Above))
      .Times(1)
      .WillOnce(Return(BaseWindow::HandleResult::Handled));
   inputCb.OnMouseMove(125, 125);
   
   EXPECT_CALL(*parent, GetRect())
      .Times(1)
      .WillRepeatedly(Return(wndRect1));
   EXPECT_CALL(*child, GetRect())
      .Times(1)
      .WillRepeatedly(Return(wndRect2));
   EXPECT_CALL(*parent, OnMouseHover(BaseWindow::HoverState::Away))
      .Times(1)
      .WillOnce(Return(BaseWindow::HandleResult::Handled));
   EXPECT_CALL(*child, OnMouseHover(BaseWindow::HoverState::Above))
      .Times(1)
      .WillOnce(Return(BaseWindow::HandleResult::Handled));
   inputCb.OnMouseMove(160, 160);
}

TEST(WindowSubsystem, HoverHiddenWindow)
{
   WindowSystem ws;
   ws.SetClientSize(800, 600);
   auto& inputCb = static_cast<input::IInputCallback&>(ws);

   const graphics::Rect wndRect1{ .x = 100, .y = 100, .w = 700, .h = 500 };
   const graphics::Rect wndRect2{ .x = 50, .y = 50, .w = 200, .h = 100 };

   auto parent = ws.Create<StrictMock<MockWindow>>();
   auto child = parent->Create<StrictMock<MockWindow>>();

   child->Hide();

   EXPECT_CALL(*parent, GetRect())
      .Times(1)
      .WillRepeatedly(Return(wndRect1));
   EXPECT_CALL(*parent, OnMouseHover(BaseWindow::HoverState::Above))
      .Times(1)
      .WillOnce(Return(BaseWindow::HandleResult::Handled));
   inputCb.OnMouseMove(125, 125);

   EXPECT_CALL(*parent, GetRect())
      .Times(1)
      .WillRepeatedly(Return(wndRect1));
   inputCb.OnMouseMove(160, 160);
}

TEST(WindowSubsystem, Draw)
{
   WindowSystem ws;
   ws.SetClientSize(800, 600);

   const Rect wndRect1{ .x = 110, .y = 100, .w = 700, .h = 500 };
   const Rect wndRect2{ .x = 30, .y = 50, .w = 500, .h = 300 };
   const Rect wndRect3{ .x = 10, .y = 5, .w = 200, .h = 98 };

   auto parent = ws.Create<StrictMock<MockWindow>>();
   auto child = parent->Create<StrictMock<MockWindow>>();
   auto grandchild = child->Create<StrictMock<MockWindow>>();

   InSequence s;
   EXPECT_CALL(*parent, GetRect())
      .Times(1)
      .WillRepeatedly(Return(wndRect1));
   EXPECT_CALL(*parent, Draw(Point{ 0, 0 }))
      .Times(1);

   EXPECT_CALL(*child, GetRect())
      .Times(1)
      .WillRepeatedly(Return(wndRect2));
   EXPECT_CALL(*child, Draw(Point{ wndRect1.x, wndRect1.y }))
      .Times(1);

   EXPECT_CALL(*grandchild, GetRect())
      .Times(1)
      .WillRepeatedly(Return(wndRect3));
   EXPECT_CALL(*grandchild, Draw(Point{ wndRect1.x + wndRect2.x, wndRect1.y + wndRect2.y }))
      .Times(1);

   ws.Draw();
}