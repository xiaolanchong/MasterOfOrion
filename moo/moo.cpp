


#include "moo.h"
#include "interfaces/IGraphics.h"
#include "interfaces/ITexture.h"
#include "graphics/Graphics.h"


constexpr auto SDL_WINDOW_HEIGHT = 990; // 480 * 2;
constexpr auto SDL_WINDOW_WIDTH = SDL_WINDOW_HEIGHT * 4 / 3; // 640 * 2;

const std::u8string assetsRootPath = u8R"(c:\project\cpp\moo_assets\)";

int main(int argc, char** argv)
{
   graphics::sdl::GraphicsContext grContext
   { .m_rootFilePath = assetsRootPath,
      .m_windowWidth = SDL_WINDOW_WIDTH, 
      .m_windowHeight = SDL_WINDOW_HEIGHT };
   graphics::IGraphicsPtr graphics = std::make_shared<graphics::sdl::Graphics>(std::move(grContext));

   graphics->SetCursor("cursors/pointing_hand.png");
   auto mainTexture = graphics->CreateTextureFromFile("images/start_screen.png");

  
   auto textTexture = graphics->CreateTextureFromText(
      u8"This is my text. Мой текст.", 
      graphics::FontMetrics{ "bicubik", 36 }, 
      { .r = 255, .g = 0, .b = 0, .a = 128 });
   

   while (graphics->Run() != graphics::IGraphics::RunResult::Quit)
   {
      graphics->BeginDraw();

      if (mainTexture)
         mainTexture->Draw(0, 0);

      if (textTexture)
         textTexture->Draw(100, 100);

      graphics->EndDraw();
   }

   return 0;
}
