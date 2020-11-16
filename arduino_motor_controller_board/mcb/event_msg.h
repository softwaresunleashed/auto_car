#ifndef __EVENT_MSG_H_
#define __EVENT_MSG_H_

#include "key_events.h"

typedef struct {
    char        *key;
    eKeyType    val;
} TagToKeyType_t;

typedef struct{
    eKeyType event_type;

    union {
        struct {
            int batt_lvl;
        } battery;

        struct {
            int x;
            int y;
        } coordinate;

        struct {
            int is_pressed;
            int analog_val;
        } key;
    } more;

} EventMsg_t;



#endif    /* __EVENT_MSG_H_ */
