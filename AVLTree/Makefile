CC = gcc
CFLAGS = -Wall -Werror -g

TARGET = AVLTree

SRCS = main.c AVLTree.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)
	@echo "Compiling AVLT..."
	@echo "AVLT is ready to run."
	./AVLTree

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean
