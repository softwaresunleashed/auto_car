#ifndef __TAGS_H_
#define __TAGS_H_

/* Lenght of TAGS spitted out from ESP32 */
#define TAG_LENGTH        3

/* --- Tags go here --- */

/* Battery Level */
#define BATT_STATUS       "BLV"

/* JoyStick */
#define LEFT_JOYSTICK     "LJS"
#define RIGHT_JOYSTICK    "RJS"

/* Keys */
#define CROSS_BTN         "CRO"
#define SQUARE_BTN        "SQU"
#define TRIANGLE_BTN      "TRI"
#define CIRCLE_BTN        "CIR"

/* D-pad button */
#define UP_BTN            "UPB"
#define DOWN_BTN          "DNB"
#define LEFT_BTN          "LFB"
#define RIGHT_BTN         "RTB"

/* Digital shoulder button */
#define SHOULDER_BTN_L1   "L1B"
#define SHOULDER_BTN_R1   "R1B"

/* Digital trigger button */
#define SHOULDER_BTN_L2   "L2B"
#define SHOULDER_BTN_R2   "R2B"

/* Digital stick button */
#define SHOULDER_BTN_L3   "L3B"
#define SHOULDER_BTN_R3   "R3B"

/* Digital select/start/ps button */
#define SELECT_BTN        "SEL"
#define START_BTN         "STR"
#define PS_BTN            "PS"



/* --- Tags - END --- */

/* Battery Status Defines */
typedef enum {
  BATT_UNDEFINED,
  BATT_CHARGING,
  BATT_FULL,
  BATT_HIGH,
  BATT_LOW,
  BATT_DYING,
  BATT_SHUTDOWN,
  BATT_MAX_ENTRIES
}eBattStatus;

/* Delimiters used in Serial Parser */
#define DELIMITER_TAG_INDEX    TAG_LENGTH    /* The next character to TAG_LENGTH should be tag delimiter else packet is malformed */
#define DELIMITER_TAG          ':'
#define DELIMITER_COORDINATE   ','
#define DELIMITER_ANALOG_VAL   ','
#define DELIMITER_SPACE        ' '

#endif    /* __TAGS_H_ */
