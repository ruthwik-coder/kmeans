
/*
 * This example code creates an SDL window and renderer, and then clears the
 * window to a different color every frame, so you'll effectively get a window
 * that's smoothly fading between colors.
 *
 * This code is public domain. Feel free to use it for any purpose!
 */

#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdlib.h>
#include <stdio.h>
 #include <SDL3_ttf/SDL_ttf.h>
 #define MY_FONT "C:\\Windows\\Fonts\\arial.ttf"
/* We will use this renderer to draw into this window every frame. */
typedef struct{
 SDL_Window *window ;
 SDL_Renderer *renderer;

int k;
TTF_Font *font ;

  }AppState;
/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{     AppState* app_state = malloc(sizeof(AppState));
    SDL_SetAppMetadata("Example Renderer Clear", "1.0", "com.example.renderer-clear");
   *appstate = app_state;
   app_state->k=1;
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
if (TTF_Init() < 0) {
        SDL_Log("Couldn't initialize SDL_ttf: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    if (!SDL_CreateWindowAndRenderer("examples/renderer/clear", 1000, 500, 0,  &(app_state->window), &(app_state->renderer))) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
  app_state->font= TTF_OpenFont(MY_FONT, 25);
   // Ensure "arial.ttf" exists in your folder
    if (!app_state->font) {
        printf("Font load error: %s\n", SDL_GetError());
        return 1;
    }
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}
int rand_lim(int limit) {
/* return a random number between 0 and limit inclusive.
 *  */
// #includde <stdlib.h>
    int divisor = RAND_MAX/(limit+1);
    int retval;

    do { 
        retval = rand() / divisor;
    } while (retval > limit);

    return retval;
}


/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{ int running = 1;
 AppState* app_state = (AppState*)appstate;

    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }



 if (event->type == SDL_EVENT_KEY_DOWN) { 
//SDL_assert(event->type == SDL_EVENT_KEY_DOWN); /* just checking key presses here... */
    if (event->key.scancode == SDL_SCANCODE_KP_PLUS) {

       app_state->k++;
                    printf("%d \n",app_state->k);
          /* pressed what would be "W" on a US QWERTY keyboard. Move forward! */
    } else if (event->key.scancode == SDL_SCANCODE_KP_MINUS) {

       app_state->k--;
                   printf("%d \n",app_state->k);
         /* pressed what would be "S" on a US QWERTY keyboard. Move backward! */
    }
 }
        // while (SDL_PollEvent(&event)) {
        //     if (event->type == SDL_EVENT_KEY_DOWN) {
        //         printf("%d ..... \n",app_state->k);
        //         SDL_Keycode key = event->key.key;
        //         if (key == SDLK_KP_PLUS || key == SDLK_PLUS) {
        //             app_state->k++;
        //             printf("%d \n",app_state->k);
        //         } else if (key == SDLK_KP_MINUS || key == SDLK_MINUS) {
        //            app_state->k--;
        //            printf("%d \n",app_state->k);
        //         }
        //     }
        // }
   
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}
void drawrect(void *appstate)
{
AppState* app_state = (AppState*)appstate;
    // Width of each rectangle (spread evenly)
    int rect_width = 50;
    int rect_height =20;
              for (int i = 0; i < app_state->k; ++i) {
            SDL_FRect rect = {
                .x = i * rect_width,
                .y = 450,
                .w = rect_width,
                .h = rect_height
            };

            // Random color
            Uint8 r = rand_lim(255);
            Uint8 g = rand_lim(255);
            Uint8 b = rand_lim(255);

            SDL_SetRenderDrawColor(app_state->renderer, r, g, b, 255);
            SDL_RenderFillRect(app_state->renderer, &rect);
        }


}
/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{   AppState* app_state = (AppState*)appstate;
SDL_SetRenderDrawColor(app_state->renderer, 20, 20, 20, 255);
        SDL_RenderClear(app_state->renderer);

        // Render k
  char cv[32];  // A buffer to hold the text "k <value>"
snprintf(cv, sizeof(cv), "k=%d", app_state->k); 
//printf("%s ... \n",cv);
        SDL_Color textColor = {255, 255, 255, 255};
        SDL_Surface* kSurface = TTF_RenderText_Blended(app_state->font, cv,strlen(cv), textColor);
        SDL_Texture* kTexture = SDL_CreateTextureFromSurface(app_state->renderer, kSurface);
        SDL_FRect kRect = {450, 10, kSurface->w, kSurface->h};
 
        SDL_RenderTexture(app_state->renderer, kTexture, NULL, &kRect);
        SDL_DestroyTexture(kTexture);



drawrect(appstate);
        SDL_DestroySurface(kSurface);

        SDL_RenderPresent(app_state->renderer);
        SDL_Delay(16);

 
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
   AppState* app_state = (AppState*)appstate;

    free(app_state);
}
//>gcc test.c -o test.exe -I"C:\msys64\mingw64\include" -L"C:\msys64\mingw64\lib"  -lmingw32 -lSDL3 -lSDL3_ttf && test.exe
//del kmeans.exe && gcc kmeans.c -o kmeans.exe -I"C:\msys64\mingw64\include" -L"C:\msys64\mingw64\lib"  -lmingw32 -lSDL3 -lSDL3_ttf && kmeans.exe