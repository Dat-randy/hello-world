CC=g++
CFLAGS=-std=c++11 -O2 -Wall
TARGET=sorting_examples
SRC=sorting_examples.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
