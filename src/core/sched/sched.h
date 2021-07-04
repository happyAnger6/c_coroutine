#ifndef _CO_SCHED_H
#define _CO_SCHED_H

#ifdef __cplusplus
extern "C"{
#endif

#include <ucontext.h>

#include "list.h"
#include "co_spinlock.h"
#include "co_coroutine.h"



#define co_p(co) ((co)->p)
#define co_rq(co) (co_p(co)->rq)
#define switch_context(prev_ctx, new_ctx)  swapcontext(prev_ctx, new_ctx)

#ifdef __cplusplus
}
#endif

#endif