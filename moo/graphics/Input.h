#pragma once

#include "../interfaces/IInput.h"
#include "../interfaces/IEnvironment.h"

namespace input
{
   class Input: public IInput
   {
   public:
      void RegisterCallback(IInputCallbackPtr callback) override;

      IEnvironment::RunResult Poll();
   private:
      IInputCallbackWeakPtr m_callback;
   };
}