# Compiler
CC = gcc

# Paths
INCLUDE_DIR = C:\msys64\mingw64\include
LIB_DIR = C:\msys64\mingw64\lib

# Compiler Flags
CFLAGS = -I"$(INCLUDE_DIR)"
LDFLAGS = -L"$(LIB_DIR)" -lmingw32 -lSDL3 -lSDL3_ttf

# Targets
TARGETS = kmeans.exe sample.exe

# Sources
KMEANS_SRC = kmeans.c
SAMPLE_SRC = sample.c

# Build Rule
all: $(TARGETS)

kmeans.exe: $(KMEANS_SRC)
	$(CC) $(KMEANS_SRC) -o kmeans.exe $(CFLAGS) $(LDFLAGS)

sample.exe: $(SAMPLE_SRC)
	$(CC) $(SAMPLE_SRC) -o sample.exe $(CFLAGS) $(LDFLAGS)

# Clean Rule
clean:
	del /Q $(TARGETS)
