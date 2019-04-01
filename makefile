CC=gcc
CFLAGS=-c
LDFLAGS=-std=c11
SOURCES=main.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=boggle
all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
