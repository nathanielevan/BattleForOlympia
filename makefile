game: GameController.c main.c Map.c pcolor.c Undo.c Unit.c User.c CircularList/CircularList.c LinearList/LinearList.c Point/Point.c StackList/Stack.c
	gcc -I. -g -Wall -Wextra -Wno-unused-parameter -o game GameController.c main.c Map.c pcolor.c Undo.c Unit.c User.c CircularList/CircularList.c LinearList/LinearList.c Point/Point.c StackList/Stack.c
