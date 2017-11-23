#include "CharMachine.h"
#include <stdio.h>
#include <assert.h>

char cmCC;
boolean cmEOT;

static FILE * cmTape;

void cmStart(FILE *tape) {
    /* Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
       Karakter pertama yang ada pada pita posisinya adalah pada jendela.
       I.S. : sembarang
       F.S. : CC adalah karakter pertama pada pita. Jika CC != MARK maka EOP akan padam (false).
       Jika CC = MARK maka EOP akan menyala (true) */

    /* Algoritma */
    cmTape = tape;
    cmAdv();
}

void cmAdv() {
    /* Pita dimajukan satu karakter. 
       I.S. : Karakter pada jendela = 
       CC, CC != MARK
       F.S. : CC adalah karakter berikutnya dari CC yang lama, 
       CC mungkin = MARK.
       Jika  CC = MARK maka EOP akan menyala (true) */

    /* Algoritma */
    assert(cmTape != NULL);
    cmCC = getc(cmTape);
    cmEOT = (cmCC == CM_MARK);
    if (cmEOT) {
        fclose(cmTape);
        cmTape = NULL;
    }
}
