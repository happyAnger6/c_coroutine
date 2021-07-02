#ifndef _CO_EVENT_LOOP_H
#define _CO_EVENT_LOOP_H 

#ifdef __cplusplus
extern "C"{
#endif

typedef struct event_engine* event_engine_t;
typedef void* (*event_callback)(void *args);

extern event_engine_t event_engine_create();

extern int event_engine_run(event_engine_t ev_engine, long expired_ms);

extern void event_engine_destory(event_engine_t ev_engine);

#ifdef __cplusplus
}
#endif

#endif