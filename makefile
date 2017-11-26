SOURCES = GameController.c main.c Map.c pcolor.c Undo.c Unit.c User.c CircularList/CircularList.c LinearList/LinearList.c Point/Point.c StackList/Stack.c Save.c Load.c WordMachine/CharMachine.c WordMachine/WordMachine.c Checksum.c Queue/Queue.c Time/Time.c

game: $(SOURCES) *.h
	gcc -I. -g -Wall -Wextra -Wno-unused-parameter -o game $(SOURCES)
