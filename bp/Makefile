TARGET := b

SRCS := $(shell ls *.c)
OBJS := $(SRCS:.c=.o)

CFLAGS += -g

default:$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)
clean:
	rm -rf $(OBJS) $(TARGET)
