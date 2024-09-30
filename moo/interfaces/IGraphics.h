#pragma once

#include "InterfaceFwd.h"
#include "Types.h"

#include <memory>
#include <string>
#include <span>

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
   virtual ITexturePtr CreateTextureFromText(const std::u8string& text,
      const FontMetrics& fontMetrics, const Color& cl) = 0;

   virtual void SetCursor(const std::string& fileName) = 0;

   virtual void BeginDraw() = 0;
   virtual void EndDraw() = 0;

   virtual void DrawFilledRect(const Rect& area, const Color& cl) = 0;

   struct Vertex
   {
      Point position{};
      Color color{};
      Point texCoord{};
   };

   virtual void DrawPolygons(std::span<Vertex> vertices, std::span<int> indices) = 0;

   virtual Rect GetClientRect() const = 0;
};

}