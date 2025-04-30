# Compiler
CC = gcc

# Paths
INCLUDE_DIR = C:\msys64\mingw64\include
LIB_DIR = C:\msys64\mingw64\lib

# Compiler Flags
CFLAGS = -I"$(INCLUDE_DIR)"
LDFLAGS = -L"$(LIB_DIR)" -lmingw32 -lSDL3

# Target
TARGET = kmeans.exe
SRC = kmeans.c

# Build Rule
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS) $(LDFLAGS)

# Clean Rule
clean:
	del /Q $(TARGET)

