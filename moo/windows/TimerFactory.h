#pragma once

#include "Window.h"
#include "../interfaces/ITimeService.h"
#include <queue>
#include <chrono>

namespace windows
{
	
   class TimerFactory
   {
   public:
      explicit TimerFactory(zeit::ITimeServicePtr timeService)
         : m_timeService(std::move(timeService))
      {}

      void OnTick();

      IWindowEnvironment::TimerHandle CreateTimer(
         std::chrono::milliseconds period, IWindowEnvironment::OnTimer&& onTimer);
   private:
      
      using TimerHandleWeakPtr = IWindowEnvironment::TimerHandle::weak_type;
      struct Item
      {
         zeit::TimePoint elapseTime;
         std::chrono::milliseconds period;
         TimerHandleWeakPtr handleWeakPtr;
         IWindowEnvironment::OnTimer onTimer;

         bool operator <(const Item& right) const
         {
            return elapseTime < right.elapseTime;
         }
      };
      std::priority_queue<Item> m_timers;
      zeit::ITimeServicePtr m_timeService;
   };
   
}
