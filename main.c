#ifdef _MSC_VER
   #define _CRT_SECURE_NO_WARNINGS
#endif
#define SDL_MAIN_USE_CALLBACKS 1
 #include <SDL3/SDL.h>
 #include <SDL3/SDL_main.h>
 #include <SDL3_ttf/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include "kmeans.h"
#define MY_FONT "C:\\Windows\\Fonts\\arial.ttf"
#define SDL_MESSAGEBOX_ERROR                    0x00000010u
//#define N 1280*720
#define D 3
//#define K 2
typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_CameraID* devices;
    SDL_Camera* camera;
    SDL_Texture* texture;
    int K;
    TTF_Font *font ;
  float cam_x, cam_y, cam_w, cam_h;
bool dragging;
float drag_offset_x, drag_offset_y;
    //  int a[17][30],a2[17][30];
    int width;
    int height;
    int camera_count;
    // Changed: Store array of centroids instead of single values
    Uint8* centroids; // Will store K*3 values (RGB for each centroid)
} AppState ;
SDL_Rect camera_viewport = {20, 20,320, 240};
 // Initial small position/size
bool resizing = false;
int resize_margin = 10;

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

SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv) {

     if (TTF_Init() < 0) {
        SDL_Log("Couldn't initialize SDL_ttf: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    AppState* app_state = malloc(sizeof(AppState));
    *app_state = (AppState){
        .width = 800,
        .height = 600,
        
    };
    *appstate = app_state;
       app_state->K=2;
    // Initialize centroids array
    app_state->centroids = malloc(app_state->K * 3 * sizeof(Uint8));
 app_state->font= TTF_OpenFont(MY_FONT, 50);
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_CAMERA)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    app_state->cam_w = app_state->width / 4.0f;
    app_state->cam_h = app_state->height / 4.0f;
    app_state->cam_x = 20.0f;
    app_state->cam_y = 20.0f;
    app_state->dragging = false;

    if (!SDL_CreateWindowAndRenderer("SDL3 Camera Demo", app_state->width, app_state->height, 0, &(app_state->window), &(app_state->renderer))) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_CameraID* devices = SDL_GetCameras(&app_state->camera_count);
    app_state->devices = devices;

    SDL_Log("Found %d cameras!", app_state->camera_count);

    // Open first camera
    app_state->camera = SDL_OpenCamera(devices[0], NULL);
    if (app_state->camera == NULL) {
        SDL_Log("Can't open the selected camera: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // Get the selected camera format
    SDL_CameraSpec spec;
    SDL_GetCameraFormat(app_state->camera, &spec);
    int FPS = spec.framerate_numerator / spec.framerate_denominator;
    SDL_Log("Got a camera of %dx%d and FPS %d", spec.width, spec.height, FPS);

    return SDL_APP_CONTINUE;
}
void drawrect(void *appstate)
{
AppState* app_state = (AppState*)appstate;
    // Width of each rectangle (spread evenly)
    int rect_width = 50;
    int rect_height =50;
              for (int i = 0; i < app_state->K; ++i) {
            SDL_FRect rect = {
                .x = i * rect_width,
                .y = 450,
                .w = rect_width,
                .h = rect_height
            };

            // Get RGB values for this centroid
            Uint8 r = app_state->centroids[i * 3 + 0];
            Uint8 g = app_state->centroids[i * 3 + 1];
            Uint8 b = app_state->centroids[i * 3 + 2];

            SDL_SetRenderDrawColor(app_state->renderer, r, g, b, 255);
            SDL_RenderFillRect(app_state->renderer, &rect);
        }


}
// Add this function to help with precise error tracking
void log_line_error(const char* function_name, int line_number) {
    printf("Error at %s (line %d): %s\n", function_name, line_number, SDL_GetError());
}

// Then in SDL_AppIterate, add specific logging without changing your code
SDL_AppResult SDL_AppIterate(void* appstate) {
    AppState* app_state = (AppState*)appstate;
  // printf("%d\n",app_state->noof);
    SDL_Surface* frame = SDL_AcquireCameraFrame(app_state->camera, NULL);
    if (frame != NULL) {//printf("**** \n");
        if (app_state->texture == NULL) {
            SDL_Log("Creating new texture %dx%d", frame->w, frame->h);
            SDL_SetWindowSize(app_state->window, frame->w, frame->h);
            app_state->width = frame->w;
            app_state->height = frame->h;
     
     
 app_state->texture = SDL_CreateTexture(app_state->renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING,camera_viewport.w, camera_viewport.h);
         //   app_state->texture = SDL_CreateTexture(app_state->renderer, frame->format, SDL_TEXTUREACCESS_STREAMING, frame->w, frame->h);

 //app_state->texture = SDL_CreateTexture(app_state->renderer, frame->format, SDL_TEXTUREACCESS_STREAMING, frame->w, frame->h);
            if (app_state->texture == NULL) {
                log_line_error(__func__, __LINE__);
            }
        } else {
            // Log point 1: Before updating texture
          //  SDL_Log("Point 1: Before updating texture - Error: %s", SDL_GetError());
            
           // SDL_UpdateTexture(app_state->texture, NULL, frame->pixels, frame->pitch);
            
            // Log point 2: After updating texture
          //  SDL_Log("Point 2: After updating texture - Error: %s", SDL_GetError());
        }

        // Log point 3: Before getting properties
        //SDL_Log("Point 3: Before getting properties - Error: %s", SDL_GetError());

        SDL_PropertiesID props = SDL_GetTextureProperties(app_state->texture);
        
        // Log point 4: After getting properties
        //SDL_Log("Point 4: After getting properties - Error: %s", SDL_GetError());
        
        if (props == 0) {
            printf("Failed to get texture properties: %s\n", SDL_GetError());
            return SDL_APP_FAILURE;
        }
        
        // Access texture properties
        int format = SDL_GetNumberProperty(props, SDL_PROP_TEXTURE_FORMAT_NUMBER, 0);
        int access = SDL_GetNumberProperty(props, SDL_PROP_TEXTURE_ACCESS_NUMBER, 0);
        int width = SDL_GetNumberProperty(props, SDL_PROP_TEXTURE_WIDTH_NUMBER, 0);
        int height = SDL_GetNumberProperty(props, SDL_PROP_TEXTURE_HEIGHT_NUMBER, 0);
        int colorspace = SDL_GetNumberProperty(props, SDL_PROP_TEXTURE_COLORSPACE_NUMBER, 0);
       
        SDL_Surface* aa = SDL_ConvertSurface(frame, SDL_PIXELFORMAT_RGB24);
      SDL_Surface* rgb_frame=  SDL_ScaleSurface(aa, camera_viewport.w, camera_viewport.h, SDL_SCALEMODE_NEAREST);
SDL_DestroySurface(aa);
int N=rgb_frame->w*rgb_frame->h;
 //  printf("%d %d %d \n ", N, rgb_frame->h,rgb_frame->w);
//3840 is the pitch
if (rgb_frame) {
    int *Location = (int*)calloc(N+(D*app_state->K) , sizeof(int));
    Uint8* pixels = (Uint8*)rgb_frame->pixels;
   // printf("%d \n",sizeof(rgb_frame->pixels));
    int pitch = rgb_frame->pitch;
    int step = 1; // Approximate step to get ~500 samples
    Location=kmeans2(pixels,Location,N,D,app_state->K);  // Make sure this function is correctly defined in test.h

    // Extract centroids from the end of Location array and store them
    for (int k = 0; k < app_state->K; k++) {
        int centroid_base = N + k * D;
        app_state->centroids[k * 3 + 0] = (Uint8)Location[centroid_base + 0]; // R
        app_state->centroids[k * 3 + 1] = (Uint8)Location[centroid_base + 1]; // G
        app_state->centroids[k * 3 + 2] = (Uint8)Location[centroid_base + 2]; // B
    }

    for (int y = 0; y < rgb_frame->h; y += step) {  //720
        for (int x = 0; x < rgb_frame->w; x += step) { //1280

            int pixel_index = y * pitch + x * 3; // 3 for RGB24
            int cluster = Location[pixel_index/3]; // 0..K-1

            // Use the stored centroid colors
            pixels[pixel_index + 0] = app_state->centroids[cluster * 3 + 0]; // R
            pixels[pixel_index + 1] = app_state->centroids[cluster * 3 + 1]; // G
            pixels[pixel_index + 2] = app_state->centroids[cluster * 3 + 2]; // B
        }
    }
    free(Location);

    //rgb_frame->pixels=calculatingthekmeans(rgb_frame->pixels);
     SDL_UpdateTexture(app_state->texture, NULL, rgb_frame->pixels, rgb_frame->pitch);
     
 SDL_RenderPresent(app_state->renderer);
    SDL_DestroySurface(rgb_frame);
}


        SDL_ReleaseCameraFrame(app_state->camera, frame);
    } else {
        return SDL_APP_CONTINUE;
        log_line_error(__func__, __LINE__);
       
    }
    
    SDL_SetRenderDrawColorFloat(app_state->renderer, 0.3f, 0.5f, 1.0f, SDL_ALPHA_OPAQUE_FLOAT);
    SDL_RenderClear(app_state->renderer);

    SDL_FRect camera_viewport_f = {
        .x = (float)camera_viewport.x,
        .y = (float)camera_viewport.y,
        .w = (float)camera_viewport.w,
        .h = (float)camera_viewport.h
    };

    // Log point 5: Before rendering texture
   // SDL_Log("Point 5: Before rendering texture - Error: %s", SDL_GetError());
    
    SDL_RenderTexture(app_state->renderer, app_state->texture, NULL, &camera_viewport_f);
 SDL_SetRenderDrawColor(app_state->renderer, 20, 20, 20, 255);
      //  SDL_RenderClear(app_state->renderer);

        // Render k
  char cv[32];  // A buffer to hold the text "k <value>"
snprintf(cv, sizeof(cv), "k=%d", app_state->K); 
//printf("%s ... \n",cv);
        SDL_Color textColor = {0,0,0,0};
        SDL_Surface* kSurface = TTF_RenderText_Blended(app_state->font, cv,strlen(cv), textColor);
        SDL_Texture* kTexture = SDL_CreateTextureFromSurface(app_state->renderer, kSurface);
        SDL_FRect kRect = {700, 50, 50,50 };
 
        SDL_RenderTexture(app_state->renderer, kTexture, NULL, &kRect);
        SDL_DestroyTexture(kTexture);



drawrect(appstate);
        SDL_DestroySurface(kSurface);
    SDL_RenderPresent(app_state->renderer);
    
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
    AppState* app_state = (AppState*)appstate;
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }

    static bool mouse_down = false;

    if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        int mx = event->button.x;
        int my = event->button.y;
        // Check if mouse is near the bottom-right corner of the camera rectangle
        if (mx >= camera_viewport.x + camera_viewport.w - resize_margin &&
            mx <= camera_viewport.x + camera_viewport.w &&
            my >= camera_viewport.y + camera_viewport.h - resize_margin &&
            my <= camera_viewport.y + camera_viewport.h) {
            resizing = true;
        }
        mouse_down = true;
    } else if (event->type == SDL_EVENT_MOUSE_BUTTON_UP) {
        resizing = false;
        mouse_down = false;
    } else if (event->type == SDL_EVENT_MOUSE_MOTION) {
        int mx = event->motion.x;
        int my = event->motion.y;

        // Change cursor when near the resize edge
        if (mx >= camera_viewport.x + camera_viewport.w - resize_margin &&
            mx <= camera_viewport.x + camera_viewport.w &&
            my >= camera_viewport.y + camera_viewport.h - resize_margin &&
            my <= camera_viewport.y + camera_viewport.h) {
            SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_NWSE_RESIZE));
        } else {
            SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT));
        }

        if (resizing && mouse_down) {
            camera_viewport.w = mx - camera_viewport.x;
            camera_viewport.h = my - camera_viewport.y;

        }
    }

 if (event->type == SDL_EVENT_KEY_DOWN) { 
//SDL_assert(event->type == SDL_EVENT_KEY_DOWN); /* just checking key presses here... */
    if (event->key.scancode == SDL_SCANCODE_KP_PLUS) {
       app_state->K++;
       // Reallocate centroids array for new K value
       app_state->centroids = realloc(app_state->centroids, app_state->K * 3 * sizeof(Uint8));
       printf("%d \n",app_state->K);
          /* pressed what would be "W" on a US QWERTY keyboard. Move forward! */
    } else if (event->key.scancode == SDL_SCANCODE_KP_MINUS) {
       if (app_state->K > 1) { // Prevent K from going below 1
           app_state->K--;
           // Reallocate centroids array for new K value
           app_state->centroids = realloc(app_state->centroids, app_state->K * 3 * sizeof(Uint8));
           printf("%d \n",app_state->K);
       }
         /* pressed what would be "S" on a US QWERTY keyboard. Move backward! */
    }
 }

    return SDL_APP_CONTINUE;
}


void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    AppState* app_state = (AppState*)appstate;
    if (app_state->devices != NULL) {
        SDL_free(app_state->devices);
    }
    if (app_state->camera != NULL) {
        SDL_CloseCamera(app_state->camera);
    }
    if (app_state->texture != NULL) {
        SDL_DestroyTexture(app_state->texture);
    }
    // Free centroids array
    if (app_state->centroids != NULL) {
        free(app_state->centroids);
    }

//TTF_CloseFont(app_state->font);

    free(app_state);
}