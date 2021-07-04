#include <stdint.h>
#include <ucontext.h>

#include "types.h"
#include "co_coroutine.h"
#include "runtime.h"
#include "sched.h"

typedef struct co_env {
    ucontext_t uctx;
    char *stack;
    int32_t stack_size;
};

typedef struct co {
    uint32_t id;
    struct p *p; /* co belongs to one p*/
    struct list_head list; /* rq list*/
    struct co_env env;
    co_func fn;
    void *fn_data;
    CO_STATUS state;
} *co_t;

static TLS co_t current;