#include "Pane.h"

namespace windows
{
	Static::Static(const graphics::IGraphicsPtr& graphics, const graphics::Point& topLeft,
		const std::u8string& text, const graphics::FontMetrics& fontMetrics, const graphics::Color& cl)
		: m_topLeft(topLeft)
	{
		m_texture = graphics->CreateTextureFromText(text, fontMetrics, cl);
	}

	void Static::Draw()
	{
		m_texture->Draw(m_topLeft.x, m_topLeft.y);
	}

	graphics::Rect Static::GetRect() const
	{
		auto size = m_texture->GetSize();
		return { .x = m_topLeft.x, .y = m_topLeft.y, .w = size.w, .h = size.h };
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

	Image::Image(WindowContext context,
		graphics::Point topLeft, std::optional<graphics::Size> optSize,
		const std::string& imageFileName)
		: m_topLeft(std::move(topLeft))
		, m_optSize(std::move(optSize))
	{
		m_texture = context.graphics->CreateTextureFromFile(imageFileName);
	}

	void Image::Draw()
	{
		if (m_optSize)
			m_texture->Draw(graphics::Rect{ m_topLeft.x, m_topLeft.y, m_optSize->w, m_optSize->h });
		else
			m_texture->Draw(m_topLeft.x, m_topLeft.y);
	}

	graphics::Rect Image::GetRect() const
	{
		if (m_optSize)
			return { m_topLeft.x, m_topLeft.y, m_optSize->w, m_optSize->h };

		auto size = m_texture->GetSize();
		return { .x = m_topLeft.x, .y = m_topLeft.y, .w = size.w, .h = size.h };
	}

}