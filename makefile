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

bin/pcolorDriver: obj/pcolorDriver.o obj/pcolor.o
	$(CC) $(CFLAGS) -o $@ $^

bin/MapDriver: obj/MapDriver.o obj/Map.o obj/User.o obj/Unit.o obj/LinearList.o obj/Queue.o obj/Point.o obj/pcolor.o obj/CircularList.o
	$(CC) $(CFLAGS) -o $@ $^

bin/pointDriver: obj/pointDriver.o obj/Point.o
	$(CC) $(CFLAGS) -o $@ $^

bin/LoadDriver: obj/LoadDriver.o obj/Load.o obj/WordMachine.o obj/CharMachine.o obj/Checksum.o obj/Time.o obj/Map.o obj/User.o obj/Unit.o obj/LinearList.o obj/Queue.o obj/Point.o obj/pcolor.o obj/CircularList.o
	$(CC) $(CFLAGS) -o $@ $^

bin/ChecksumDriver: obj/ChecksumDriver.o obj/Checksum.o
	$(CC) $(CFLAGS) -o $@ $^

bin/WordMachineDriver: obj/WordMachineDriver.o obj/WordMachine.o obj/CharMachine.o obj/Checksum.o
	$(CC) $(CFLAGS) -o $@ $^

bin/CircularListDriver: obj/CircularListDriver.o obj/CircularList.o
	$(CC) $(CFLAGS) -o $@ $^

bin/lcDriver: obj/lcDriver.o obj/CircularList.o
	$(CC) $(CFLAGS) -o $@ $^

bin/StackDriver: obj/StackDriver.o obj/Stack.o
	$(CC) $(CFLAGS) -o $@ $^

bin/timeDriver: obj/timeDriver.o obj/Time.o
	$(CC) $(CFLAGS) -o $@ $^

-include $(OBJS:%.o=%.d)
-include $(DRIVEROBJS:%.o=%.d)
