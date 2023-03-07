CC = gcc
CFLAGS = -Wall
LDLIBS = -lm
OBJS = fibo.o
TARGET = fibo

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDLIBS)

.PHONY: tmpclean clean
tmpclean:
	rm -f *~
clean: tmpclean
	rm -f $(OBJS) $(TARGET) 

