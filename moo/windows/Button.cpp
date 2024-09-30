#include "Button.h"
#include "../interfaces/IGraphics.h"
#include "../interfaces/ITexture.h"

namespace windows
{
   BaseButton::BaseButton(WindowContext context, Textures textures, State state,
      graphics::Point topLeft, OnPressed onPressed)
      : WindowContext(std::move(context))
      , m_state(state == State::Enabled ? ExtState::Enabled : ExtState::Disabled)
      , m_topLeft(std::move(topLeft))
      , m_onPressed(std::move(onPressed))
      , m_textures(std::move(textures))
   {

   }

   void BaseButton::Draw()
   {
      graphics::ITexturePtr texture = nullptr;
      switch (m_state)
      {
      case ExtState::Hovered:
         texture = m_textures.hoveredTexture;
         break;
      case ExtState::Enabled:
         texture = m_textures.enabledTexture;
         break;
      case ExtState::Disabled:
         texture = m_textures.disabledTexture;
         break;
      }

      if (texture)
         texture->Draw(m_topLeft.x, m_topLeft.y);
   }

   graphics::Rect BaseButton::GetRect() const
   {
      auto size = m_textures.hoveredTexture->GetSize();
      return { .x = m_topLeft.x, .y = m_topLeft.y, .w = size.w, .h = size.h };
   }

   void BaseButton::MoveTo(const graphics::Point& topLeft)
   {
      m_topLeft = topLeft;
   }

   BaseWindow::HandleResult BaseButton::OnMouseHover(HoverState state)
   {
      if (m_state == ExtState::Disabled)
         return HandleResult::Handled;

      switch (state)
      {
      case HoverState::Above:
         m_state = ExtState::Hovered;
         break;
      case HoverState::Away:
         m_state = ExtState::Enabled;
         break;
      }

      return HandleResult::Handled;
   }

   BaseWindow::HandleResult BaseButton::OnMouseButtonPressed(input::IInputCallback::Pressed pressed,
      input::IInputCallback::Button button, int x, int y)
   {
      if (m_state == ExtState::Disabled)
         return HandleResult::Continue;

      if (pressed == input::IInputCallback::Pressed::Up && 
         m_state == ExtState::Hovered)
      {
         if (m_onPressed)
            m_onPressed();
      }
      return HandleResult::Handled;
   }

   TextButton::TextButton(WindowContext context, std::u8string text, State state, Theme theme,
      graphics::Point topLeft, OnPressed onPressed)
      : BaseButton(context, createTextures(context.graphics, text, theme), state, std::move(topLeft), std::move(onPressed))
   {

   }

   BaseButton::Textures TextButton::createTextures(const graphics::IGraphicsPtr& graphics,
      const std::u8string& text, const Theme& theme)
   {
      Textures textures
      {
         .hoveredTexture = graphics->CreateTextureFromText(text, theme.fontMetrics, theme.hovered),
         .enabledTexture = graphics->CreateTextureFromText(text, theme.fontMetrics, theme.enabled),
         .disabledTexture = graphics->CreateTextureFromText(text, theme.fontMetrics, theme.disabled)
      };
      return textures;
   }

   ImageButton::ImageButton(WindowContext context, State state, Theme theme,
      graphics::Point topLeft, OnPressed onPressed)
      : BaseButton(context, createTextures(context.graphics, theme), state, std::move(topLeft), std::move(onPressed))
   {

   }

   BaseButton::Textures ImageButton::createTextures(const graphics::IGraphicsPtr& graphics, const Theme& theme)
   {
      Textures textures
      {
         .hoveredTexture = graphics->CreateTextureFromFile(theme.hoveredImageName),
         .enabledTexture = graphics->CreateTextureFromFile(theme.enabledImageName),
         .disabledTexture = graphics->CreateTextureFromFile(theme.disabledImageName)
      };
      return textures;
   }
}