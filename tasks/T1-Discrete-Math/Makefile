CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Werror -pedantic
PICFLAGS = -fPIC
LIBRARY = libpa.so
UTILS_LIBRARY = libutils.so
TARGET = pa
TEST_TARGET = tests/test_pa

PA_OBJECT = src/pa.o
UTILS_OBJECT = src/utils.o
MAIN_OBJECT = src/main.o
TEST_OBJECT = tests/test_pa.o

.PHONY: all app run test clean

all: app

$(LIBRARY): $(PA_OBJECT)
	$(CC) -shared $^ -o $@

$(UTILS_LIBRARY): $(UTILS_OBJECT)
	$(CC) -shared $^ -o $@

app: $(MAIN_OBJECT) $(LIBRARY) $(UTILS_LIBRARY)
	$(CC) $(CFLAGS) $(MAIN_OBJECT) -L. -lpa -lutils -Wl,-rpath,'$$ORIGIN' -o $(TARGET)

src/pa.o: src/pa.c src/pa.h
	$(CC) $(CFLAGS) $(PICFLAGS) -c $< -o $@

src/utils.o: src/utils.c src/utils.h
	$(CC) $(CFLAGS) $(PICFLAGS) -c $< -o $@

src/main.o: src/main.c src/pa.h src/utils.h
	$(CC) $(CFLAGS) -Isrc -c $< -o $@

run: app
	./$(TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJECT) $(LIBRARY)
	$(CC) $(CFLAGS) $(TEST_OBJECT) -L. -lpa -Wl,-rpath,'$$ORIGIN/..' -o $@

tests/test_pa.o: tests/test_pa.c src/pa.h
	$(CC) $(CFLAGS) -Isrc -c $< -o $@

clean:
	rm -f $(MAIN_OBJECT) $(PA_OBJECT) $(UTILS_OBJECT) $(TEST_OBJECT)
	rm -f $(LIBRARY) $(UTILS_LIBRARY) $(TARGET) $(TEST_TARGET)
	rm -f src/libpa.a src/libpa.so src/pa
