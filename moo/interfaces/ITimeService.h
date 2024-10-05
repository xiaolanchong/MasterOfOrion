#pragma once

#include <chrono>
#include <memory>

namespace zeit
{

using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;
	
class ITimeService
{
public:
   virtual ~ITimeService() = default;
   
   virtual TimePoint GetNow() = 0;
};

using ITimeServicePtr = std::shared_ptr<ITimeService>;

}
