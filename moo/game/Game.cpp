#include "Game.h"
#include "ui/StartScreen.h"
#include "ui/GalaxyScreen.h"

namespace game
{
   Game::Game(GameContext context)
      : GameContext(std::move(context))
   {
   }

   template<typename ScreenType>
   void Game::setCurrentScreen()
   {
      m_currentScreen = nullptr;
      ui::ScreenContext screenContext{ .graphics = graphics, .input = input, .callback = shared_from_this() };
      m_currentScreen = std::make_shared<ScreenType>(std::move(screenContext));
   }

   void Game::init()
   {
      setCurrentScreen<ui::StartScreen>();
   }

   std::shared_ptr<Game> Game::Create(GameContext context)
   {
      std::shared_ptr<Game> newGame(new Game(std::move(context)));
      newGame->init();
      return newGame;
   }

   void Game::Draw()
   {
      graphics->BeginDraw();
      m_currentScreen->Draw();
      graphics->EndDraw();
   }

   void Game::ToStart()
   {
   }

   void Game::ToNewGame()
   {
      setCurrentScreen<ui::GalaxyScreen>();
   }

   void Game::Quit()
   {
      m_needQuit = true;
   }
}
