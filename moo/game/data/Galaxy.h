#pragma once

#include "Common.h"
#include "Star.h"
#include <vector>

namespace data
{
	
class Galaxy
{
public:
   Galaxy(Parsec width, Parsec height)
      : m_width(width), m_height(height)
   {}

   Parsec GetWidth() const { return m_width; }
   Parsec GetHeight() const { return m_height; }

   const Stars& GetStars() const { return m_stars; }

private:
   Stars m_stars;

   Parsec m_width;
   Parsec m_height;
};


}
