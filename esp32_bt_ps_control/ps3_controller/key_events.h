#ifndef __KEY_EVENTS_H_
#define __KEY_EVENTS_H_


#define MIN_ANALOG_VALUE      0
#define MAX_ANALOG_VALUE      255

typedef enum {
    KT_NONE,

    /* Battery */
    KT_BATT_STATUS,

    /* JoyStick */
    KT_LEFT_JOYSTICK,
    KT_RIGHT_JOYSTICK,

    /* Keys */
    KT_CROSS_BTN,
    KT_SQUARE_BTN,
    KT_TRIANGLE_BTN,
    KT_CIRCLE_BTN,

    /* D-pad button */
    KT_UP_BTN,
    KT_RIGHT_BTN,
    KT_DOWN_BTN,
    KT_LEFT_BTN,

    /* Digital shoulder button */
    KT_SHOULDER_BTN_L1,
    KT_SHOULDER_BTN_R1,

    /* Digital trigger button */
    KT_SHOULDER_BTN_L2,
    KT_SHOULDER_BTN_R2,

    /* Digital stick button events */
    KT_SHOULDER_BTN_L3,
    KT_SHOULDER_BTN_R3,

    /* Digital select/start/ps button */
    KT_SELECT_BTN,
    KT_START_BTN,
    KT_PS_BTN,

    /* Used as limiting / sanity check */
    KT_MAX
}eKeyType;

typedef enum {
  KS_RELEASED,
  KS_PRESSED
}eKeyState;


#endif    /* __KEY_EVENTS_H_ */
