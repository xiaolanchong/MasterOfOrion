#pragma once

#include "Window.h"
#include "../interfaces/Types.h"
#include "../interfaces/IGraphics.h"

#include <string>

namespace windows
{
   class BaseButton: public BaseWindow
               , protected WindowContext
   {
   public:

      enum class State
      {
         Enabled,
         Disabled,
      };

      using OnPressed = std::function<void()>;

      graphics::Rect GetRect() const override;

   protected:
      struct Textures
      {
         graphics::ITexturePtr hoveredTexture;
         graphics::ITexturePtr enabledTexture;
         graphics::ITexturePtr disabledTexture;
      };

      BaseButton(WindowContext context, Textures textures, State state,
         graphics::Point topLeft, OnPressed onPressed);

      void Draw() override;
      void MoveTo(const graphics::Point& topLeft) override;

      HandleResult OnMouseHover(HoverState state) override;

      HandleResult OnMouseButtonPressed(input::IInputCallback::Pressed pressed,
         input::IInputCallback::Button button, int x, int y) override;

      enum ExtState
      {
         Hovered,
         Enabled,
         Disabled,
      };
      
   private:
      Textures m_textures;

      ExtState m_state;
      graphics::Point m_topLeft;
      OnPressed m_onPressed;
   };

   class TextButton : public BaseButton
   {
      friend class BaseWindow;
   public:
      struct Theme
      {
         graphics::FontMetrics fontMetrics;
         graphics::Color hovered;
         graphics::Color enabled;
         graphics::Color disabled;
      };

   private:
      TextButton(WindowContext context, std::u8string text, State state, Theme theme,
         graphics::Point topLeft, OnPressed onPressed);

      static Textures createTextures(const graphics::IGraphicsPtr& graphics,
         const std::u8string& text, const Theme& theme);
   };

   class ImageButton : public BaseButton
   {
      friend class BaseWindow;
   public:
      struct Theme
      {
         std::string hoveredImageName;
         std::string enabledImageName;
         std::string disabledImageName;
      };

   private:
      ImageButton(WindowContext context, State state, Theme theme,
         graphics::Point topLeft, OnPressed onPressed);

      static Textures createTextures(const graphics::IGraphicsPtr& graphics, const Theme& theme);
   };
}