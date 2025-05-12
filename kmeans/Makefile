CC = g++
SRCDIR = .
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:.c=.o)
CFLAGS = -Wall -O2 -c
EXECUTABLE = kmeansC.exe

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS)

.PHONY: clean
clean:
	del /Q $(subst /,\,$(OBJECTS)) $(EXECUTABLE) 2> NUL || exit 0

example: $(EXECUTABLE)
	./$(EXECUTABLE) cluster 1024 2 2 ./N1_K2_D2.txt
