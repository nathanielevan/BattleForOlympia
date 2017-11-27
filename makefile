SOURCES = main.c $(filter-out %Driver.c,$(wildcard */*.c))
OBJS = $(patsubst %.c,obj/%.o,$(notdir $(SOURCES)))
DRIVERSRCS = $(wildcard */*Driver.c)
DRIVEROBJS = $(patsubst %.c,obj/%.o,$(notdir $(DRIVERSRCS)))
DRIVERS = $(DRIVEROBJS:obj/%.o=bin/%)
CPPFLAGS += -I. -MMD -MP
CFLAGS = -g -Wall -Wextra -Wno-unused-parameter

.PHONY: all clean

all: bin/olympia $(DRIVERS)

bin/olympia: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

obj/main.o: main.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

obj/%.o: */%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) -f obj/*
	$(RM) -f bin/*

bin/llDriver: obj/llDriver.o obj/LinearList.o
	$(CC) $(CFLAGS) -o $@ $^

-include $(OBJS:%.o=%.d)
-include $(DRIVEROBJS:%.o=%.d)
