ifeq ($(OS),Windows_NT)
CC = gcc
CFLAGS = -Wall -Wextra -g -I.
LDFLAGS = -L. -lpdcurses -lm
LIBS = -luser32 -lgdi32 -lpdcurses
OBJECTS = main.o

TARGET = vite

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS) $(LIBS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o $(TARGET)

.PHONY: all clean



else
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LIBS = -lm -lncurses

TARGET = vite

all: $(TARGET)

$(TARGET): main.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o $(LIBS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f $(TARGET) *.o
endif