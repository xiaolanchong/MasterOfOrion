#include "Pane.h"

namespace windows
{
	Static::Static(const graphics::IGraphicsPtr& graphics, const graphics::Rect& rect,
		const std::u8string& text, const graphics::FontMetrics& fontMetrics, const graphics::Color& cl)
		: m_rect(rect)
	{
		m_texture = graphics->CreateTextureFromText(text, fontMetrics, cl);
	}

	void Static::Draw()
	{
		m_texture->Draw(m_rect.x, m_rect.y);
	}

	Pane::Pane(const graphics::IGraphicsPtr& graphics,
		const graphics::Rect& rect, const std::string& bgImageFileName)
		: m_rect(rect)
	{
		m_texture = graphics->CreateTextureFromFile(bgImageFileName);
	}

	void Pane::Draw()
	{
		m_texture->Draw(m_rect);
	}

	Image::Image(const graphics::IGraphicsPtr& graphics,
		const graphics::Point topLeft, const std::string& imageFileName)
		: m_topLeft(topLeft)
	{
		m_texture = graphics->CreateTextureFromFile(imageFileName);
	}

	void Image::Draw()
	{
		m_texture->Draw(m_topLeft.x, m_topLeft.y);
	}

	graphics::Rect Image::GetRect() const
	{
		auto size = m_texture->GetSize();
		return { .x = m_topLeft.x, .y = m_topLeft.y, .w = size.w, .h = size.h };
	}

}