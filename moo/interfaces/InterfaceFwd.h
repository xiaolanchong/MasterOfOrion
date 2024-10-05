#pragma once

#include <memory>

namespace graphics
{

class IGraphics;
class ITexture;

using ITexturePtr = std::shared_ptr<ITexture>;
using IGraphicsPtr = std::shared_ptr<IGraphics>;

}

namespace input
{

   class IInput;
   class IInputCallback;

   using ITexturePtr = std::shared_ptr<IInput>;
   using IInputCallbackPtr = std::shared_ptr<IInputCallback>;

}

namespace zeit
{
   class ITimeService;
   using ITimeServicePtr = std::shared_ptr<ITimeService>;
}
