// moo.cpp : Defines the entry point for the application.
//

#define SDL_MAIN_USE_CALLBACKS 1 /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

#include "moo.h"

struct AppState
{
   SDL_Window* window;
   SDL_Renderer* renderer;
   //SDL_Surface* screenSurface;
   SDL_Texture* mainMenuTexture;

   SDL_Cursor* cursor;
};

const std::string mainMenuPath = R"(c:\project\cpp\moo_assets\start_screen\start_screen.png)";
const std::string cursorPath = R"(c:\project\cpp\moo_assets\cursor_hand.png)";

SDL_AppResult initialize(AppState* as)
{
   int flags = IMG_INIT_PNG;
   if (!(IMG_Init(flags) & flags)) {
      //std::cout << "Can't init image: " << IMG_GetError() << std::endl;
      SDL_Log("SDL_image could not initialize! SDL_image Error: %s\n", SDL_GetError());
      return SDL_APP_FAILURE;
   }

   SDL_Surface* loadedSurface = IMG_Load(mainMenuPath.c_str());
   if (loadedSurface == NULL)
   {
      SDL_Log("Unable to load image %s! SDL_image Error: %s\n", mainMenuPath.c_str(), SDL_GetError());
   }
   else
   {
      as->mainMenuTexture = SDL_CreateTextureFromSurface(as->renderer, loadedSurface);
      //Convert surface to screen format
      //mainMenu = SDL_SurfacePtr(SDL_ConvertSurface(loadedSurface, as->screenSurface->format), &SDL_DestroySurface);
      if (!as->mainMenuTexture)
      {
         SDL_Log("Unable to optimize image %s! SDL Error: %s\n", mainMenuPath.c_str(), SDL_GetError());
      }

      //Get rid of old loaded surface
      SDL_DestroySurface(loadedSurface);
   }

   loadedSurface = IMG_Load(cursorPath.c_str());
   as->cursor = SDL_CreateColorCursor(loadedSurface, 0, 0);
   SDL_SetCursor(as->cursor);

   return SDL_APP_CONTINUE;
}

//SDL_SurfacePtr mainMenu;


SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
   if (!SDL_Init(SDL_INIT_VIDEO))
   {
      return SDL_APP_FAILURE;
   }

   AppState* as = (AppState*)SDL_calloc(1, sizeof(AppState));

   *appstate = as;

   constexpr auto SDL_WINDOW_WIDTH = 640 * 2;
   constexpr auto SDL_WINDOW_HEIGHT = 480 * 2;
   const uint64_t wflags = SDL_WINDOW_MOUSE_FOCUS | SDL_WINDOW_INPUT_FOCUS;
   if (!SDL_CreateWindowAndRenderer("Moo", SDL_WINDOW_WIDTH, SDL_WINDOW_HEIGHT, wflags, &as->window, &as->renderer))
   {
      return SDL_APP_FAILURE;
   }

   return initialize(as);


   //return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
   auto* ctx = (AppState*)appstate;
   switch (event->type)
   {
   case SDL_EVENT_QUIT:
      return SDL_APP_SUCCESS;
   case SDL_EVENT_USER:
      //snake_step(ctx);
      break;
   case SDL_EVENT_KEY_DOWN:
      //return handle_key_event_(ctx, event->key.scancode);
      break;
   case SDL_EVENT_MOUSE_MOTION:
      break;
   }
   return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate)
{
   AppState* as;
 //  SnakeContext* ctx;
   //SDL_FRect r;
   as = (AppState*)appstate;
   SDL_RenderClear(as->renderer);

   SDL_SetRenderDrawColor(as->renderer, 255, 255, 0, 255); /*head*/
  // set_rect_xy_(&r, ctx->head_xpos, ctx->head_ypos);
   SDL_FRect r{ .x = 0, .y =0, .w = 200, .h = 100 };
   SDL_RenderFillRect(as->renderer, &r);
   SDL_Rect dest{ 0, 0, 100, 100 };
   //SDL_BlitSurfaceScaled(mainMenu.get(), &dest, as->screenSurface, &dest, SDL_SCALEMODE_LINEAR);
   SDL_RenderTexture(as->renderer, as->mainMenuTexture, nullptr, nullptr);
   SDL_RenderPresent(as->renderer);
   return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate)
{
   if (appstate != NULL) {
      AppState* as = (AppState*)appstate;
      SDL_DestroyTexture(as->mainMenuTexture);
      SDL_DestroyRenderer(as->renderer);
      SDL_DestroyWindow(as->window);
      SDL_free(as);
   }
}