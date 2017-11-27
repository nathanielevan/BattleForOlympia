#include "WordMachine.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

FILE *Ftest;
boolean notEmpty;


int main()
{
    Ftest = fopen("teststring.tmp", "w");
    fputs("Battle for Olympia", Ftest);
    fclose(Ftest);
    Ftest = fopen("teststring.tmp", "r");

    notEmpty = wmStart(Ftest);
    while (notEmpty) {
        notEmpty = wmAdv();
        
    }
}