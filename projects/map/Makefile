CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -fPIC
LIB_SRC = map.c utils.c
LIB_OBJ = $(LIB_SRC:.c=.o)
LIB_TARGET = libmap.so
TARGET = grocery_app.out

all: $(LIB_TARGET) $(TARGET)

$(LIB_TARGET): $(LIB_OBJ)
	$(CC) -shared -o $@ $(LIB_OBJ)

$(TARGET): main.o $(LIB_TARGET)
	$(CC) $(CFLAGS) -o $(TARGET) main.o -L. -lmap -Wl,-rpath,.

run: all
	./$(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET) $(LIB_TARGET)

.PHONY: all clean run