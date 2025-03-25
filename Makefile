GXX = gcc
TARGET = myshell

all: $(TARGET)

$(TARGET): myshell.c
	$(GXX) myshell.c -o $(TARGET)

clean:
	rm -f $(TARGET)
