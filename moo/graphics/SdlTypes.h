#pragma once

#include <memory>

struct SDL_Surface;
struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Window;
struct SDL_Cursor;

struct TTF_Font;

namespace graphics::sdl
{
   using SDL_SurfacePtr = std::shared_ptr<SDL_Surface>;
   using SDL_TexturePtr = std::shared_ptr<SDL_Texture>;
   using SDL_RendererPtr = std::shared_ptr<SDL_Renderer>;
   using SDL_WindowPtr = std::shared_ptr< SDL_Window>;
   using SDL_CursorPtr = std::shared_ptr< SDL_Cursor>;

   using TTF_FontPtr = std::shared_ptr< TTF_Font>;
}