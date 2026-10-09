CC = cl.exe
CFLAGS = /W4 /nologo /D_CRT_SECURE_NO_WARNINGS
OBJS = main.obj parser.obj lexer.obj db.obj
TARGET = squidsql.exe

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) /Fe$@ $(OBJS)

run: all
	.\$(TARGET)

test: all
	.\$(TARGET) tests\basic.sql

.c.obj:
	$(CC) $(CFLAGS) /c $<

clean:
	del /Q *.obj $(TARGET)

.PHONY: all run test clean
