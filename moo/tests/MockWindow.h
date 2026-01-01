#pragma once

#include "../windows/Window.h"

class MockWindow : public windows::BaseWindow
{
public:
   MOCK_METHOD(HandleResult, OnMouseMove, (int x, int y), (override));
   MOCK_METHOD(HandleResult, OnMouseButtonPressed, (input::IInputCallback::Pressed pressed,
      input::IInputCallback::Button button, int x, int y), (override));
   MOCK_METHOD(HandleResult, OnMouseHover, (HoverState state), (override));

   MOCK_METHOD(void, Draw, (const graphics::Point&), (override));
   MOCK_METHOD(graphics::Rect, GetRect, (), (const override));
};
