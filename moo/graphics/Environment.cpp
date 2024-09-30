#pragma once

#include "Environment.h"

namespace env
{
   Environment::Environment(graphics::sdl::GraphicsContext context)
      : m_graphics(std::make_shared<graphics::sdl::Graphics>(std::move(context)))
      , m_input(std::make_shared<input::Input>())
   {

   }

   IEnvironment::RunResult Environment::Run()
   {
      return m_input->Poll();
   }

}