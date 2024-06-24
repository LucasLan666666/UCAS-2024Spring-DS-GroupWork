CC = gcc
# CFLAGS = -Wall -Werror -g
CFLAGS = -g

TARGET = KTP

SRCS = main.c board.c test.c title.c function.c algorithm.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)
	@echo "Compiling KTP..."
	@echo "KTP is ready to run."
	./KTP

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean
