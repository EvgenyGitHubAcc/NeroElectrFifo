#include "xfifo.h"

struct Fifo fifoArr[XFIFO_QUEUES_COUNT];

int xfifo_init(int fifo_num)
{
    fifoArr[fifo_num].start = 0;
    fifoArr[fifo_num].end = 0;
    return 0;
}

int xfifo_put(int fifo_num, uint8_t *buff, uint8_t dataSize)
{

    fifoArr[fifo_num].memRoot[fifoArr[fifo_num].end++] = dataSize;
    fifoArr[fifo_num].end %= XFIFO_QUEUE_SIZE;

    for(uint8_t i = 0; i < dataSize + 1; ++i)
    {
        if(fifoArr[fifo_num].start == fifoArr[fifo_num].end)
        {
            printf("Query memory is overloaded");
            return -1;
        }
        fifoArr[fifo_num].memRoot[fifoArr[fifo_num].end++] = buff[i];
        fifoArr[fifo_num].end %= XFIFO_QUEUE_SIZE;
    }

    return 0;
}

int xfifo_get(int fifo_num, uint8_t *buff, uint8_t buffSize, uint8_t *dataSize)
{
    if(fifoArr[fifo_num].start == fifoArr[fifo_num].end)
    {
        printf("Query is empty");
        return -1;
    }
    *dataSize = fifoArr[fifo_num].memRoot[fifoArr[fifo_num].start++];
    fifoArr[fifo_num].start %= XFIFO_QUEUE_SIZE;

    for(uint8_t i = 0; i < *dataSize + 1; ++i)
    {
        if(fifoArr[fifo_num].start == fifoArr[fifo_num].end)
        {
            printf("Query pop front error");
            return -1;
        }
        buff[i] = fifoArr[fifo_num].memRoot[fifoArr[fifo_num].start++];
        fifoArr[fifo_num].start %= XFIFO_QUEUE_SIZE;
    }
    return 0 ;
}
