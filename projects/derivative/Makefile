CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=gnu89 -O3
TARGET = derivative_test

all: $(TARGET)

$(TARGET): main.c derivative.h
	$(CC) $(CFLAGS) main.c -o $(TARGET)

clean:
	rm -f $(TARGET)

run: all
	./$(TARGET)

