#ifndef BUFFER_H_
#define BUFFER_H_


#include <stdint.h>

struct buffer{
    volatile uint64_t position;
    volatile int array[1000][4096];
};

#endif
