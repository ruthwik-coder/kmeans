#ifndef test_h
#define test_h  
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#define MAX_SIZE 100
#define FLAG_MAX 9999
#define PREVIOUS_FILES 100

#endif
/*Sorry for Caps */
/*CURRENT VERSION WORKS WITHOUT HEADER FILES AND FUNCTIONS, IT'S WRITTEN THIS WAY
FOR EASE OF USING AND READING OF RAW CODE*/

int* kmeans2(float DataArray[],int Location[],int N,unsigned D,unsigned K) {

    /* Starting Variables */
    // int N = 20; /*Size of data|| Initializing at -1 because our finder always count the last \n*/
    // unsigned int K = 2; /* Amount of clusters to be created,input given by the user */
    // unsigned int D = 3; /* Number of features(dimensions) */
  //  srand(time(NULL));/*True Random*/
    unsigned int randVar = 0;/*Variable for picking random initial Centroids*/
    unsigned int iteration = 0;/*Amount of algorithm's iterations counter*/
    int flagEnd = 0;/*Initializing flag variable for do-while break*/
    clock_t start, end; //Timers

    /*(loop var) i is used for N, j is used for K,d is used for D */
    register int i; //Elements
    register int j; //Clusters
    register int d; //Features



    // /*------------Finding the number of features from the dataset -----------------*/


    int flag = 0;/*temp flag */
    int flagPrev = 0;/*Holder of previous iteration's flag */
 
    /*-----------------------------*/

    /*------Memory Allocation-----*/
    // float *DataArray;//Main Array for loading the initial Data
    // DataArray = (float*)calloc(N*D,sizeof(float));/*Allocating space for N(rows) * D(features) */

    float *Centroids;/*Array holding Centroids throughout the execution of the algorithm*/
    Centroids = (float*)calloc(K*D,sizeof(float));/*Allocating space for K(clusters) * D(features) */

    float *FlagCentroids;/*Array for holding Centroids of a previous iteration,used in loop testing */
    FlagCentroids = (float*)calloc(K*D,sizeof(float));/*Same allocation as line:120*/

    int *Counter;/*Array for holding the counter about how many elements each cluster has */
    Counter = (int*)calloc(K,sizeof(int));/*Allocating space the same as K(clusters)*/

    float *ClusterTotalSum;/*Array for holding the total sum of each cluster*/
    ClusterTotalSum = (float*)calloc(K*D,sizeof(float));/*Allocating space for K(rows) and D(features)*/

    float *Distance;/*Array for holding the distance between each element from each Centroid*/
    Distance = (float*)calloc(N*K,sizeof(float));/*Allocating space for N(elements) * K(Centroids)*/

    float *Min;/*Array for holding the min Distance*/
    Min = (float*)calloc(N,sizeof(float));

    // int *Location;/*Array holding each element's location(cluster)*/
    // Location = (int*)calloc(N,sizeof(int));


    /*--------------------------*/

    /*---------Loading Data---------*/
    // for(i = 0; i < N; ++i)
    // {
    //   for(d = 0; d < D; ++d)
    //    // fscanf(Dataset,"%f,",&DataArray[i*D + d]);/*"%f," is c undefined behaviour */

    // }
    //fclose(Dataset);//Closing the initial Data File
    /*--------------------------*/

    /*--------Generating Initial Random Centroids-----*/
    // --- k-means++ initialization ---
Centroids[0*D + 0] = DataArray[0*D + 0];
for (d = 1; d < D; ++d)
    Centroids[0*D + d] = DataArray[0*D + d];

// Array to store the minimum squared distance to any centroid so far
float *minDistSq = (float*)calloc(N, sizeof(float));
if (!minDistSq) { printf("Memory error\n"); exit(1); }

for (i = 0; i < N; ++i) {
    float dist = 0.0;
    for (d = 0; d < D; ++d)
        dist += (DataArray[i*D + d] - Centroids[0*D + d]) * (DataArray[i*D + d] - Centroids[0*D + d]);
    minDistSq[i] = dist;
}

// Select the rest K-1 centroids
for (j = 1; j < K; ++j) {
    // 1. Compute total of minDistSq
    float total = 0.0;
    for (i = 0; i < N; ++i)
        total += minDistSq[i];

    // 2. Pick a random value in [0, total)
    float r = ((float)rand() / RAND_MAX) * total;

    // 3. Find the data point at or just above this value
    float cumSum = 0.0;
    int nextCentroid = N-1; // fallback
    for (i = 0; i < N; ++i) {
        cumSum += minDistSq[i];
        if (cumSum >= r) {
            nextCentroid = i;
            break;
        }
    }

    // 4. Assign this as the next centroid
    for (d = 0; d < D; ++d)
        Centroids[j*D + d] = DataArray[nextCentroid*D + d];

    // 5. Update minDistSq for all points
    for (i = 0; i < N; ++i) {
        float dist = 0.0;
        for (d = 0; d < D; ++d)
            dist += (DataArray[i*D + d] - Centroids[j*D + d]) * (DataArray[i*D + d] - Centroids[j*D + d]);
        if (dist < minDistSq[i])
            minDistSq[i] = dist;
    }
}

// Copy Centroids to FlagCentroids
for (j = 0; j < K; ++j)
    for (d = 0; d < D; ++d)
        FlagCentroids[j*D + d] = Centroids[j*D + d];

free(minDistSq);
// --- end k-means++ initialization ---

      /*--------------------------*/

start = clock();
  /*--Initializing the algoritm---*/
    do {

      /*For every iteration after the initial one resets the counter and sums to 0*/
      if(iteration > 0)
      {
        for(j = 0; j < K; ++j)
        {
          Counter[j] = 0;//Resets counter array to 0
          for(d = 0; d < D; ++d)
          {
            ClusterTotalSum[j*D + d] = 0;//Resets Sum of each cluster to 0
          }
        }
      }

      for(i = 0; i < N; ++i)
      {
        Min[i] = FLAG_MAX;
        for(j = 0; j < K; ++j)
        {
          Distance[i*K + j] = 0;/*Reseting Distance at every iteration to 0 to calculate new ones */
          for(d = 0; d < D; ++d)
          {
            /*Calculating distance for each element from each centroid by using sqrt(pow((x-y),2))*/
            Distance[i*K + j] +=((DataArray[i*D + d] - Centroids[j*D + d])*(DataArray[i*D + d] - Centroids[j*D + d]));
          }
          Distance[i*K + j] = sqrt(Distance[i*K + j]);/*Getting the sqrt of the total features distance*/

         /*Everytime it finds a distance Smaller than previous it stores it's cluster location*/
          if(Distance[i*K + j] < Min[i])
          {
            Min[i] = Distance[i*K + j];
            Location[i] = j;
          }
        }
  /*For every element's  j(current Cluster)==location add it to Cluster's total sum
  and increase counter by 1 for the corresponding cluster */
        for(j = 0; j < K; ++j)
        {
          if(Location[i] == j)
          {
            for(d = 0; d < D; ++d)
            {
              ClusterTotalSum[j*D + d] += DataArray[i*D + d];
            }
            ++Counter[j];
          }
        }
      }

 /*Calculate new Centroids by dividing each feature sum with Counter */
      for(j = 0; j < K; ++j)
      {
        for(d = 0; d < D; ++d)
        {
          Centroids[j*D + d] = ClusterTotalSum[j*D +d]/Counter[j];
        }
      }

/*If even one feature of flag is different than the equal to Centroids
it set's flagEnd to 0 and breaks the nested for loop and follows with an if to
break the parent for loop. If all features are equal then set flagEnd to -1 which
breaks the do-while loop */
      for(j = 0; j < K; ++j)
      {
        for(d = 0; d < D; ++d)
        {
          if(FlagCentroids[j*D + d] != Centroids[j*D + d])
          {
            flagEnd = 0;
             break;
          }else
          {
            flagEnd = -1;
          }
          
        }

        if(flagEnd == 0)
          break;
      }


/*Copy new Centroids to FlagCentroids */
      for(j = 0; j < K; ++j)
      {
        for(d = 0; d < D; ++d)
        {
          FlagCentroids[j*D + d] = Centroids[j*D + d];
        }
      }

      ++iteration;

    } while(flagEnd != -1);

    end = clock();

    printf("\n Iterations : %d\n",iteration );
    double total_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\n Time of Algorithm Execution: %lf \n\n",total_time);

    
for (int j = 0; j < K * D; ++j) {
    Location[N + j] = Centroids[j];
}

  //  free(DataArray);
    free(Centroids);
    free(FlagCentroids);
    free(Counter);
    free(ClusterTotalSum);
    free(Distance);
    free(Min);
    return(Location);
    //free(Location);
   // free(OutputArray);

 // return 0;
}
