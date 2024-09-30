#include "Window.h"
#include <cassert>
#include <algorithm>

namespace windows
{

   void BaseWindow::EnumerateChildWindows(const WindowVisitor& visitor)
   {
      m_enumeratedWindows.reserve(m_childWindows.size());
      for (auto it = m_childWindows.begin(); it != m_childWindows.end();)
      {
         if (auto window = it->lock())
         {
            m_enumeratedWindows.push_back(std::move(window));
            ++it;
         }
         else
         {
            it = m_childWindows.erase(it);
         }
      }
      for(const auto& window: m_enumeratedWindows)
         visitor(window);
      m_enumeratedWindows.clear();
   }

   void BaseWindow::addChild(const BaseWindowWeakPtr& child)
   {
      auto equivalent = [&](const auto& ptr)
         { return !child.owner_before(ptr) && !ptr.owner_before(child); };
      assert(std::find_if(m_childWindows.begin(), m_childWindows.end(), std::move(equivalent)) == m_childWindows.end());
      m_childWindows.push_back(child);
   }

}