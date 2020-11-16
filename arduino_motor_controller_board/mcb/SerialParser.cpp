/* System Defined Header Files */
#include <SoftwareSerial.h>

/* Developer Defined Header Files */
#include "tags.h"
#include "key_events.h"
#include "event_msg.h"
#include "global_defs.h"
#include "utils.h"
#include "configuration.h"
#include "SerialParser.h"


static char token[UART_BUFFER_LEN];


/* Constructor */
SerialParser::SerialParser(){

}

/* Destructor */
SerialParser::~SerialParser(){

}

SerialParser *SerialParser::instance = 0;


/* Add Tag To KeyType mapping */
static TagToKeyType_t lookuptable[] = {
    { BATT_STATUS,      KT_BATT_STATUS    },
    { LEFT_JOYSTICK,    KT_LEFT_JOYSTICK  },
    { RIGHT_JOYSTICK,   KT_RIGHT_JOYSTICK },
    { CROSS_BTN,        KT_CROSS_BTN },
    { SQUARE_BTN,       KT_SQUARE_BTN },
    { TRIANGLE_BTN,     KT_TRIANGLE_BTN },
    { CIRCLE_BTN,       KT_CIRCLE_BTN },
    { UP_BTN,           KT_UP_BTN },
    { DOWN_BTN,         KT_DOWN_BTN },
    { LEFT_BTN,         KT_LEFT_BTN },
    { RIGHT_BTN,        KT_RIGHT_BTN },
    { SHOULDER_BTN_L1,  KT_SHOULDER_BTN_L1 },
    { SHOULDER_BTN_R1,  KT_SHOULDER_BTN_R1 },
    { SHOULDER_BTN_L2,  KT_SHOULDER_BTN_L2 },
    { SHOULDER_BTN_R2,  KT_SHOULDER_BTN_R2 },
    { SHOULDER_BTN_L3,  KT_SHOULDER_BTN_L3 },
    { SHOULDER_BTN_R3,  KT_SHOULDER_BTN_R3 },
    { SELECT_BTN,       KT_SELECT_BTN },
    { START_BTN,        KT_START_BTN },
    { PS_BTN,           KT_PS_BTN },
};


/* Size of Lookup table */
static int NKEYS = sizeof(lookuptable) / sizeof(lookuptable[0]);

/* Converts Tag to KeyType */
eKeyType SerialParser::ConvertTagToKeyType(char *Tag)
{
    for ( int idx = 0; idx < NKEYS; idx++ ) {
        TagToKeyType_t *sym = &lookuptable[idx];
        if ( strcmp(sym->key, Tag) == 0 ) {
            return sym->val;
        }
    }
    return KT_NONE;
}

/* Converts KeyType to Tag */
char * SerialParser::ConvertKeyTypeToTag(eKeyType KeyType)
{
    for ( int idx = 0; idx < NKEYS; idx++ ) {
        TagToKeyType_t *sym = &lookuptable[idx];
        if ( sym->val == KeyType ) {
            return sym->key;
        }
    }
    return KEYTYPE_NONE;
}


char * SerialParser::GetToken(char *StringInput)
{
    unsigned i = 0, token_found = 0, delimiter_after_token = 0;
    unsigned token_idx = 0;
    unsigned len = strlen(StringInput);

    while( len ){
        switch ( StringInput[i] ) {
            case CR:
            case LF:
            case DELIMITER_COORDINATE:
            case DELIMITER_SPACE:
            case DELIMITER_TAG:
                if(token_found == 1)
                    delimiter_after_token = 1;
                break;

            default:
                token_found = 1;
                token[token_idx++] = StringInput[i];
        }

        if(delimiter_after_token == 1)
        {
            /* Break the while loop if a delimiter is hit after token was already found */
            break;
        } else {
            i++;    /* Increment to next input char */
            len--;  /* Decrement overall input string to track loop completion */
        }

    };

    token[token_idx] = '\0';        // NULL terminate

    return token;
}


EventMsg_t * SerialParser::GetBatteryLevel(char *SerialInput, EventMsg_t *Event)
{
    int i = 0;
    char *token = NULL;

    /* Check if Tag Delimiter is intact */
    if(SerialInput[DELIMITER_TAG_INDEX] != DELIMITER_TAG)
    {
        Event->event_type = KT_NONE;
        goto ret;
    }

    token = GetToken(&SerialInput[i]);
    Event->more.battery.batt_lvl = ATOI(token);

    if(Event->more.battery.batt_lvl <= BATT_UNDEFINED ||
            Event->more.battery.batt_lvl >= BATT_MAX_ENTRIES)
    {
        /* Not In Valid Range */
        Event->event_type = KT_NONE;
        goto ret;
    }

ret:
    return Event;
}

EventMsg_t * SerialParser::GetCoOrdinates(char *SerialInput, EventMsg_t *Event)
{
    int i = 0;
    char *token = NULL;

    /* Check if Tag Delimiter is intact */
    if(SerialInput[DELIMITER_TAG_INDEX] != DELIMITER_TAG)
    {
        Event->event_type = KT_NONE;
        goto ret;
    }

    /* Move to beginning of X coordinate */
    while(SerialInput[i] != DELIMITER_TAG)
        i++;

    token = GetToken(&SerialInput[i]);
    Event->more.coordinate.x = ATOI(token);
    if(Event->more.coordinate.x < MIN_VALUE_JOYSTICK ||
            Event->more.coordinate.x > MAX_VALUE_JOYSTICK)
    {
        /* Not In Valid Range */
        Event->event_type = KT_NONE;
        goto ret;
    }

    /* Move to beginning of Y coordinate */
    while(SerialInput[i] != DELIMITER_COORDINATE)
        i++;
    token = GetToken(&SerialInput[i]);
    Event->more.coordinate.y = ATOI(token);
    if(Event->more.coordinate.y < MIN_VALUE_JOYSTICK ||
            Event->more.coordinate.y > MAX_VALUE_JOYSTICK)
    {
        /* Not In Valid Range */
        Event->event_type = KT_NONE;
        goto ret;
    }

ret:
    return Event;
}

EventMsg_t * SerialParser::GetKeyAnalogValue(char *SerialInput, EventMsg_t *Event)
{
    int i = 0;
    char *token = NULL;

    /* Check if Tag Delimiter is intact */
    if(SerialInput[DELIMITER_TAG_INDEX] != DELIMITER_TAG)
    {
        Event->event_type = KT_NONE;
        goto ret;
    }

    /* Move to beginning of Key Press Release */
    while(SerialInput[i] != DELIMITER_TAG)
        i++;

    token = GetToken(&SerialInput[i]);
    Event->more.key.is_pressed = ATOI(token);

    /* Move to beginning of Key Analog Value */
    while(SerialInput[i] != DELIMITER_ANALOG_VAL)
        i++;
    token = GetToken(&SerialInput[i]);
    Event->more.key.analog_val = ATOI(token);
    if(Event->more.key.analog_val < MIN_ANALOG_VALUE ||
            Event->more.key.analog_val > MAX_ANALOG_VALUE)
    {
        /* Not In Valid Range */
        Event->event_type = KT_NONE;
        goto ret;
    }

ret:
    return Event;
}

/* Parse Input received from Software Serial Port */
EventMsg_t * SerialParser::ParseSerialInput(char *SerialInput, EventMsg_t *Event)
{
    int idx = 0;
    eKeyType keytype = KT_NONE;
    char tag[TAG_LENGTH + 1] = {0, 0, 0, 0};

    /* Get TAG from serial input */
    while(idx < TAG_LENGTH)
    {
        tag[idx] = SerialInput[idx];
        idx++;
    };
    tag[idx] = '\0';    /* NULL terminate tag obtained */


    /* Convert the tag to KeyType for further processing */
    keytype = ConvertTagToKeyType(tag);
    switch (keytype) {
        case KT_BATT_STATUS:
            Event->event_type = KT_BATT_STATUS;
            Event = GetBatteryLevel(SerialInput, Event);
            break;
        case KT_LEFT_JOYSTICK:
            Event->event_type = KT_LEFT_JOYSTICK;
            Event = GetCoOrdinates(SerialInput, Event);
            break;
        case KT_RIGHT_JOYSTICK:
            Event->event_type = KT_RIGHT_JOYSTICK;
            Event = GetCoOrdinates(SerialInput, Event);
            break;
        case KT_CROSS_BTN:
            Event->event_type = KT_CROSS_BTN;
            Event = GetKeyAnalogValue(SerialInput, Event);
            break;
        case KT_SQUARE_BTN:
            Event->event_type = KT_SQUARE_BTN;
            Event = GetKeyAnalogValue(SerialInput, Event);
            break;
        case KT_TRIANGLE_BTN:
            Event->event_type = KT_TRIANGLE_BTN;
            Event = GetKeyAnalogValue(SerialInput, Event);
            break;
        case KT_CIRCLE_BTN:
            Event->event_type = KT_CIRCLE_BTN;
            Event = GetKeyAnalogValue(SerialInput, Event);
            break;
        case KT_UP_BTN:
            Event->event_type = KT_UP_BTN;
            Event = GetKeyAnalogValue(SerialInput, Event);
            break;
        case KT_RIGHT_BTN:
            Event->event_type = KT_RIGHT_BTN;
            Event = GetKeyAnalogValue(SerialInput, Event);
            break;
        case KT_DOWN_BTN:
            Event->event_type = KT_DOWN_BTN;
            Event = GetKeyAnalogValue(SerialInput, Event);
            break;
        case KT_LEFT_BTN:
            Event->event_type = KT_LEFT_BTN;
            Event = GetKeyAnalogValue(SerialInput, Event);
            break;
        case KT_SHOULDER_BTN_L1:
            Event->event_type = KT_SHOULDER_BTN_L1;
            Event = GetKeyAnalogValue(SerialInput, Event);
            break;
        case KT_SHOULDER_BTN_R1:
            Event->event_type = KT_SHOULDER_BTN_R1;
            Event = GetKeyAnalogValue(SerialInput, Event);
            break;
        case KT_SHOULDER_BTN_L2:
            Event->event_type = KT_SHOULDER_BTN_L2;
            Event = GetKeyAnalogValue(SerialInput, Event);
            break;
        case KT_SHOULDER_BTN_R2:
            Event->event_type = KT_SHOULDER_BTN_R2;
            Event = GetKeyAnalogValue(SerialInput, Event);
            break;
        case KT_SHOULDER_BTN_L3:
            Event->event_type = KT_SHOULDER_BTN_L3;
            Event = GetKeyAnalogValue(SerialInput, Event);
            break;
        case KT_SHOULDER_BTN_R3:
            Event->event_type = KT_SHOULDER_BTN_R3;
            Event = GetKeyAnalogValue(SerialInput, Event);
            break;
        case KT_SELECT_BTN:
            Event->event_type = KT_SELECT_BTN;
            Event = GetKeyAnalogValue(SerialInput, Event);
            break;
        case KT_START_BTN:
            Event->event_type = KT_START_BTN;
            Event = GetKeyAnalogValue(SerialInput, Event);
            break;
        case KT_PS_BTN:
            Event->event_type = KT_PS_BTN;
            Event = GetKeyAnalogValue(SerialInput, Event);
            break;
        default:
            /* No valid tag found, simply skip */
            break;
    };

  return Event;
}
