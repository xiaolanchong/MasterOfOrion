#pragma once

#include "Common.h"
#include <vector>

namespace data
{
	
class Star
{
public:
	enum class Type
	{
		BlueWhite,
		White,
		Yellow,
		Red,
		Orange,
		Brown,
	};

	Star(Type type, SpacePosition pos)
		: m_type(type)
		, m_pos(std::move(pos))
	{}

private:
	Type m_type;
	SpacePosition m_pos;
};

using Stars = std::vector<Star>;

}
