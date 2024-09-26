#include "Texture.h"

#include <SDL3/SDL.h>

namespace graphics::sdl
{
   bool Texture::Draw(const Rect& area)
   {
      SDL_FRect textLocation = { .x = (float)area.x, .y = (float)area.y, .w = (float)area.w, .h = (float)area.h };
      return SDL_RenderTexture(m_renderer.get(), m_texture.get(), nullptr, &textLocation);
   }

   bool Texture::Draw(int x, int y)
   {
      SDL_FRect textLocation = { .x = (float)x, .y = (float)y, .w = (float)m_width, .h = (float)m_height };
      return SDL_RenderTexture(m_renderer.get(), m_texture.get(), nullptr, &textLocation);
   }
}
