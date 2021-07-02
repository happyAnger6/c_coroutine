#ifndef _CO_RUNTIME_H
#define _CO_RUNTIME_H

#include "co_coroutine.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef struct runtime *runtime_t;

extern runtime_t runtime_create();
extern void runtime_loop();
extern void runtime_destory();

int sched_submit_co(co_t co);
void schedule();


#ifdef __cplusplus
}
#endif

#endif