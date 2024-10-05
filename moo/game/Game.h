#pragma once

#include "ui/IScreen.h"
#include "../interfaces/IGraphics.h"
#include "../interfaces/IInput.h"
#include "../interfaces/ITimeService.h"
#include <memory>

namespace game
{
   struct GameContext
   {
      graphics::IGraphicsPtr graphics;
      input::IInputPtr input;
      zeit::ITimeServicePtr timeService;
   };

   class Game: private GameContext
             , public ui::IScreenCallback
             , public std::enable_shared_from_this<Game>
   {
   public:
      static std::shared_ptr<Game> Create(GameContext context);

      bool NeedQuit() const { return m_needQuit; }
      void ProcessFrame();

   private:
      explicit Game(GameContext context);

      void ToStart() override;
      void ToGalaxy() override;
     // void ToStarSystem() override;
     // void ToPlanet() override;
      void Quit() override;

      void init();

      template<typename ScreenType>
      ui::IScreenPtr createScreen();
   private:

      bool m_needQuit = false;
      ui::IScreenPtr m_currentScreen;

      ui::IScreenPtr m_startScreen;
      ui::IScreenPtr m_galaxyScreen;
      ui::IScreenPtr m_starSystemScreen;
      ui::IScreenPtr m_planetScreen;
   };

}