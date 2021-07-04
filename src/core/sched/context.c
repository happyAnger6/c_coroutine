#include <ucontext.h>

#include "runtime.h"
#include "co_coroutine.h"

typedef void (*uctx_fn)();

int main_co_context(struct p *p, struct co *co, co_func func)
{
    if(getcontext(&co->uctx) == -1)
        error_exit("make_co_context getcontext failed!");

    co->uctx.uc_stack.ss_sp = p->stack;
    co->uctx.uc_stack.ss_size = sizeof(p->stack);
    co->uctx.uc_link = &p->uctx_main; //if end, return to p's thread_entry.
    makecontext(&co->uctx, (uctx_fn)func, 0);
    return 0;
}