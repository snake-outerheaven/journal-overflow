CC = cl.exe
CFLAGS = /W4 /nologo /std:c11 /D_CRT_SECURE_NO_WARNINGS
OBJS = main.obj parser.obj lexer.obj db.obj arena.obj rbtree.obj hal_win32.obj hal_posix.obj
STORAGE_OBJS = arena.obj rbtree.obj hal_win32.obj hal_posix.obj
TARGET = squidsql.exe
TEST_STORAGE = test_storage.exe

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) /Fe$@ $(OBJS)

$(TEST_STORAGE): tests\test_storage.c $(STORAGE_OBJS)
	$(CC) $(CFLAGS) /I. /Fe$@ tests\test_storage.c $(STORAGE_OBJS)

run: all
	.\$(TARGET)

# unit tests for the storage layer, then SQL scripts compared with expected output
test: all $(TEST_STORAGE)
	.\$(TEST_STORAGE)
	-@del /Q test.db 2>nul
	.\$(TARGET) test.db tests\basic.sql > tests\basic.actual
	fc /L tests\basic.out tests\basic.actual
	.\$(TARGET) test.db tests\persist.sql > tests\persist.actual
	fc /L tests\persist.out tests\persist.actual
	@del /Q test.db tests\basic.actual tests\persist.actual

.c.obj:
	$(CC) $(CFLAGS) /c $<

clean:
	-@del /Q *.obj *.pdb *.ilk $(TARGET) $(TEST_STORAGE) test.db tests\*.actual 2>nul

.PHONY: all run test clean
