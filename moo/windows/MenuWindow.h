#pragma once

#include "Window.h"
#include "../interfaces/Types.h"
#include <string>
#include <functional>

namespace windows
{

#if 0
   class MenuWindow: public Window,
                     private WindowContext
   {
      friend class BaseWindow;
   public:

      enum class ItemState
      {
         Enabled,
         Disabled,
      };

      struct ItemData
      {
         ItemState state;
         std::u8string text;
      };

      struct ColorScheme
      {
         graphics::Color active; // also hover
         graphics::Color inactive;
         graphics::Color disabled;
      };

      void AddItem(const ItemData& data, std::function<void()> onSelected);

   private:
      class MenuItem : public Window,
         private WindowContext
      {
         friend class BaseWindow;
      public:

      private:
         MenuItem(WindowContext context, const FontMetrics& font, const std::u8string& text, std::function<void()> onSelected);
      };

      MenuWindow(WindowContext context, const FontMetrics& font, ColorScheme scheme);
   };
#endif
}