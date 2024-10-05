#pragma once

#include "../interfaces/ITimeService.h"

namespace zeit
{
   class StdTimeService : public ITimeService
   {
   public:
      TimePoint GetNow() override
      {
         return TimePoint::clock::now();
      }
   };
}
