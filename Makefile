# Compiler
CC = gcc

# Paths
INCLUDE_DIR = C:\msys64\mingw64\include
LIB_DIR = C:\msys64\mingw64\lib

# Compiler Flags
CFLAGS = -I"$(INCLUDE_DIR)"
LDFLAGS = -L"$(LIB_DIR)" -fopenmp -O3 -lmingw32 -lSDL3 -lSDL3_ttf

# Targets
TARGETS = kmeans.exe

# Sources
KMEANS_SRC = kmeans.c
KMEANS_HDR = kmeans.h

# Build Rule
all: $(TARGETS)

# Explicit dependency on kmeans.h
kmeans.exe: $(KMEANS_SRC) $(KMEANS_HDR)
	$(CC) $(KMEANS_SRC) -o kmeans.exe $(CFLAGS) $(LDFLAGS)

# Clean Rule
clean:
	del /Q $(TARGETS)
