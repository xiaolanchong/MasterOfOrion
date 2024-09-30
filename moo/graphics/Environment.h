#pragma once

#include "../interfaces/IEnvironment.h"
#include "Input.h"
#include "Graphics.h"

#include <memory>

namespace env
{

   class Environment : public IEnvironment
   {
   public:
      Environment(graphics::sdl::GraphicsContext context);

      graphics::IGraphicsPtr GetGraphics() override { return m_graphics; }
      input::IInputPtr GetInput() override { return m_input; }

      RunResult Run() override;

   private:
      graphics::IGraphicsPtr m_graphics;
      std::shared_ptr<input::Input> m_input;
   };
}