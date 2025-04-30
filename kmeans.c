// #ifdef _MSC_VER
//    #define _CRT_SECURE_NO_WARNINGS
// #endif
// #define SDL_MAIN_USE_CALLBACKS 1
// #include <SDL3/SDL.h>
// #include <SDL3/SDL_main.h>
// #include <stdio.h>
// #include <stdlib.h>
// typedef struct {
//     SDL_Window* window;
//     SDL_Renderer* renderer;
//     SDL_CameraID* devices;
//     SDL_Camera* camera;
//     SDL_Texture* texture;
  
//     int width;
//     int height;
//     int camera_count;
// } AppState;
// SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv) {
//     AppState* app_state = malloc(sizeof(AppState));
//     *app_state = (AppState){
//         .width = 800,
//         .height = 600
//     };
//     *appstate = app_state;

//     if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_CAMERA)) {
//         SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
//         return SDL_APP_FAILURE;
//     }

//     if (!SDL_CreateWindowAndRenderer("SDL3 Camera Demo", app_state->width, app_state->height, 0, &(app_state->window), &(app_state->renderer))) {
//         SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
//         return SDL_APP_FAILURE;
//     }

//     SDL_CameraID* devices = SDL_GetCameras(&app_state->camera_count);
//     app_state->devices = devices;

//     SDL_Log("Found %d cameras!", app_state->camera_count);

//     // Open first camera
//     app_state->camera = SDL_OpenCamera(devices[0], NULL);
//     if (app_state->camera == NULL) {
//         SDL_Log("Can't open the selected camera: %s", SDL_GetError());
//         return SDL_APP_FAILURE;
//     }

//     // Get the selected camera format
//     SDL_CameraSpec spec;
//     SDL_GetCameraFormat(app_state->camera, &spec);
//     int FPS = spec.framerate_numerator / spec.framerate_denominator;
//     SDL_Log("Got a camera of %dx%d and FPS %d", spec.width, spec.height, FPS);

//     return SDL_APP_CONTINUE;
// }


// SDL_AppResult SDL_AppIterate(void* appstate) {
//       SDL_PropertiesID props;
//     AppState* app_state = (AppState*)appstate;
//     SDL_Surface* frame = SDL_AcquireCameraFrame(app_state->camera, NULL);
//     if (frame != NULL) {
//         if (app_state->texture == NULL) {
//             SDL_SetWindowSize(app_state->window,frame->w,frame->h);
//             app_state->width=frame->w;
//             app_state->height=frame->h;
//             app_state->texture = SDL_CreateTexture(app_state->renderer, frame->format, SDL_TEXTUREACCESS_STREAMING, frame->w, frame->h);
//         } else {
//             SDL_UpdateTexture(app_state->texture, NULL, frame->pixels, frame->pitch);
           

//         }
    
//         SDL_ReleaseCameraFrame(app_state->camera, frame);
        

//              props = SDL_GetTextureProperties(app_state->texture);

         

           
// typedef enum SDL_Colorspace
// {
  

//     SDL_COLORSPACE_RGB_DEFAULT = SDL_COLORSPACE_SRGB, /**< The default colorspace for RGB surfaces if no colorspace is specified */
//     SDL_COLORSPACE_YUV_DEFAULT = SDL_COLORSPACE_JPEG  /**< The default colorspace for YUV surfaces if no colorspace is specified */
// } SDL_Colorspace;
            
            




//     }
        
//     SDL_SetRenderDrawColorFloat(app_state->renderer, 0.3f, 0.5f, 1.0f, SDL_ALPHA_OPAQUE_FLOAT);
//     SDL_RenderClear(app_state->renderer);

   
// SDL_Colorspace s=SDL_GetNumberProperty(props, SDL_PROP_TEXTURE_COLORSPACE_NUMBER, 0);

    
//     if (props == 0) {
//         printf("Failed to get texture properties: %s\n", SDL_GetError());
//        return  SDL_APP_FAILURE;
//     }
    
//     // Access texture properties
//     int format = SDL_GetNumberProperty(props, SDL_PROP_TEXTURE_FORMAT_NUMBER, 0);
//     int access = SDL_GetNumberProperty(props, SDL_PROP_TEXTURE_ACCESS_NUMBER, 0);
//     int width = SDL_GetNumberProperty(props, SDL_PROP_TEXTURE_WIDTH_NUMBER, 0);
//     int height = SDL_GetNumberProperty(props, SDL_PROP_TEXTURE_HEIGHT_NUMBER, 0);
//     int colorspace = SDL_GetNumberProperty(props, SDL_PROP_TEXTURE_COLORSPACE_NUMBER, 0);
//     float sdr_white = SDL_GetFloatProperty(props, SDL_PROP_TEXTURE_SDR_WHITE_POINT_FLOAT, 1.0f);
//     float hdr_headroom = SDL_GetFloatProperty(props, SDL_PROP_TEXTURE_HDR_HEADROOM_FLOAT, 1.0f);
    
//     printf("Texture Properties:\n");
//     printf("- Format: %d\n", format);
//     printf("- Access: %d\n", access);
//     printf("- Size: %dx%d\n", width, height);
//     printf("- Colorspace: %d\n", colorspace);
//     printf("- SDR White Point: %.2f\n", sdr_white);
//     printf("- HDR Headroom: %.2f\n", hdr_headroom);
//     SDL_GetRGB();
    
// //     SDL_Rect pixelRect;
// // pixelRect.x = 250;
// // pixelRect.y = 250;
// // pixelRect.w = 1;
// // pixelRect.h = 1;

// // SDL_Surface* pixelSurface = SDL_RenderReadPixels(app_state->renderer, &pixelRect);
// // if (pixelSurface != NULL)
// // {
// // 	Uint8 red;
// // 	Uint8 green;
// // 	Uint8 blue;
	
// // 	Uint32 pixelValue = *((Uint32*) pixelSurface->pixels);
// // 	SDL_GetRGB(pixelValue, pixelSurface->format, NULL,&red, &green, &blue);
// // 	SDL_DestroySurface(pixelSurface);
	
// // 	printf("Red: %d, Green: %d, Blue: %d\n", red, green, blue);
// // }

// //SDL_GetTextureProperties(app_state->texture);
//     if (app_state->texture) {
//         SDL_RenderTexture(app_state->renderer, app_state->texture, NULL, NULL);
//     }
//     SDL_RenderPresent(app_state->renderer);
//     return SDL_APP_CONTINUE;
// }

// SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
//     if (event->type == SDL_EVENT_QUIT) {
//         return SDL_APP_SUCCESS;
//     }
//     return SDL_APP_CONTINUE;
// }

// void SDL_AppQuit(void* appstate, SDL_AppResult result) {
//     AppState* app_state = (AppState*)appstate;
//     if (app_state->devices != NULL) {
//         SDL_free(app_state->devices);
//     }
//     if (app_state->camera != NULL) {
//         SDL_CloseCamera(app_state->camera);
//     }
//     if (app_state->texture != NULL) {
//         SDL_DestroyTexture(app_state->texture);
//     }
//     free(app_state);
// }
#ifdef _MSC_VER
   #define _CRT_SECURE_NO_WARNINGS
#endif
#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_CameraID* devices;
    SDL_Camera* camera;
    SDL_Texture* texture;
    int width;
    int height;
    int camera_count;
    bool texture_valid;  // Flag to track if the texture is valid
    int frame_count;     // Counter for frames
} AppState;

// Function to dump pixel data for analysis
void AnalyzePixels(SDL_Texture* texture, SDL_Renderer* renderer) {
    // Skip if texture is not valid
    if (!texture) return;
    
    // Get texture dimensions
    int width, height;
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    
    if (width <= 0 || height <= 0) {
        SDL_Log("Invalid texture dimensions: %dx%d", width, height);
        return;
    }
    
    // Lock the texture to access pixels directly
    void* pixels;
    int pitch;
    
    if (SDL_LockTexture(texture, NULL, &pixels, &pitch) == 0) {
        // Sample pixels at specific locations
        int sample_points[5][2] = {
            {width/2, height/2},           // Center
            {width/4, height/4},           // Top-left quadrant
            {width*3/4, height/4},         // Top-right quadrant
            {width/4, height*3/4},         // Bottom-left quadrant
            {width*3/4, height*3/4}        // Bottom-right quadrant
        };
        
        // Assume RGBA8888 format (most common)
        Uint8* p = (Uint8*)pixels;
        SDL_Log("Sampling pixels at key points:");
        
        // Detect if there's meaningful visual data
        bool has_data = false;
        int max_diff = 0;
        
        for (int i = 0; i < 5; i++) {
            int x = sample_points[i][0];
            int y = sample_points[i][1];
            
            // Calculate offset in the pixel array
            int offset = y * pitch + x * 4;  // Assuming 4 bytes per pixel
            
            // Check if offset is within bounds
            if (offset + 4 <= pitch * height) {
                Uint8 r = p[offset];
                Uint8 g = p[offset+1];
                Uint8 b = p[offset+2];
                Uint8 a = p[offset+3];
                
                SDL_Log("Point %d (%d,%d): R=%d, G=%d, B=%d, A=%d", 
                       i, x, y, r, g, b, a);
                       
                // Check for variance between channels
                int diff = abs(r - g) + abs(r - b) + abs(g - b);
                if (diff > max_diff) max_diff = diff;
                
                // If any channel has significant value, we have data
                if (r > 20 || g > 20 || b > 20) {
                    has_data = true;
                }
            }
        }
        
        SDL_Log("Max color difference: %d, Has visible data: %s", 
               max_diff, has_data ? "yes" : "no");
        
        SDL_UnlockTexture(texture);
    } else {
        SDL_Log("Failed to lock texture: %s", SDL_GetError());
    }
}

SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv) {
    AppState* app_state = malloc(sizeof(AppState));
    *app_state = (AppState){
        .width = 800,
        .height = 600,
        .texture_valid = false,
        .frame_count = 0
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

    if (app_state->camera_count == 0) {
        SDL_Log("No cameras found!");
        return SDL_APP_FAILURE;
    }

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
    AppState* app_state = (AppState*)appstate;
    
    // Increment frame counter
    app_state->frame_count++;
    
    // Acquire a new frame from the camera
    SDL_Surface* frame = SDL_AcquireCameraFrame(app_state->camera, NULL);
    if (frame != NULL) {
        SDL_Log("Frame acquired: %dx%d, format: %d", frame->w, frame->h, frame->format);
        
        // If we don't have a texture or it's the wrong size, create a new one
        if (app_state->texture == NULL || 
            app_state->width != frame->w || 
            app_state->height != frame->h) {
            
            // Destroy old texture if it exists
            if (app_state->texture != NULL) {
                SDL_DestroyTexture(app_state->texture);
                app_state->texture = NULL;
            }
            
            // Create new texture with the right dimensions
            SDL_SetWindowSize(app_state->window, frame->w, frame->h);
            app_state->width = frame->w;
            app_state->height = frame->h;
            app_state->texture = SDL_CreateTexture(app_state->renderer, frame->format, 
                                                  SDL_TEXTUREACCESS_STREAMING, frame->w, frame->h);
            
            if (app_state->texture == NULL) {
                SDL_Log("Failed to create texture: %s", SDL_GetError());
                app_state->texture_valid = false;
            } else {
                SDL_Log("New texture created: %dx%d, format: %d", 
                       frame->w, frame->h, frame->format);
                app_state->texture_valid = true;
            }
        }
        
        // Update the texture with the new frame data
        if (app_state->texture != NULL) {
            int result = SDL_UpdateTexture(app_state->texture, NULL, frame->pixels, frame->pitch);
            if (result != 0) {
                SDL_Log("Failed to update texture: %s", SDL_GetError());
                app_state->texture_valid = false;
            } else {
                app_state->texture_valid = true;
            }
        }
        
        SDL_ReleaseCameraFrame(app_state->camera, frame);
    } else {
        SDL_Log("Failed to acquire camera frame: %s", SDL_GetError());
    }

    // Only proceed with texture operations if we have a valid texture
    if (app_state->texture_valid) {
        SDL_PropertiesID props = SDL_GetTextureProperties(app_state->texture);
        if (props != 0) {
            int width = SDL_GetNumberProperty(props, SDL_PROP_TEXTURE_WIDTH_NUMBER, 0);
            int height = SDL_GetNumberProperty(props, SDL_PROP_TEXTURE_HEIGHT_NUMBER, 0);
            int format = SDL_GetNumberProperty(props, SDL_PROP_TEXTURE_FORMAT_NUMBER, 0);
            int access = SDL_GetNumberProperty(props, SDL_PROP_TEXTURE_ACCESS_NUMBER, 0);
            int colorspace = SDL_GetNumberProperty(props, SDL_PROP_TEXTURE_COLORSPACE_NUMBER, 0);
            
            if (app_state->frame_count % 30 == 0) {  // Print every 30 frames
                SDL_Log("Texture Properties:");
                SDL_Log("- Format: %d", format);
                SDL_Log("- Access: %d", access);
                SDL_Log("- Size: %dx%d", width, height);
                SDL_Log("- Colorspace: %d", colorspace);
                
                // Analyze pixels to see what's going on
                AnalyzePixels(app_state->texture, app_state->renderer);
            }
        } else {
            SDL_Log("Failed to get texture properties: %s", SDL_GetError());
            app_state->texture_valid = false;
        }
    }

    // Draw the scene
    SDL_SetRenderDrawColorFloat(app_state->renderer, 0.3f, 0.5f, 1.0f, SDL_ALPHA_OPAQUE_FLOAT);
    SDL_RenderClear(app_state->renderer);

    if (app_state->texture_valid) {
        SDL_RenderTexture(app_state->renderer, app_state->texture, NULL, NULL);
    } else {
        // Draw a placeholder or error message if texture isn't valid
        SDL_SetRenderDrawColorFloat(app_state->renderer, 1.0f, 0.0f, 0.0f, SDL_ALPHA_OPAQUE_FLOAT);
        SDL_FRect rect = {app_state->width/4, app_state->height/4, app_state->width/2, app_state->height/2};
        SDL_RenderFillRect(app_state->renderer, &rect);
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