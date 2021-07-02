#include "co_waitq.h"

static int wakeup_co(struct co *c, int wake_flags)
{
    sched_co_resume((void *)co);
    return 0;
}

void sched_submit_co(struct co *c)