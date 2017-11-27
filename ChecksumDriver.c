#include "Checksum.h"

ChecksumResult CksResult;
ChecksumState CksState;
int CharString;

checksumInit(&CksState);
printf("Input a string here:\n");
CharString = getchar();
while ((CharString != '\n') && (CharString != EOF)) {
    checksumUpdate(&CksState,CharString);
    CharString = getchar();
}
CksResult = checksumFinal(&CksState);