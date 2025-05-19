CC = gcc
SDL_INC = $(HOME)/SDL3/include
SDL_LIB = $(HOME)/SDL3/build ./kmeans
CFLAGS = -I"$(SDL_INC)"
LDFLAGS = -L"$(SDL_LIB)" -lm -lSDL3
TARGET = kmeans
SRC = kmeans.c
HDR = kmeans.h

all: $(TARGET)
$(TARGET): $(SRC) $(HDR)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS) $(LDFLAGS)
clean:
	rm -f $(TARGET)

