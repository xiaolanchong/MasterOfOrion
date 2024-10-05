#include "moo.h"
#include "interfaces/IGraphics.h"
#include "interfaces/ITexture.h"
#include "graphics/Environment.h"
#include "windows/WindowSystem.h"
#include "game/Game.h"
#include <glog/logging.h>

constexpr auto SDL_WINDOW_HEIGHT = 990; // 480 * 2;
constexpr auto SDL_WINDOW_WIDTH = SDL_WINDOW_HEIGHT * 4 / 3; // 640 * 2;

const std::u8string assetsRootPath = u8R"(c:\project\cpp\moo_assets\)";

int main(int argc, char** argv)
{
   google::InitGoogleLogging(argv[0]);

   graphics::sdl::GraphicsContext grContext
   { .m_rootFilePath = assetsRootPath,
      .m_windowWidth = SDL_WINDOW_WIDTH, 
      .m_windowHeight = SDL_WINDOW_HEIGHT };
   IEnvironmentPtr env = std::make_shared<env::Environment>(std::move(grContext));
   auto graphics = env->GetGraphics();

   const auto game = game::Game::Create(game::GameContext{ graphics, env->GetInput()});

   while (env->Run() != IEnvironment::RunResult::Quit)
   {
      if (game->NeedQuit())
      {
         LOG(INFO) << "Need quitting";
         break;
      }
      game->ProcessFrame();
   }

   return 0;
}
