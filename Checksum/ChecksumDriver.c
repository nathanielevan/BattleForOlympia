#include "Checksum/Checksum.h"
#include <stdio.h>

ChecksumResult CksResult;
ChecksumState CksState;
int CharString;

int main() {
    checksumInit(&CksState);
    printf("Input a string here:\n");
    CharString = getchar();
    while ((CharString != '\n') && (CharString != EOF)) {
        checksumUpdate(&CksState,CharString);
        CharString = getchar();
    }
    CksResult = checksumFinal(&CksState);
    printf("Checksum: 0x%04lx\n", CksResult);
    return 0;
}
