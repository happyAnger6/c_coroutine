#include <sys/sysinfo.h>
#include <pthread.h>

#include "list.h"
#include "co_spinlock.h"

#include "event_loop.h"
#include "runtime.h"

typedef struct runtime {
    struct p *all_p;
    struct threadpool *th_pool;
} *runtime_t;

static pthread_key_t p_key;

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