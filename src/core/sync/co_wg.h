#ifndef _CO_WG_H
#define _CO_WG_H

#ifdef __cplusplus
extern "C"{
#endif

/* waitGroup impl. */

typedef struct co_wg* co_wg_t;

extern co_wg_t co_wg_create();
extern void co_wg_add(co_wg_t wg, int val);
extern void co_wg_done(co_wg_t wg);
extern void co_wg_wait(co_wg_t wg);

#ifdef __cplusplus
}
#endif

#endif