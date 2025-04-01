GXX = gcc
CFLAGS = -fsanitize=address -g3
TARGET = myshell

all: $(TARGET)

$(TARGET): myshell.c
	$(GXX) $(CFLAGS) myshell.c -o $(TARGET)

clean:
	rm -f $(TARGET)
