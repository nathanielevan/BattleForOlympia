#include "Load.h"
#include "WordMachine/WordMachine.h"
#include <stdio.h>
#include <assert.h>

#define check(x) do { if (!(x)) goto fail; } while (0)
#define checkMsg(x, m) do { if (!(x)) { errormsg(m); goto fail; } } while (0)
#define expect(s) check(wmAdv() && wmEqStr(s))
#define expectMsg(s, m) checkMsg(wmAdv() && wmEqStr(s), (m))
#define checkScan(s, v, c) check(wmAdv() &&                         \
                                 sscanf(wmCWord.buf, s, v) == 1 &&  \
                                 (c))

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

boolean handlePlayers(const Map *map, Player **players, int *nPlayers) {
    int n = 0;
    int playerID;
    Player *player;
    expect("NPLAYERS");
    checkScan("%d", nPlayers, *nPlayers > 0);
    printf("Creating %d players\n", *nPlayers);
    createPlayers(map, *nPlayers);
    while (n++ < *nPlayers) {
        expect("PLAYER");
        checkScan("%d", &playerID, playerID == n);
        /*printf("Player %d\n", playerID);*/
        player = getPlayer(playerID);
        expect("GOLD");
        checkScan("%d", &player->gold, player->gold >= 0);
        expect("INCOME");
        checkScan("%d", &player->income, player->income >= 0);
        expect("UPKEEP");
        checkScan("%d", &player->upkeep, player->upkeep >= 0);
        expect("COLOR");
        checkScan("%d", &player->color, player->color >= 0);
        expect("ENDPLAYER");
    }
    expect("ENDPLAYERS");
    printf("Loaded %d players!\n", playerID);
    return true;
 fail:
    return false;
}

boolean handleUnit(Square *square, const Point loc, Player *players,
                   const int nPlayers) {
    char type;
    TypeID typeID;
    int unitID;
    int canAttack;
    Unit *unit;
    /* Read unit type character and convert it to a TypeID */
    expect("TYPE");
    checkScan("%c", &type, true);
    typeID = lookupTypeID(type);
    check(typeID != INVALID_TYPE);
    printf("Type %c: ID %d\n", type, typeID);
    /* Create a unit of that type */
    unitID = createUnit(typeID);
    unit = getUnit(unitID);
    assert(unit != NULL);
    /* Fill its fields */
    expect("OWNER");
    checkScan("%d", &unit->ownerID,
              unit->ownerID > 0 && unit->ownerID <= nPlayers);
    expect("HEALTH");
    checkScan("%d", &unit->health, unit->health >= 0);
    expect("MOV");
    checkScan("%d", &unit->movPoints, unit->movPoints >= 0);
    expect("CAN_ATTACK");
    checkScan("%d", &canAttack, canAttack == 0 || canAttack == 1);
    unit->canAttack = canAttack;
    unit->location = loc;
    expect("ENDUNIT");
    /* Add it to its owner's list of units */
    lcInsVLast(&getPlayer(unit->ownerID)->units, unitID);
    /* Add it to the grid */
    square->unitID = unitID;
    return true;
 fail:
    return false;
}

boolean handleMap(Map *map, Player *players, const int nPlayers) {
    int w, h; /* map size */
    int n = 0, m = 0; /* number of squares, units loaded */
    int i, j; /* square position */
    Square square;
    boolean set[4];
    expect("WIDTH");
    checkScan("%d", &w, w > 0);
    expect("HEIGHT");
    checkScan("%d", &h, h > 0);
    printf("Creating map (w=%d h=%d)\n", w, h);
    createMap(h, w, map);
    initUnitPool(map);
    expect("SQUARES");
    while (wmAdv() && !wmEqStr("ENDSQUARES")) {
        check(wmEqStr("SQUARE"));
        checkScan("%d", &i, i >= 0 && i < h);
        checkScan("%d", &j, j >= 0 && j < w);
        square = grid(*map, i, j);
        set[0] = set[1] = set[2] = set[3] = false;
        check(wmAdv());
        if (wmEqStr("TYPE")) {
            char c;
            check(!set[0]);
            set[0] = true;
            checkScan("%c", &c, true);
            square.type = c;
            check(wmAdv());
        }
        if (wmEqStr("OWNER")) {
            check(!set[1]);
            set[1] = true;
            checkScan("%d", &square.ownerID,
                      square.ownerID > 0 && square.ownerID <= nPlayers);
            addSquare(square.ownerID, square.squareID);
            /* income from this square has been set in handlePlayer() */
            check(wmAdv());
        }
        if (wmEqStr("TRIBUTE")) {
            check(!set[2]);
            check(square.type == VILLAGE);
            checkScan("%d", &square.tribute,
                      square.tribute >= MIN_TRIBUTE &&
                      square.tribute <= MAX_TRIBUTE);
            set[2] = true;
            check(wmAdv());
        }
        /* tribute is set iff square.type == VILLAGE */
        check(square.type != VILLAGE || set[2]);
        check(!set[2] || square.type == VILLAGE);
        if (wmEqStr("UNIT")) {
            check(!set[3]);
            check(handleUnit(&square, MakePoint(j, i), players, nPlayers));
            check(wmAdv());
            set[3] = true;
            ++m;
        }
        grid(*map, i, j) = square;
        check(wmEqStr("ENDSQUARE"));
        ++n;
    }
    expect("ENDMAP");
    printf("Loaded %d squares and %d units!\n", n, m);
    return true;
 fail:
    return false;
}

boolean handleChecksum() {
    ChecksumResult sum = cmChecksum();
    ChecksumResult cmp;
    /*printf("Checksumming at %ld\n", ftell(f));*/
    if (!(wmAdv() && sscanf(wmCWord.buf, "#%lx", &cmp) == 1))
        return false;
    /*printf("File sum: %08lx; Computed sum: %08lx\n", cmp, sum);*/
    return (sum == cmp);
}

boolean loadFrom(const char *fname, Map *map, Player **players, int *nPlayers) {
    FILE *file = fopen(fname, "r");
    checkMsg(file != NULL, "Cannot open file");
    checkMsg(wmStart(file), "Header not found");
    checkMsg(wmEqStr("BATTLEFOROLYMPIA"), "Header not found");
    expectMsg("SAVEFILE", "Header not found");
    expectMsg("VERSION", "Header not found");
    checkMsg(handleVersion(), "Savefile version not compatible");
    expectMsg("DATE", "Save date not found");
    checkMsg(handleDate(), "Date format error");
    expectMsg("TIME", "Save time not found");
    checkMsg(handleTime(), "Time format error");
    expectMsg("PLAYERS", "Player section not found");
    checkMsg(handlePlayers(map, players, nPlayers), "Cannot load player data");
    expectMsg("MAP", "Map section not found");
    checkMsg(handleMap(map, *players, *nPlayers), "Cannot load map data");
    expectMsg("CHECKSUM", "Checksum not found");
    checkMsg(handleChecksum(), "Checksum mismatch");
    expectMsg("ENDFILE", "End-of-file mark not found");
    /* Ensure that file ends here */
    checkMsg(!wmAdv(), "Garbage at end of file");
    cmFinish();
    return true;
 fail:
    cmFinish();
    return false;
}
