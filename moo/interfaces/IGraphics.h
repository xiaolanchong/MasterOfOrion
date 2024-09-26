#pragma once

#include <memory>
#include <string>

#include "InterfaceFwd.h"
#include "Types.h"

namespace graphics
{

struct FontMetrics
{
   std::string fontName;
   int size;
};

class IGraphics
{
public:
   virtual ~IGraphics() = default;

   virtual ITexturePtr CreateTextureFromFile(const std::string& fileName) = 0;
   virtual ITexturePtr CreateTextureFromText(const std::u8string& text, const FontMetrics& fontMetrics,const Color& cl) = 0;

   virtual void SetCursor(const std::string& fileName) = 0;

   virtual void BeginDraw() = 0;
   virtual void EndDraw() = 0;

   enum class RunResult
   {
      Continue,
      Quit
   };
   virtual RunResult Run() = 0;
};

}