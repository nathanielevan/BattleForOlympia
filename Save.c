#include "Save.h"
#include "Checksum.h"
#include <stdio.h>

#define check(x) do { if (!(x)) goto fail; } while (0)
#define checkPos(x) check((x) > 0)

boolean saveAs(const char *fname, const Map *map, const Player *players,
               const int nPlayers) {
    FILE *file;
    ChecksumState sum;
    int c;
    /* Open file */
    file = fopen(fname, "w+");
    if (file == NULL)
        return false;
    checkPos(fputs("BATTLEFOROLYMPIA SAVEFILE\n", file));
    checkPos(fputs("VERSION 1\n", file));
    checkPos(fputs("DATE YYYY MM DD\n", file));
    checkPos(fputs("TIME HH MM SS\n", file));
    check(savePlayers(file, players, nPlayers));
    check(saveSquares(file, map));
    checkPos(fputs("CHECKSUM #", file));
    /*printf("Checksumming at %ld\n", ftell(file));*/
    rewind(file);
    checksumInit(&sum);
    while ((c = getc(file)) != EOF)
        checksumUpdate(&sum, c);
    fseek(file, 0, SEEK_END);
    checkPos(fprintf(file, "%08lx\n", checksumFinal(&sum)));
    checkPos(fputs("ENDFILE\n", file));
    fclose(file);
    return true;
 fail:
    fclose(file);
    return false;
}

boolean savePlayers(FILE *file, const Player *players, const int nPlayers) {
    int i;
    const Player *player;
    checkPos(fputs("PLAYERS\n", file));
    checkPos(fprintf(file, "NPLAYERS %d\n", nPlayers));
    for (i = 1; i <= nPlayers; i++) {
        player = getPlayer(i);
        checkPos(fprintf(file, "PLAYER %d\n", i));
        checkPos(fprintf(file, "GOLD %d\n", player->gold));
        checkPos(fprintf(file, "INCOME %d\n", player->income));
        checkPos(fprintf(file, "UPKEEP %d\n", player->upkeep));
        checkPos(fprintf(file, "COLOR %d\n", player->color));
        checkPos(fputs("ENDPLAYER\n", file));
    }
    checkPos(fputs("ENDPLAYERS\n", file));
    return true;
 fail:
    return false;
}

boolean saveSquares(FILE *file, const Map *map) {
    int i, j;
    Square sq;
    checkPos(fputs("MAP\n", file));
    checkPos(fprintf(file, "WIDTH %d\nHEIGHT %d\n",
                     width(*map), height(*map)));
    checkPos(fputs("SQUARES\n", file));
    for (i = 0; i < height(*map); i++) {
        for (j = 0; j < width(*map); j++) {
            sq = grid(*map, i, j);
            if (sq.type != NORMAL || sq.unitID != 0) {
                checkPos(fprintf(file, "SQUARE %d %d\n", i, j));
                if (sq.type != NORMAL)
                    checkPos(fprintf(file, "TYPE %c\n", sq.type));
                if (sq.ownerID != 0)
                    checkPos(fprintf(file, "OWNER %d\n", sq.ownerID));
                if (sq.type == VILLAGE)
                    checkPos(fprintf(file, "TRIBUTE %d\n", sq.tribute));
                if (sq.unitID != 0)
                    checkPos(saveUnit(file, sq.unitID));
                checkPos(fputs("ENDSQUARE\n", file));
            }
        }
    }
    checkPos(fputs("ENDSQUARES\n", file));
    checkPos(fputs("ENDMAP\n", file));
    return true;
 fail:
    return false;
}

boolean saveUnit(FILE *file, const int unitID) {
    Unit *unit = getUnit(unitID);
    checkPos(fputs("UNIT\n", file));
    checkPos(fprintf(file, "TYPE %c\n", unitTypes[unit->type].mapSymbol));
    checkPos(fprintf(file, "OWNER %d\n", unit->ownerID));
    checkPos(fprintf(file, "HEALTH %d\n", unit->health));
    checkPos(fprintf(file, "MOV %d\n", unit->movPoints));
    checkPos(fprintf(file, "CAN_ATTACK %d\n", !!(unit->canAttack)));
    checkPos(fputs("ENDUNIT\n", file));
    return true;
 fail:
    return false;
}
