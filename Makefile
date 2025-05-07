CC ?= gcc
CFLAGS ?= -g 
TARGET = bin/myshell
OBJS = bin/hash_map.o

all: $(TARGET)

$(TARGET): src/myshell.c $(OBJS)
	$(CC) $(CFLAGS) src/myshell.c $(OBJS) -o $(TARGET)

$(OBJS): src/hash_map.c src/hash_map.h 
	$(CC) $(CFLAGS) -c src/hash_map.c -o $(OBJS)
clean:
	rm -f $(TARGET) $(OBJS)
