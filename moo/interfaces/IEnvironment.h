#pragma once

#include "IGraphics.h"
#include "IInput.h"

class IEnvironment
{
public:
   virtual ~IEnvironment() = default;

   virtual graphics::IGraphicsPtr GetGraphics() = 0;
   virtual input::IInputPtr GetInput() = 0;

   enum class RunResult
   {
      Continue,
      Quit
   };

   virtual RunResult Run() = 0;
};

using IEnvironmentPtr = std::shared_ptr<IEnvironment>;
