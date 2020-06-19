#include "xfifo.h"
#include <string.h>

int xfifo_test_run(void)
{
    uint8_t test_buff[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    uint8_t out_buff[10];
    int max_size = sizeof(out_buff);
    int rec_size;
    xfifo_init(0);
    xfifo_init(1);
    xfifo_put(0, &test_buff[5], 3); // очередь 0, добавили сообщение { 5, 6, 7 }
    xfifo_put(1, &test_buff[2], 2); // очередь 1, добавили сообщение { 2, 3 }
    xfifo_put(1, &test_buff[0], 5); // очередь 1, добавили сообщение { 0, 1, 2, 3, 4 }
    xfifo_put(0, &test_buff[3], 5); // очередь 0, добавили сообщение { 3, 4, 5, 6, 7 }
    xfifo_put(0, &test_buff[8], 1); // очередь 0, добавили сообщение { 8 }
    // очередь 1, добавили сообщение { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }
    xfifo_put(1, &test_buff[0], 10);
    // получили сообщение { 5, 6, 7 }, rec_size == 3
    xfifo_get(0, out_buff, max_size, &rec_size);
    if (rec_size != 3) return -1;
    if (memcmp(out_buff, &test_buff[5], 3) != 0) return 1;
    // получили сообщение { 3, 4, 5, 6, 7 }, rec_size == 5
    xfifo_get(0, out_buff, max_size, &rec_size);
    if (rec_size != 5) return -1;
    if (memcmp(out_buff, &test_buff[3], 5) != 0) return 1;
    // получили сообщение { 8 }, rec_size == 1
    xfifo_get(0, out_buff, max_size, &rec_size);
    if (rec_size != 1) return -1;
    if (out_buff[0] != test_buff[8]) return 1;
    // получили сообщение { 2, 3 }, rec_size == 2
    xfifo_get(1, out_buff, max_size, &rec_size);
    if (rec_size != 2) return -1;
    if (memcmp(out_buff, &test_buff[2], 2) != 0) return 1;
    // получили сообщение { 0, 1, 2, 3, 4 }, rec_size == 5
    xfifo_get(1, out_buff, max_size, &rec_size);
    if (rec_size != 5) return -1;
    if (memcmp(out_buff, &test_buff[0], 5) != 0) return 1;
    // получили сообщение { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }, rec_size == 10
    xfifo_get(1, out_buff, max_size, &rec_size);
    if (rec_size != 10) return -1;
    if (memcmp(out_buff, &test_buff[0], 10) != 0) return 1;
    return 0;
}

int xfifo_test_init()
{

}
