#pragma once

#include "../interfaces/Types.h"
#include "../interfaces/ITexture.h"
#include "SdlTypes.h"

namespace graphics::sdl
{

class Texture: public ITexture
{
public:
   Texture(SDL_RendererPtr renderer, SDL_TexturePtr texture,
          int width, int height)
      : m_texture(std::move(texture))
      , m_renderer(std::move(renderer))
      , m_width(width)
      , m_height(height)
   {}

   bool Draw(const Rect& area) override;
   bool Draw(int x, int y) override;

private:
   SDL_TexturePtr m_texture;
   SDL_RendererPtr m_renderer;
   int m_width = 0;
   int m_height = 0;
};

}