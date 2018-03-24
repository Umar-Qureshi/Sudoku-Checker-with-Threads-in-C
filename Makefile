CC = clang
CFLAGS = -std=c99 -Wall -Wextra -g -lpthread

SOURCES = puzzle.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = puzzle

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(SOURCES)
run:
	./$(EXECUTABLE)

.PHONY: clean

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)
