#ifndef _CO_RUNTIME_H
#define _CO_RUNTIME_H

#include <pthread.h>

#include "co_coroutine.h"
#include "sched.h"

#ifdef __cplusplus
extern "C"{
#endif

#define P_RUNNING 0x1
#define P_EXIT 0x2

typedef p_id_t int32_t;

#define p_rq(p) ((p)->rq)

#define MAX_CO_STACK_SIZE 1024 * 1024

struct sched {
    uint32_t rq_size;
    struct rq *g_rq;
};


typedef struct runtime *runtime_t;

extern runtime_t runtime_create();
extern void runtime_loop();
extern void runtime_destory();

/* get current p*/
extern struct p* processor_p();

int sched_submit_co(co_t co);
void schedule();


#ifdef __cplusplus
}
#endif

#endif