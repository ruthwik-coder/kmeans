# Implementing K-Means algorithm on real-time Camera Frames in SDL3 

A real-time computer vision application that applies K-means clustering to live camera feeds for color quantization and palette extraction.

## Overview

This application captures video from your webcam and performs K-means clustering on each frame to reduce the image to K dominant colors. The clustered colors are displayed as a sorted palette bar at the bottom of the window, ordered from darkest to lightest by luminance.

## Features

- **Real-time K-means clustering** on live camera feed
- **Dynamic K adjustment** - Change the number of color clusters on the fly
- **Resizable viewport** - Adjust camera display dimensions during runtime
- **Color palette visualization** - Sorted by luminance for easy analysis
- **Efficient processing** - Optimized K-means implementation for real-time performance

### Implementation

- **Graphics Library**: SDL3 (with SDL3_ttf for text rendering)
- **Clustering Algorithm**: K-means (source: [Michael-Gkotsis/k-means](https://github.com/Michael-Gkotsis/k-means))
- **Color Space**: RGB24
- **Inspiration**: [Webcam K-means by Ricky Reusser](https://rreusser.github.io/webcam-kmeans/)
# Note
The program uses OpenMP for parallel processing , hence increasing the K-value will increase your CPU usage
### Algorithm

The K-means implementation clusters pixels in RGB color space, iteratively assigning each pixel to the nearest centroid and recalculating centroids until convergence. Each frame is processed independently, with the resulting cluster centroids used to replace pixel colors for visualization.

## Controls

|Key|Action|
|---|---|
|`Numpad +`|Increase K (add color cluster)|
|`Numpad -`|Decrease K (remove color cluster)|
|`M`|Increase viewport width|
|`N`|Increase viewport height|
|`J`|Decrease viewport width|
|`K`|Decrease viewport height|

## Requirements

- SDL3
- SDL3_ttf
- Camera/webcam device
- Arial font (Windows: `C:\Windows\Fonts\arial.ttf`)

## Building

```bash
git clone https://github.com/ruthwik-coder/kmeans.git
cd kmeans
make
```

If that doesn't work ,
Go to your make file in the SDL3_CFLAGS , SDL3_LIBS section , replace the path with the
SDL3 include and library in your system.
Or,

```bash
gcc kmeans.c -o kmeans.exe -fopenmp -O3 -lmingw32 -lSDL3 -lSDL3_ttf && kmeans
```


Make sure to have SDL3.dll and SDL3_ttf.dll in the same directory as your executable , if you're on Windows.

Screenshot from Progam:
<img width="1286" height="767" alt="image" src="https://github.com/user-attachments/assets/95ed804e-670f-490a-8824-6c74df449fa4" />

## Acknowledgments

- K-means algorithm based on work by [Michael Gkotsis](https://github.com/Michael-Gkotsis/k-means)
- Inspired by [Ricky Reusser's Webcam K-means visualization](https://rreusser.github.io/webcam-kmeans/)
