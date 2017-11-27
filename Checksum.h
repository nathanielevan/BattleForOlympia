#ifndef BATTLEFOROLYMPIA_CHECKSUM_H
#define BATTLEFOROLYMPIA_CHECKSUM_H

typedef struct {
    unsigned short a, b;
} ChecksumState;

typedef unsigned long ChecksumResult;

void checksumInit(ChecksumState *sum);
void checksumUpdate(ChecksumState *sum, unsigned char c);
ChecksumResult checksumFinal(ChecksumState *sum);

#endif /* BATTLEFOROLYMPIA_CHECKSUM_H */