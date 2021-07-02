#include <sys/sysinfo.h>
#include <pthread.h>

#include "list.h"
#include "co_spinlock.h"

#include "event_loop.h"
#include "runtime.h"

struct co_queue {
    co_spinlock_t lock;
    uint32_t len;
    struct list_head queue;
};

struct co_p {
    int32_t id;
    pthread_t thread;
    struct co_queue rq;
    event_engine_t ev_engine;
};

typedef struct runtime {
    struct co_p *all_p;
    struct threadpool *th_pool;
} *runtime_t;

static int cpu_nums()
{
    static int cpu_nums = -1;
    if (cpu_nums == -1) 
        cpu_nums = get_nprocs();
    
    return cpu_nums;
}

void runtime_t runtime_create()
{

}