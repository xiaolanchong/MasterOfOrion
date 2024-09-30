#pragma once

#include <functional>
#include <memory>

namespace input
{
   class IInputCallback
   {
   public:
      virtual ~IInputCallback() = default;

      virtual void OnMouseMove(int x, int y) = 0;

      enum class Pressed
      {
         Down,
         Up,
      };

      enum class Button
      {
         Left,
         Middle,
         Right,
      };
      virtual void OnMouseButtonPressed(Pressed pressed, Button button, int x, int y) = 0;
   };

   using IInputCallbackPtr = std::shared_ptr<IInputCallback>;
   using IInputCallbackWeakPtr = std::weak_ptr<IInputCallback>;

   class IInput
   {
   public:
      virtual ~IInput() = default;

      virtual void RegisterCallback(IInputCallbackPtr callback) = 0;
   };

   using IInputPtr = std::shared_ptr<IInput>;

}