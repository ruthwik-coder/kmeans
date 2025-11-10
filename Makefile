# Compiler
CC = gcc

# Automatically detect SDL3 paths
SDL3_CFLAGS := $(shell pkg-config --cflags sdl3 SDL3_ttf 2>nul || echo -I"C:\msys64\mingw64\include")
SDL3_LIBS := $(shell pkg-config --libs sdl3 SDL3_ttf 2>nul || echo -L"C:\msys64\mingw64\lib" -lSDL3 -lSDL3_ttf)

# Compiler Flags
CFLAGS = $(SDL3_CFLAGS) -fopenmp -O3
LDFLAGS = -lmingw32 $(SDL3_LIBS)

# Targets
TARGETS = kmeans.exe

# Sources
KMEANS_SRC = kmeans.c
KMEANS_HDR = kmeans.h

# Build Rule
all: $(TARGETS)

kmeans.exe: $(KMEANS_SRC) $(KMEANS_HDR)
	$(CC) $(KMEANS_SRC) -o kmeans.exe $(CFLAGS) $(LDFLAGS)

clean:
	del /Q $(TARGETS) 2>nul || echo Clean complete

.PHONY: all clean
