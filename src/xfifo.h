#ifndef XFIFO_H
#define XFIFO_H

#include <stdint.h>
#include "xfifo_defs.h"
#include <memory.h>

struct Fifo
{
    uint8_t memRoot[XFIFO_QUEUE_SIZE];
    size_t start;
    size_t end;
};

int xfifo_init(int fifo_num);
int xfifo_put(int fifo_num, uint8_t * buff, uint8_t dataSize);
int xfifo_get(int fifo_num, uint8_t * buff, uint8_t buffSize, uint8_t * dataSize);

#endif // XFIFO_H
