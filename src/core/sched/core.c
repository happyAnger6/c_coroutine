#include "co_coroutine.h"
#include "co_waitq.h"
#include "runtime.h"

#define mlock(obj) pthread_mutex_lock(&(obj)->lock)
#define mulock(obj) pthread_mutex_unlock(&(obj)->lock)
#define mwait(obj) pthread_cond_wait(&(obj)->lock, &(obj)->cond)

static inline co_t dequeue_co(struct rq *q)
{
    co_t co = NULL;
    if(list_empty(&q->queue)) {
        return NULL;
    }

    co = list_entry(q->queue.next, co_t, list);
    list_del(&co->list);
    return co;
}

static inline void enqueue_co(struct rq *rq, struct co *co)
{
    list_add_tail(&co->list, &rq->queue);
}

static void activate_co(struct rq *rq, struct co *co)
{
    enqueue_co(rq, co);
}

/* when create a new coroutine, wake up it will do follows:
 * 
 * 1. put it new to a rq of p, now we only suppport co run 
 *      on p which p create it.
 * 2. wake it up
 */
void wake_up_new_co(struct co *new_co)
{
    new_co->state = CO_RUNNING;
    struct rq *rq = co_rq(co);

    activate_co(rq, co);
}

static inline void restore_co_stack(struct p *p, struct co *co)
{
    memcpy(p->stack + MAX_CO_STACK_SIZE - co->stack_size, co->stack, co->stack_size);
}

static void save_co_stack(struct co *co, char *top)
{
    char stack_base = 0;
    int32_t stack_size = top - &stack_base;
    assert(stack_size <= MAX_CO_STACK_SIZE);

    if(co->stack_size < stack_size) {
        free((void *)co->stack); // free null is ok.
        co->stack = (char *)malloc(stack_size);
    }

    co->stack_size = stack_size;
    memcpy(co->stack, &stack_base, stack_size);
}

void schedule()
{
    struct p *p = processor_p();
    struct rq *rq = p_rq(p);

    struct co *prev_co = rq->curr;
    struct co *next_co = rq_next(rq);

    if (next_co == NULL) { /* if no runnable co, go to main.*/
        next_co = rq->main;
    } 
    
    if (next_co->stack != NULL) { /* co is not run first time, so restore stack*/
        restore_co_stack(p, next_co);
    }
    
    rq->curr = next_co;
    next_co->state = CO_RUNNING;
    save_co_stack(prev_co, p->stack + p->stack_size);
    
    switch_context(prev_co, next_co);
}

static void* thread_entry(void *args)
{

}

/* this is the main_coroutine code*/
static void main_loop()
{
    struct p *p = processor_p();

    while (p->state == P_RUNNING) {
        mlock(p);
        struct rq *rq = p_rq(p);
        while(rq->running_num == 0) {
            if (p->state != P_RUNNING) {
                munlock(&p->lock);
                return;
            }
            mwait(p);
        }
        munlock(p);

        rq->curr = NULL;
        schedule();
    }
}

void wake_up_new_coroutine(struct co *c)
{

}

static int wakeup_co(struct co *c, int wake_flags)
{
    sched_co_resume((void *)co);
    return 0;
}

void sched_submit_co(struct co *c)