CC := g++
CFLAGS := -g
TARGET := test
SRCS := $(wildcard *.cpp */*.cpp )
OBJS = $(SRCS:.cpp = .o )

all:$(TARGET)
%.o:%.cpp
	$(CC) $(CFLAGS) -c $<
$(TARGET):$(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
clean:
	rm -rf $(TARGET) *.o