SOURCES = main.c $(filter-out %Driver.c,$(wildcard */*.c))
OBJS = $(patsubst %.c,obj/%.o,$(notdir $(SOURCES)))
CPPFLAGS += -I. -MMD -MP
CFLAGS = -g -Wall -Wextra -Wno-unused-parameter

bin/olympia: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

obj/main.o: main.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

obj/%.o: */%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

-include $(OBJS:%.o=%.d)
