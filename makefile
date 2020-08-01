cc = gcc 
srcs = $(shell find ./ -name "*.c")
proms = $(srcs:%.c=%)
objs = $(srcs:%.c=%.o)
cflags = -g -Wall
libs += -lpthread

all: $(proms)

.secondary: $(objs)

.phony: all clean

%: %.o
	$(cc) $(cflags) $< $(libs) -o $@

%.o: %.c
	$(cc) $(cflags) -c $< -o $@

clean:
	rm -rf $(objs) $(proms)
