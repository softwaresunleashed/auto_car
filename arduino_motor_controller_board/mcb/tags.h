#ifndef __TAGS_H_
#define __TAGS_H_


#define TAG_LENGTH        3

/* Tags go here */
#define BATT_STATUS       "BLV"
#define LEFT_JOYSTICK     "LJS"
#define RIGHT_JOYSTICK    "RJS"


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
#define DELIMITER_TAG_INDEX    3    /* 4th character should be tag delimiter else packet is malformed */
#define DELIMITER_TAG          ':'
#define DELIMITER_COORDINATE   ','
#define DELIMITER_SPACE        ' '

#endif    /* __TAGS_H_ */
