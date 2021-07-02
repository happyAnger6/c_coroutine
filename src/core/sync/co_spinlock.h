#ifndef _CO_SPINLOCK_H
#define _CO_SPINLOCK_H

#include <stdatomic.h>

#ifdef __cplusplus
extern "C"{
#endif

typedef volatile atomic_flag co_spinlock_t;

static inline int co_spin_init(co_spinlock_t *lock)
{
    atomic_flag_clear(lock);
    return 0;
}

static inline int co_spin_lock(co_spinlock_t *lock)
{
    while (atomic_flag_test_and_set(lock));
    return 0;
}

static inline int co_spin_unlock(co_spinlock_t *lock)
{
    atomic_flag_clear(lock);
    return 0;
}

static inline int co_spin_destory(co_spinlock_t *lock)
{
    return 0;
}

#ifdef __cplusplus
}
#endif

#endif
