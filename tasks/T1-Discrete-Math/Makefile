CC ?= gcc

ifeq ($(OS),Windows_NT)
	CFLAGS ?= -Wall -Wextra -std=c11 -Werror -pedantic
	PICFLAGS =
	LIBRARY = libpa.dll
	UTILS_LIBRARY = libutils.dll
	TARGET = pa.exe
	TEST_TARGET = tests/test_pa.exe
	RUNTIME_PATH =
	RM = del /Q
	RUN =
else
	CFLAGS ?= -Wall -Wextra -std=c11 -Werror -pedantic
	PICFLAGS = -fPIC
	LIBRARY = libpa.so
	UTILS_LIBRARY = libutils.so
	TARGET = pa
	TEST_TARGET = tests/test_pa
	RUNTIME_PATH = -Wl,-rpath,'$$ORIGIN'
	RM = rm -f
	RUN = ./
endif

PA_CFLAGS = $(CFLAGS) -DPA_BUILD_DLL
UTILS_CFLAGS = $(CFLAGS) -DUTILS_BUILD_DLL

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
	$(CC) $(CFLAGS) $(MAIN_OBJECT) -L. -lpa -lutils $(RUNTIME_PATH) -o $(TARGET)

src/pa.o: src/pa.c src/pa.h
	$(CC) $(PA_CFLAGS) $(PICFLAGS) -c $< -o $@

src/utils.o: src/utils.c src/utils.h
	$(CC) $(UTILS_CFLAGS) $(PICFLAGS) -c $< -o $@

src/main.o: src/main.c src/pa.h src/utils.h
	$(CC) $(CFLAGS) -Isrc -c $< -o $@

run: app
	$(RUN)$(TARGET)

test: $(TEST_TARGET)
	$(RUN)$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJECT) $(LIBRARY)
	$(CC) $(CFLAGS) $(TEST_OBJECT) -L. -lpa $(RUNTIME_PATH) -o $@

tests/test_pa.o: tests/test_pa.c src/pa.h
	$(CC) $(CFLAGS) -Isrc -c $< -o $@

clean:
	$(RM) $(MAIN_OBJECT) $(PA_OBJECT) $(UTILS_OBJECT) $(TEST_OBJECT) $(LIBRARY) $(UTILS_LIBRARY) $(TARGET) $(TEST_TARGET)
