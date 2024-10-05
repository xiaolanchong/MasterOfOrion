#include "TimerFactory.h"

namespace windows
{
   void TimerFactory::OnTick()
   {
      auto now = m_timeService->GetNow();
      for (;!m_timers.empty();)
      {
         const auto& topRef = m_timers.top();
         if (topRef.elapseTime > now)
            break;

         auto top = m_timers.top();
         m_timers.pop();
         if (auto handle = top.handleWeakPtr.lock())
         {
            top.onTimer();
            // timer may be reset in the handler
            bool clientHoldsTimer = handle.use_count() > 1;
            if (clientHoldsTimer)
               m_timers.push({ now + top.period, top.period, std::move(top.handleWeakPtr), std::move(top.onTimer) });
         }
      }
   }

   IWindowEnvironment::TimerHandle TimerFactory::CreateTimer(
      std::chrono::milliseconds period, IWindowEnvironment::OnTimer&& onTimer)
   {
      struct Dummy {};
      auto handle = std::make_shared<Dummy>();
      auto now = m_timeService->GetNow();
      m_timers.push({ now + period, period, handle, std::move(onTimer)});
      return handle;
   }
}
