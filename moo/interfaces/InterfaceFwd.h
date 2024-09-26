#pragma once

namespace graphics
{

class IGraphics;
class ITexture;

using ITexturePtr = std::shared_ptr<ITexture>;
using IGraphicsPtr = std::shared_ptr<IGraphics>;

}