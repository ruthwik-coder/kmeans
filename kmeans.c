#ifdef _MSC_VER
   #define _CRT_SECURE_NO_WARNINGS
#endif
#define SDL_MAIN_USE_CALLBACKS 1
 #include <SDL3/SDL.h>
 #include <SDL3/SDL_main.h>
 #include <SDL3_ttf/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#define MY_FONT "C:\\Windows\\Fonts\\arial.ttf"
#define SDL_MESSAGEBOX_ERROR                    0x00000010u
typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_CameraID* devices;
    SDL_Camera* camera;
    SDL_Texture* texture;
    
    //TTF_Font *font ;
  float cam_x, cam_y, cam_w, cam_h;
bool dragging;
float drag_offset_x, drag_offset_y;

    int width;
    int height;
    int camera_count;
} AppState ;
SDL_Rect camera_viewport = {20, 20, 320, 240}; // Initial small position/size
bool resizing = false;
int resize_margin = 10;


SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv) {
    //   TTF_Init();
      
    //    if (TTF_Init() < 0) {
    //     printf("SDL_ttf could not initialize! TTF_Error: %s\n", SDL_GetError());
    //     return SDL_APP_FAILURE;
    //    }
     
    AppState* app_state = malloc(sizeof(AppState));
    *app_state = (AppState){
        .width = 800,
        .height = 600
    };
    *appstate = app_state;
 //app_state->font= TTF_OpenFont(MY_FONT, 50);
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


SDL_AppResult SDL_AppIterate(void* appstate) {
    
             // Dynamically allocate memory for the 2D array using malloc
   int **a = (int **)malloc(1280 * sizeof(int  *));  
    
     int **a2 = (int**)malloc(1280 * sizeof(int *));  
    // Allocate memory for row pointers
    if ((a == NULL) ||a2==NULL) {
        printf("Memory allocation failed for rows!\n");
        return 1;  // Return with an error code if memory allocation fails
    }


    // Allocate memory for each row
    for (int i = 0; i < 1280; i++) {
        a[i] = (int *)malloc(720 * sizeof(int));
          a2[i] = (int *)malloc(720 * sizeof(int));
        if ((a[i] == NULL) ||a2[i]==NULL) {
            printf("Memory allocation failed for row %d!\n", i);
            return 1;  // Return with an error code if memory allocation fails
        }
    }

      SDL_PropertiesID props;
    AppState* app_state = (AppState*)appstate;
    SDL_Surface* frame = SDL_AcquireCameraFrame(app_state->camera, NULL);
    if (frame != NULL) {
        if (app_state->texture == NULL) {
            SDL_SetWindowSize(app_state->window,frame->w,frame->h);
            app_state->width=frame->w;
            app_state->height=frame->h;
            app_state->texture = SDL_CreateTexture(app_state->renderer, frame->format, SDL_TEXTUREACCESS_STREAMING, frame->w, frame->h);
        } else {
            SDL_UpdateTexture(app_state->texture, NULL, frame->pixels, frame->pitch);
      

        }


 props = SDL_GetTextureProperties(app_state->texture);
        
    if (props == 0) {
        printf("Failed to get texture properties: %s\n", SDL_GetError());
       return  SDL_APP_FAILURE;
    }
    
    // Access texture properties
    int format = SDL_GetNumberProperty(props, SDL_PROP_TEXTURE_FORMAT_NUMBER, 0);
    int access = SDL_GetNumberProperty(props, SDL_PROP_TEXTURE_ACCESS_NUMBER, 0);
    int width = SDL_GetNumberProperty(props, SDL_PROP_TEXTURE_WIDTH_NUMBER, 0);
    int height = SDL_GetNumberProperty(props, SDL_PROP_TEXTURE_HEIGHT_NUMBER, 0);
    int colorspace = SDL_GetNumberProperty(props, SDL_PROP_TEXTURE_COLORSPACE_NUMBER, 0);

SDL_Surface* rgb_frame = SDL_ConvertSurface(frame, SDL_PIXELFORMAT_RGB24);
if (rgb_frame) {
    Uint8* pixels = (Uint8*)rgb_frame->pixels;
    int pitch = rgb_frame->pitch;
    for (int y = 0; y < rgb_frame->h; y += 20) {
        for (int x = 0; x < rgb_frame->w; x += 20) {
            int index = y * pitch + x * 3;

            Uint8 r = pixels[index];
            Uint8 g = pixels[index + 1];
            Uint8 b = pixels[index + 2];
              a[y][x] = r;
                a2[y][x] = g;

          // printf("Pixel[%d][%d] = R:%d G:%d B:%d\n", y, x, r, g, b);
        }
    }
    SDL_DestroySurface(rgb_frame);  // Free when done
}


        SDL_ReleaseCameraFrame(app_state->camera, frame);
    }
        
     SDL_SetRenderDrawColorFloat(app_state->renderer, 0.3f, 0.5f, 1.0f, SDL_ALPHA_OPAQUE_FLOAT);
    SDL_RenderClear(app_state->renderer);

SDL_FRect camera_viewport_f = {
    .x = (float)camera_viewport.x,
    .y = (float)camera_viewport.y,
    .w = (float)camera_viewport.w,
    .h = (float)camera_viewport.h
};

      SDL_RenderTexture(app_state->renderer,app_state->texture, NULL, &camera_viewport_f);

// Render all points at once
//SDL_RenderPoints(app_state->renderer, points, 100);
    // Free the allocated memory
    for (int i = 0; i < 1280; i++) {
        free(a[i]);
        free (a2[i]) ; // Free each row
    }
    
    free(a); 
    free(a2); // Free the row pointers
 
    SDL_RenderPresent(app_state->renderer);
   //  SDL_DestroySurface(textSurface);
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
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

//TTF_CloseFont(app_state->font);

    free(app_state);
}

           