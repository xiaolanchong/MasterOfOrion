#pragma once

#include "ui/IScreen.h"
#include "../interfaces/IGraphics.h"
#include "../interfaces/IInput.h"
#include <memory>

namespace game
{
   struct GameContext
   {
      graphics::IGraphicsPtr graphics;
      input::IInputPtr input;
   };

   class Game: private GameContext
             , public ui::IScreenCallback
             , public std::enable_shared_from_this<Game>
   {
   public:
      static std::shared_ptr<Game> Create(GameContext context);

      bool NeedQuit() const { return m_needQuit; }
      void Draw();

   private:
      explicit Game(GameContext context);

      void ToStart() override;
      void ToNewGame() override;
      void Quit() override;

      void init();

      template<typename ScreenType>
      void setCurrentScreen();
   private:

      bool m_needQuit = false;
      std::shared_ptr<ui::IScreen> m_currentScreen;
   };

}