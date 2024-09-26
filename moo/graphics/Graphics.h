#pragma once

#include "../interfaces/IGraphics.h"
#include "SdlTypes.h"

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "SDL3_ttf/SDL_ttf.h"

#include <memory>
#include <map>

namespace graphics
{
   inline bool operator < (const FontMetrics& left, const FontMetrics& right) noexcept
   {
      return std::tie(left.fontName, left.size) <
         std::tie(right.fontName, right.size);
   }
}

namespace graphics::sdl
{

struct GraphicsContext
{
   std::u8string m_rootFilePath;
   int m_windowWidth;
   int m_windowHeight;
};



class Graphics: public IGraphics
              , private GraphicsContext
{
public:

   explicit Graphics(GraphicsContext context);
   ~Graphics() override;

   ITexturePtr CreateTextureFromFile(const std::string& fileName) override;
   ITexturePtr CreateTextureFromText(const std::u8string& text, const FontMetrics& fontMetrics, const Color& cl) override;

   void BeginDraw() override;
   void EndDraw() override;

   void SetCursor(const std::string& fileName) override;

   RunResult Run() override;
private:

   using InitGuard = std::unique_ptr<const void, void(*)(const void*)>;

   InitGuard m_initSdlGuard = InitGuard{nullptr, nullptr};
   InitGuard m_initImgGuard = InitGuard{ nullptr, nullptr };
   InitGuard m_initTtfGuard = InitGuard{ nullptr, nullptr };

   SDL_WindowPtr m_window;
   SDL_RendererPtr m_renderer;

   SDL_CursorPtr m_cursor;

   //using FontKey = std::pair<std::string, int>;
   using FontMap = std::map<FontMetrics, TTF_FontPtr>;

   FontMap m_availableFonts;
};

}
