#include <ucontext.h>

#include "types.h"
#include "co_coroutine.h"

typedef struct co_env {
    ucontext_t uctx;
    char *stack;
    int32_t stack_size;
};

typedef struct co {
    struct list_head list;
    sched_t sched;
    struct co_env env;
    co_func fn;
    void *fn_data;
    CO_STATUS state;
} *co_t;

static TLS co_t current;