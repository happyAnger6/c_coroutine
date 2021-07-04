#ifndef _CO_TYPES_H
#define _CO_TYPES_H 

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#ifdef __cplusplus
extern "C"{
#endif

#define TLS __thread

static inline void error_exit(char *msg)
{
    perror(msg);
    exit(1);
}

#ifdef __cplusplus
}
#endif

#endif