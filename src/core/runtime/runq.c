#include "list.h"

typedef struct list_head g_rq;

struct rq {
    co_spinlock_t lock;
    uint32_t running_num;
    struct list_head queue;
    co_t curr;
    co_t main;
};