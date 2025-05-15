/*#include <SDL3/SDL.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("Linked SDL version: %s\n", SDL_GetRevision());
    printf("Compiled SDL version: %d.%d.%d\n",
        SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_MICRO_VERSION
    );
    return 0;
}
*/
// #include <SDL3/SDL.h> // Uncomment if using SDL
#include <stdio.h>
#include <stdlib.h>  // Needed for calloc
#include "test.h"

#define N 20
#define D 3
#define K 2

int main() {
    //  int N = 20; /*Size of data|| Initializing at -1 because our finder always count the last \n*/
    // unsigned int K = 2; /* Amount of clusters to be created,input given by the user */
    // unsigned int D = 3; 
    // Allocate space for N (rows) * D (features)
    float *DataArray = (float*)calloc(N * D, sizeof(float));
int *Location = (int*)calloc(N+(D*K) , sizeof(int));
    if (DataArray == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize data manually (as you had 20x3 values)
    float initData[N * D] = {
       100 ,100,100,
       100 ,100,100,
       100 ,100,100,
       100 ,100,100,
       100 ,100,100,
       200,200,200,
       200,200,200,
       200,200,200,
       200,200,200,
       200,200,200,
       200,200,200,
       200,200,200,
       200,200,200,
       200,200,200,
       200,200,200,
       200,200,200,
       200,200,200,
       200,200,200,
       200,200,200,
       200,200,200,

    };

    // Copy initData into allocated memory
    for (int i = 0; i < N * D; ++i) {
        DataArray[i] = initData[i];
    }

    // Call clustering function
      Location=kmeans2(DataArray,Location,N,D,K);  // Make sure this function is correctly defined in test.h

    // Free memory
    free(DataArray);
    for(int i=0;i<N;i++)
  printf("%d ",Location[i]);
  for(int i=N;i<N+(K*D);i++)
  printf("centroidds: %d",Location[i]);
 free(Location);
    return 0;
}
