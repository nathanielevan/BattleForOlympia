SOURCES = main.c $(filter-out %Driver.c,$(wildcard */*.c))
CPPFLAGS += -I.
CFLAGS = -g -Wall -Wextra -Wno-unused-parameter

bin/olympia: $(SOURCES)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o bin/olympia $(SOURCES)
