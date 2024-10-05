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
   ui::IScreenPtr Game::createScreen()
   {
      m_currentScreen = nullptr;
      ui::ScreenContext screenContext{ .graphics = graphics, .input = input, .callback = shared_from_this() };
      return std::make_shared<ScreenType>(std::move(screenContext));
   }

   void Game::init()
   {
      ToStart();
   }

   std::shared_ptr<Game> Game::Create(GameContext context)
   {
      std::shared_ptr<Game> newGame(new Game(std::move(context)));
      newGame->init();
      return newGame;
   }

   void Game::ProcessFrame()
   {
      m_currentScreen->PreDraw();

      graphics->BeginDraw();
      m_currentScreen->Draw();
      graphics->EndDraw();
   }

   void Game::ToStart()
   {
      if (!m_startScreen)
         m_startScreen = createScreen<ui::StartScreen>();
      m_currentScreen = m_startScreen;
   }

   void Game::ToGalaxy()
   {
      if (!m_galaxyScreen)
         m_galaxyScreen = createScreen<ui::GalaxyScreen>();
      m_currentScreen = m_galaxyScreen;
   }

   void Game::Quit()
   {
      m_needQuit = true;
   }
}
