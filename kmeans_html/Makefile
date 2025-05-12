# Compiler
CC = emcc

# Compiler Flags
CFLAGS = -O2 -sUSE_SDL=3 -sALLOW_MEMORY_GROWTH=1

# Output Targets
TARGETS = kmeans.html 

# Sources
KMEANS_SRC = C:\Users\ruthw\Documents\c_files\SDL_projects\k-means-project\kmeans.c


# Build Rule
all: $(TARGETS)

kmeans.html: $(KMEANS_SRC)
	$(CC) $(KMEANS_SRC) -o kmeans.html $(CFLAGS)

sample.html: $(SAMPLE_SRC)
	$(CC) $(SAMPLE_SRC) -o sample.html $(CFLAGS)

# Clean Rule
clean:
	del /Q *.html *.wasm *.js
