#include <stdint.h>
#include <pthread.h>

struct p {
    pthread_mutex_t lock;
    pthread_cond_t cond;
    int32_t id;
    uint32_t thread_num;
    pthread_t *threads;
    struct rq *rq;
    event_engine_t ev_engine;
    int state;
};
