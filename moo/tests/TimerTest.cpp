#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../windows/TimerFactory.h"

using namespace testing;
using namespace windows;
using namespace std::chrono_literals;
using namespace ::testing;

namespace
{
   class MockTimeService: public zeit::ITimeService
   {
   public:
       MOCK_METHOD(zeit::TimePoint, GetNow, (), (override));
   };

   class Counter
   {
   public:
      zeit::TimePoint Now()
      {
         ++m_ticks;
         return zeit::TimePoint(m_ticks * 10ms);
      }
   private:
      int m_ticks = 0;
   };
}

class TimerTest : public Test
{
protected:
   TimerTest()
      : m_timeService(std::make_shared< MockTimeService>())
      , m_factory(m_timeService)
   {}

   std::shared_ptr< MockTimeService> m_timeService;
   TimerFactory m_factory;
   Counter m_counter;
};

TEST_F(TimerTest, SimpeTimer)
{
   InSequence s;
   EXPECT_CALL(*m_timeService, GetNow())
      .Times(Exactly(2))
      .WillRepeatedly(InvokeWithoutArgs(&m_counter, &Counter::Now));

   bool called = false;
   auto handle = m_factory.CreateTimer(5ms, [&]() {called = true; });
   m_factory.OnTick();

   EXPECT_TRUE(called);
}

TEST_F(TimerTest, ExpiredTimer)
{
   InSequence s;
   EXPECT_CALL(*m_timeService, GetNow())
      .Times(Exactly(2))
      .WillRepeatedly(InvokeWithoutArgs(&m_counter, &Counter::Now));

   bool called = false;
   auto handle = m_factory.CreateTimer(5ms, [&]() {called = true; });
   handle = nullptr;  // reset the timer
   m_factory.OnTick();

   EXPECT_FALSE(called);
}

TEST_F(TimerTest, RecurringTimer)
{
   InSequence s;
   const size_t ticksCalled = 6;
   EXPECT_CALL(*m_timeService, GetNow())
      .Times(Exactly(ticksCalled + 1))
      .WillRepeatedly(InvokeWithoutArgs(&m_counter, &Counter::Now));

   size_t called = 0;
   auto handle = m_factory.CreateTimer(17ms, [&]() {called++; });
   for (size_t i = 0; i < ticksCalled; ++i)
      m_factory.OnTick();

   EXPECT_EQ(called, ticksCalled*10/17);
}

TEST_F(TimerTest, SelfResettingTimer)
{
   InSequence s;
   const size_t ticksCalled = 10;
   EXPECT_CALL(*m_timeService, GetNow())
      .Times(Exactly(ticksCalled + 1))
      .WillRepeatedly(InvokeWithoutArgs(&m_counter, &Counter::Now));

   size_t called = 0;
   windows::IWindowEnvironment::TimerHandle handle;
   handle = m_factory.CreateTimer(17ms, [&]()
      { 
         ++called;
         if (called == 2)
            handle = nullptr;
      });
   for (size_t i = 0; i < ticksCalled; ++i)
      m_factory.OnTick();

   EXPECT_EQ(called, 2);
}
