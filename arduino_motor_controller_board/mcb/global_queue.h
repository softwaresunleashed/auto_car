#ifndef __GLOBAL_QUEUE_H_
#define __GLOBAL_QUEUE_H_


#include <queue.h>    /* FreeRTOS queue */

#define KEY_EVENT_QUEUE_LEN   10
QueueHandle_t xKeyEventQueue;

#endif    /* __GLOBAL_QUEUE_H_ */
