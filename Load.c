#include "Load.h"
#include "WordMachine/WordMachine.h"
#include <stdio.h>

#define check(x) do { if (!(x)) goto fail; } while (0)
#define checkMsg(x, m) do { if (!(x)) { errormsg(m); goto fail; } } while (0)

void errormsg(const char *m) {
    fputs(m, stderr);
    fputc('\n', stderr);
}

boolean handleVersion() {
    return (wmAdv() && wmEqStr("1"));
}

void wmPrint() {
    fputs(wmCWord.buf, stdout);
}

boolean handleDate() {
    printf("Date: ");
    check(wmAdv());
    wmPrint(); putchar('-');
    check(wmAdv());
    wmPrint(); putchar('-');
    check(wmAdv());
    wmPrint(); putchar('\n');
    return true;
 fail:
    return false;
}

boolean handleTime() {
    printf("Time: ");
    check(wmAdv());
    wmPrint(); putchar(':');
    check(wmAdv());
    wmPrint(); putchar(':');
    check(wmAdv());
    wmPrint(); putchar('\n');
    return true;
 fail:
    return false;
}

boolean handlePlayers(Player **players, int *nPlayers) {
    while (wmAdv())
        if (wmEqStr("ENDPLAYERS"))
            return true;
    return false;
}

boolean handleMap(Map *map, Player *players) {
    while (wmAdv())
        if (wmEqStr("ENDMAP"))
            return true;
    return false;
}

boolean handleChecksum() {
    ChecksumResult sum = cmChecksum();
    ChecksumResult cmp;
    /*printf("Checksumming at %ld\n", ftell(f));*/
    if (!wmAdv())
        return false;
    sscanf(wmCWord.buf, "#%lx", &cmp);
    /*printf("File sum: %08lx; Computed sum: %08lx\n", cmp, sum);*/
    return (sum == cmp);
}

boolean loadFrom(const char *fname, Map *map, Player **players, int *nPlayers) {
    FILE *file = fopen(fname, "r");
    checkMsg(file != NULL, "Cannot open file");
    checkMsg(wmStart(file), "Header not found");
    checkMsg(wmEqStr("BATTLEFOROLYMPIA"), "Header not found");
    checkMsg(wmAdv() && wmEqStr("SAVEFILE"), "Header not found");
    checkMsg(wmAdv() && wmEqStr("VERSION"), "Header not found");
    checkMsg(handleVersion(), "Savefile version not compatible");
    checkMsg(wmAdv() && wmEqStr("DATE"), "Save date not found");
    checkMsg(handleDate(), "Date format error");
    checkMsg(wmAdv() && wmEqStr("TIME"), "Save time not found");
    checkMsg(handleTime(), "Time format error");
    checkMsg(wmAdv() && wmEqStr("PLAYERS"), "Player section not found");
    checkMsg(handlePlayers(players, nPlayers), "Cannot load player data");
    checkMsg(wmAdv() && wmEqStr("MAP"), "Map section not found");
    checkMsg(handleMap(map, *players), "Cannot load map data");
    checkMsg(wmAdv() && wmEqStr("CHECKSUM"), "Checksum not found");
    checkMsg(handleChecksum(), "Checksum mismatch");
    checkMsg(wmAdv() && wmEqStr("ENDFILE"), "End-of-file mark not found");
    /* Ensure that file ends here */
    checkMsg(!wmAdv(), "Garbage at end of file");
    cmFinish();
    return true;
 fail:
    cmFinish();
    return false;
}
