#pragma once

#include "StrongType.h"

namespace data
{

STRONG_TYPEDEF(double, Parsec);
STRONG_TYPEDEF(double, AU);

struct SpacePosition
{
   Parsec x, y, z;
};

}
