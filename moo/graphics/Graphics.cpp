#include "Graphics.h"
#include "Texture.h"

#include <glog/logging.h>

#include <stdexcept>
#include <format>
#include <filesystem>

namespace graphics::sdl
{

namespace
{
   SDL_TexturePtr loadTextureFromFile(const std::string& fileName, SDL_Renderer* renderer, int& w, int& h)
   {
      SDL_Surface* loadedSurface = IMG_Load(fileName.c_str());
      if (loadedSurface == nullptr)
      {
         SDL_Log("Unable to load image %s! SDL_image Error: %s\n", fileName.c_str(), SDL_GetError());
         return nullptr;
      }
      else
      {
         w = loadedSurface->w;
         h = loadedSurface->h;
         auto texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
         if (!texture)
         {
            SDL_Log("Unable to optimize image %s! SDL Error: %s\n", fileName.c_str(), SDL_GetError());
         }
         SDL_DestroySurface(loadedSurface);
         return SDL_TexturePtr(texture, &SDL_DestroyTexture);
      }
   }
}

Graphics::Graphics(GraphicsContext context)
   : GraphicsContext(std::move(context))
{
   if (!SDL_Init(SDL_INIT_VIDEO))
   {
      LOG(ERROR) << "SDL could not initialize! SDL error: " << SDL_GetError();
      throw std::runtime_error(std::format("SDL could not initialize! SDL error: %s", SDL_GetError()));
   }

   static const int dummy = 0;
   m_initSdlGuard = InitGuard(&dummy, [](auto) {SDL_Quit(); });

   if (!TTF_Init())
   {
      throw std::runtime_error(std::format("TTF could not initialize! TTF error: %s", SDL_GetError()));
   }

   m_initTtfGuard = InitGuard(&dummy, [](auto) { TTF_Quit(); });

   const int flags = IMG_INIT_PNG;
   if (!(IMG_Init(flags) & flags))
   {
      throw std::runtime_error(std::format("SDL_image could not initialize! SDL_image error: %s", SDL_GetError()));
   }

   m_initImgGuard = {&dummy, [](auto) { IMG_Quit(); }};

   SDL_Window* window = nullptr;
   SDL_Renderer* renderer = nullptr;
   const uint64_t wflags = SDL_WINDOW_MOUSE_FOCUS | SDL_WINDOW_INPUT_FOCUS;
   if (!SDL_CreateWindowAndRenderer("MoO2:Re", m_windowWidth, m_windowHeight, wflags, &window, &renderer))
   {
      throw std::runtime_error(std::format("Could not create the main window! SDL error: %s", SDL_GetError()));
   }

   m_window = SDL_WindowPtr{ window, &SDL_DestroyWindow };
   m_renderer = SDL_RendererPtr{ renderer, &SDL_DestroyRenderer };
}

Graphics::~Graphics()
{

}

ITexturePtr Graphics::CreateTextureFromFile(const std::string& fileName)
{
   std::filesystem::path rootPath(m_rootFilePath);
   auto imagePath = rootPath / fileName;

   int w = 0;
   int h = 0;
   auto texture = loadTextureFromFile(imagePath.string(), m_renderer.get(), w, h);
   return std::make_shared<Texture>(m_renderer, std::move(texture), w, h);
}

ITexturePtr Graphics::CreateTextureFromText(const std::u8string& text, const FontMetrics& fontMetrics, const Color& cl)
{
   auto it = m_availableFonts.find(fontMetrics);
   TTF_FontPtr font;
   if (it == m_availableFonts.end())
   {
      std::filesystem::path rootPath(m_rootFilePath);
      auto fontPath = rootPath / u8"fonts" / (fontMetrics.fontName + ".otf");
      if (!std::filesystem::exists(fontPath))
      {
         fontPath = rootPath / u8"fonts" / (fontMetrics.fontName + ".ttf");
         if (!std::filesystem::exists(fontPath))
         {
            SDL_Log("Can't locate font %s", fontMetrics.fontName.c_str());
            throw std::runtime_error(std::format("Can't locate font %s", fontMetrics.fontName));
         }
      }

      font = { TTF_OpenFont((const char*)fontPath.u8string().c_str(), fontMetrics.size), &TTF_CloseFont };
      if (!font)
      {
         SDL_Log("Can't create font %s, %d pt", fontMetrics.fontName.c_str(), fontMetrics.size);
         throw std::runtime_error(std::format("Can't create font %s, %d pt", fontMetrics.fontName, fontMetrics.size));
      }

      m_availableFonts.emplace(fontMetrics, font);
   }
   else
   {
      font = it->second;
   }

   SDL_Color foregroundColor = { .r = cl.r, .g = cl.g, .b = cl.b, .a = cl.a };
   auto surface = TTF_RenderUTF8_Blended(font.get(), (const char*)text.c_str(), foregroundColor);
   auto surfaceSize = std::pair{ surface->w, surface->h };

   auto texture = SDL_CreateTextureFromSurface(m_renderer.get(), surface);
   if (!texture)
   {
      SDL_Log("Unable to optimize text texture! SDL Error: %s\n", SDL_GetError());
   }
   SDL_DestroySurface(surface);
   SDL_TexturePtr textTexture(texture, SDL_DestroyTexture);
   SDL_SetTextureBlendMode(textTexture.get(), SDL_BLENDMODE_BLEND);

   return std::make_shared<Texture>(m_renderer, std::move(textTexture), surfaceSize.first, surfaceSize.second);
}

void Graphics::BeginDraw()
{
   SDL_RenderClear(m_renderer.get());
}

void Graphics::EndDraw()
{
   SDL_RenderPresent(m_renderer.get());
}

void Graphics::SetCursor(const std::string& fileName)
{
   std::filesystem::path rootPath(m_rootFilePath);
   auto cursorPath = rootPath / fileName;
   auto loadedSurface = IMG_Load((const char*)cursorPath.u8string().c_str());
   m_cursor = { SDL_CreateColorCursor(loadedSurface, 0, 0), &SDL_DestroyCursor };
   SDL_SetCursor(m_cursor.get());
}

void Graphics::DrawFilledRect(const Rect& area, const Color& cl)
{
   SDL_FRect rc{ .x = (float)area.x, .y = (float)area.y, .w = (float)area.w, .h = (float)area.h };
   SDL_RenderFillRect(m_renderer.get(), &rc);
}

void Graphics::DrawPolygons(std::span<Vertex> vertices, std::span<int> indices)
{
   m_tempVertices.resize(vertices.size());
   for (const auto& vertex: vertices)
   {
      m_tempVertices.push_back({
         .position = SDL_FPoint{.x = (float)vertex.position.x,
                                .y = (float)vertex.position.y},
         .color = SDL_FColor{.r = (float)vertex.color.r, 
                              .g = (float)vertex.color.g,
                              .b = (float)vertex.color.b,
                              .a = (float)vertex.color.a},
         .tex_coord = SDL_FPoint{.x = (float)vertex.texCoord.x,
                                .y = (float)vertex.texCoord.y}
         });
   }

   SDL_RenderGeometry(m_renderer.get(), nullptr,
      &m_tempVertices[0], (int)m_tempVertices.size(),
      indices.data(), (int)indices.size());
}

Rect Graphics::GetClientRect() const
{
   int width;
   int height;
   SDL_GetWindowSize(m_window.get(), &width, &height);
   return { .x = 0, .y = 0, .w = width, .h = height };
}

}