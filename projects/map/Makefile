CC = cl.exe
CFLAGS = /W4 /std:c11 /nologo
LIB_SRC = map.c utils.c
LIB_OBJ = map.obj utils.obj
LIB_TARGET = map.lib
TARGET = grocery_app.exe

all: $(LIB_TARGET) $(TARGET)

$(LIB_TARGET): $(LIB_OBJ)
	lib /out:$@ $**

$(TARGET): main.obj $(LIB_TARGET)
	$(CC) $(CFLAGS) /Fe$@ main.obj /link $(LIB_TARGET)

run: all
	.\$(TARGET)

.c.obj:
	$(CC) $(CFLAGS) /c $<

clean:
	del /Q *.obj $(TARGET) $(LIB_TARGET)

.PHONY: all clean run
