CC = gcc
CFLAGS = -Wall
LDLIBS = -lm
OBJS = paintapp.o func.o canvas.o
TARGET = paint

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDLIBS)

.PHONY: tmpclean clean
tmpclean:
	rm -f *~
clean: tmpclean
	rm -f $(OBJS) $(TARGET) 
