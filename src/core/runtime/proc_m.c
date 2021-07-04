#include <stdint.h>
#include <pthread.h>

#include "co_coroutine.h"

struct m {
    struct co *c;
    pthread_t os_thread;
    char *stack;
    uint32_t stack_size;
    struct p *p;
};

/* M entry point*/
void m_start(void *arg)
{

}

void m_create(struct m *m)
{
    /* Disable signals before pthread_create, so new thread
     *  starts with no signals.
     */
}