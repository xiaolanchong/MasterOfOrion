#include "StartScreen.h"
#include "../../windows/Pane.h"
#include "../../windows/Button.h"

namespace game::ui
{
   StartScreen::StartScreen(ScreenContext context)
      : ScreenContext(std::move(context))
   {
      using namespace graphics;
      using namespace windows;

      m_windowSystem = std::make_shared<WindowSystem>();
      input->RegisterCallback(m_windowSystem);
      {
         Rect rect = graphics->GetClientRect();
         m_windowSystem->SetClientSize(rect.w, rect.h);
      }

      graphics->SetCursor("cursors/pointing_hand.png");
      auto mainPain = m_windowSystem->Create<Pane>(graphics, graphics->GetClientRect(), "images/start_screen/background.png");
      m_windows.push_back(mainPain);
      {
         windows::TextButton::Theme theme{
            .fontMetrics = { "Days Sans Black", 48 },
            .hovered = {.r = 0x33, .g = 0xff, .b = 0x33, .a = 192 },
            .enabled = {.r = 0, .g = 0xcc, .b = 0, .a = 192 },
            .disabled = {.r = 0x33, .g = 0x66, .b = 0x33, .a = 192 },
         };
         const int yshift = 60;

         auto onQuit = [callback = callback]()
         {
            if (auto callbackPtr = callback.lock())
            {
               callbackPtr->Quit();
            }
         };

         auto onNewGame = [callback = callback]()
            {
               if (auto callbackPtr = callback.lock())
               {
                  callbackPtr->ToGalaxy();
               }
            };

         auto onLoad = []() {};
         auto onContinue = []() {};

         WindowContext windowContext{ m_windowSystem, graphics };
         m_windows.push_back(mainPain->Create<TextButton>(windowContext, u8"CONTINUE", BaseButton::State::Disabled, theme, Point{ 400, 400 + 0 * yshift }, std::move(onContinue)));
         m_windows.push_back(mainPain->Create<TextButton>(windowContext, u8"LOAD GAME", BaseButton::State::Disabled, theme, Point{ 400, 400 + 1 * yshift }, std::move(onLoad)));
         m_windows.push_back(mainPain->Create<TextButton>(windowContext, u8"NEW GAME", BaseButton::State::Enabled, theme, Point{ 400, 400 + 2 * yshift }, std::move(onNewGame)));
         m_windows.push_back(mainPain->Create<TextButton>(windowContext, u8"QUIT GAME", BaseButton::State::Enabled, theme, Point{ 400, 400 + 3 * yshift }, std::move(onQuit)));
      }
   }

   void StartScreen::Draw()
   {
      m_windowSystem->Draw();
   }

   void StartScreen::PreDraw()
   {
      m_windowSystem->PreDraw();
   }

}