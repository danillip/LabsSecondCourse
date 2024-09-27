CC = gcc
CFLAGS = -Wall

SRCS = main.c math_operations.c
OBJS = $(SRCS:.c=.o)
TARGET = MyProgramm

.PHONY: all clean install

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lm

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)

install: $(TARGET)
	mkdir -p ~/bin
	cp $(TARGET) ~/bin

