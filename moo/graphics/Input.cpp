#include "Input.h"

#include <SDL3/SDL.h>

namespace input
{

   void Input::RegisterCallback(IInputCallbackPtr callback)
   {
      m_callback = callback;
   }

   IEnvironment::RunResult Input::Poll()
   {
      SDL_Event event{};
      if (!SDL_PollEvent(&event))
      {
         return IEnvironment::RunResult::Continue;
      }

      if (event.type == SDL_EVENT_QUIT)
         return IEnvironment::RunResult::Quit;

      auto callback = m_callback.lock();
      if (!callback)
         return IEnvironment::RunResult::Continue;

      switch (event.type)
      {
      case SDL_EVENT_QUIT:
         break;

      case SDL_EVENT_MOUSE_MOTION:
         callback->OnMouseMove((int)event.motion.x, (int)event.motion.y);
         break;

      case SDL_EVENT_MOUSE_BUTTON_DOWN:
         callback->OnMouseButtonPressed(IInputCallback::Pressed::Down, IInputCallback::Button::Left, (int)event.button.x, (int)event.button.y);
         break;

      case SDL_EVENT_MOUSE_BUTTON_UP:
         callback->OnMouseButtonPressed(IInputCallback::Pressed::Up, IInputCallback::Button::Left, (int)event.button.x, (int)event.button.y);
         break;

      default:
         break;
      }

      return IEnvironment::RunResult::Continue;
   }

}