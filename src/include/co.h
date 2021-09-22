#ifndef CO_H
#define CO_H 

#ifdef __cplusplus
extern "C"{
#endif

typedef void (*co_func)(void*);

typedef enum {
    CO_NEW=0,
    CO_RUNNABLE,
    CO_RUNNING,
    CO_INTERRUPTIBLE,
    CO_UNINTERRUPTIBLE,
    CO_DEAD
} CO_STATUS;

/* Convenience macros for the sake of wake_up(): */
#define CO_NORMAL (CO_INTERRUPTIBLE | CO_UNINTERRUPTIBLE)

typedef struct co* co_t;

extern int co_init();
extern co_t co_create(co_func fn, void *args);
extern int co_yield();
extern int co_loop();
extern void co_destory(co_t co);
extern void co_await(future_t future);

/* api control current coroutine, like linux kernel current.
 * todo: optimize current use thread local data.
*/
extern co_t current;
extern void co_set_current_state(int state);

#ifdef __cplusplus
}
#endif

#endif