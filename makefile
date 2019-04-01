CC=gcc
LDFLAGS=-std=c11
SOURCES=main.c
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=boggle
all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
