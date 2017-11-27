#include "Checksum/Checksum.h"

/* Adler-32 checksum (Mark Adler, circa 1995) */
/* Specified in RFC 1950 (Deutsch and Gailly, 1996) */

void checksumInit(ChecksumState *sum) {
    sum->a = 1;
    sum->b = 0;
}

void checksumUpdate(ChecksumState *sum, unsigned char c) {
    sum->a = (sum->a + c) % 65521;
    sum->b = (sum->b + sum->a) % 65521;
}

ChecksumResult checksumFinal(ChecksumState *sum) {
    return (((unsigned long) sum->b << 16) | sum->a);
}
