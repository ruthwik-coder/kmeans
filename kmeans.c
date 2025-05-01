#ifdef _MSC_VER
   #define _CRT_SECURE_NO_WARNINGS
#endif
#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_CameraID* devices;
    SDL_Camera* camera;
    SDL_Texture* texture;
  
    int width;
    int height;
    int camera_count;
} AppState;
SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv) {
    AppState* app_state = malloc(sizeof(AppState));
    *app_state = (AppState){
        .width = 800,
        .height = 600
    };
    *appstate = app_state;

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_CAMERA)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

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
printf(".. \n");

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



//         Uint32* pixels = (Uint32*)frame->pixels;
       
//         int pitch = frame->pitch / 4; // pitch is in bytes; divide by 4 for Uint32
// printf("Camera Frame Format: %s\n", SDL_GetPixelFormatName(frame->format));
//         for (int y = 0; y < height; ++y) {
//             for (int x = 0; x < width; ++x) {
//                 Uint32 pixel = pixels[y * pitch + x];
//                 Uint8 r, g, b, a;
//                 SDL_GetRGBA(pixel, SDL_GetPixelFormatDetails(frame->format),0,&r, &g, &b,&a);
//                 //printf("Pixel[%d][%d] = R:%d G:%d B:%d A:%d\n", y, x, r, g, b,a);
//                // printf("%d \n",r);
//             }

//         }
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
            

          //  printf("Pixel[%d][%d] = R:%d G:%d B:%d\n", y, x, r, g, b);
        }
    }
    SDL_DestroySurface(rgb_frame);  // Free when done
}

    // printf("Texture Properties:\n");
    // printf("- Format: %d\n", format);
    // printf("- Access: %d\n", access);
    // printf("- Size: %dx%d\n", width, height);
    // printf("- Colorspace: %d\n", colorspace);
    // printf("- SDR White Point: %.2f\n", sdr_white);
    // printf("- HDR Headroom: %.2f\n", hdr_headroom);
    //SDL_GetRGB();

        SDL_ReleaseCameraFrame(app_state->camera, frame);
    }
        
     SDL_SetRenderDrawColorFloat(app_state->renderer, 0.3f, 0.5f, 1.0f, SDL_ALPHA_OPAQUE_FLOAT);
    SDL_RenderClear(app_state->renderer);



    
//     SDL_Rect pixelRect;
// pixelRect.x = 250;
// pixelRect.y = 250;
// pixelRect.w = 1;
// pixelRect.h = 1;

// SDL_Surface* pixelSurface = SDL_RenderReadPixels(app_state->renderer, &pixelRect);
// if (pixelSurface != NULL)
// {
// 	Uint8 red;
// 	Uint8 green;
// 	Uint8 blue;
	
// 	Uint32 pixelValue = *((Uint32*) pixelSurface->pixels);
// 	SDL_GetRGB(pixelValue, pixelSurface->format, NULL,&red, &green, &blue);
// 	SDL_DestroySurface(pixelSurface);
	
// 	printf("Red: %d, Green: %d, Blue: %d\n", red, green, blue);
// }

//SDL_GetTextureProperties(app_state->texture);
    if (app_state->texture) {
        SDL_RenderTexture(app_state->renderer, app_state->texture, NULL, NULL);
    }
    SDL_RenderPresent(app_state->renderer);
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
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
    free(app_state);
}

           