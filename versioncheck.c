#include <SDL3/SDL.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("Linked SDL version: %s\n", SDL_GetRevision());
    printf("Compiled SDL version: %d.%d.%d\n",
        SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_MICRO_VERSION
    );
    return 0;
}
