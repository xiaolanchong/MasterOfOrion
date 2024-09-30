#pragma once

#include "Window.h"
#include "../interfaces/ITexture.h"
#include "../interfaces/IGraphics.h"
#include "../interfaces/Types.h"

#include <string>

namespace windows
{

class Static : public BaseWindow
{
	friend class BaseWindow;
protected:
	Static(const graphics::IGraphicsPtr& graphics, const graphics::Rect& rect,
		const std::u8string& text, const graphics::FontMetrics& fontMetrics, const graphics::Color& cl);

	void Draw() override;
	graphics::Rect GetRect() const override { return m_rect; }

private:
	graphics::ITexturePtr m_texture;
	graphics::Rect m_rect;
};
	
class Pane : public BaseWindow
{
	friend class WindowSystem;
	friend class BaseWindow;
protected:
	Pane(const graphics::IGraphicsPtr& graphics,
		const graphics::Rect& rect, const std::string& bgImageFileName);

	void Draw() override;
	graphics::Rect GetRect() const override { return m_rect; }

private:
	graphics::ITexturePtr m_texture;
	graphics::Rect m_rect;
};

class Image : public BaseWindow
{
	friend class BaseWindow;
protected:
	Image(const graphics::IGraphicsPtr& graphics,
		const graphics::Point topLeft, const std::string& imageFileName);

	void Draw() override;
	graphics::Rect GetRect() const override;

private:
	graphics::ITexturePtr m_texture;
	graphics::Point m_topLeft;
};
	
}