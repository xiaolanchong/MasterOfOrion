#pragma once

#include <memory>

namespace game::ui
{
   class IScreenCallback
   {
   public:
      virtual ~IScreenCallback() = default;

      virtual void ToStart() = 0;
      virtual void ToGalaxy() = 0;
    //  virtual void ToStarSystem() = 0;
      //virtual void ToPlanet() = 0;
      virtual void Quit() = 0;
   };

   using IScreenCallbackPtr = std::shared_ptr<IScreenCallback>;
   using IScreenCallbackWeakPtr = std::weak_ptr<IScreenCallback>;

   class IScreen
   {
   public:
      virtual ~IScreen() = default;

      virtual void PreDraw() = 0;
      virtual void Draw() = 0;
   };

   using IScreenPtr = std::shared_ptr<IScreen>;
   using IScreenWeakPtr = std::weak_ptr<IScreen>;
}