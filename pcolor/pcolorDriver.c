#include <stdio.h>
#include <string.h>
#include "pcolor/pcolor.h"

const char InputDriver[] = "KWSACTVX";
int foo;

int main()
{
    for (foo = 0; foo < strlen(InputDriver); foo++) {
        printf("%c: ", InputDriver[foo]);
        print_white(InputDriver[foo]);
        print_red(InputDriver[foo]);
        print_green(InputDriver[foo]);
        print_yellow(InputDriver[foo]);
        print_blue(InputDriver[foo]);
        print_magenta(InputDriver[foo]);
        print_cyan(InputDriver[foo]);
        printf("\n");
    }
    return 0;
}