/* System Defined Header Files */
#include <stdio.h>
#include <string.h>

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
    { BATT_STATUS,    KT_BATT_STATUS    },
    { LEFT_JOYSTICK,  KT_LEFT_JOYSTICK  },
    { RIGHT_JOYSTICK, KT_RIGHT_JOYSTICK },
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
        Event = NULL;
        goto ret;
    }

    token = GetToken(&SerialInput[i]);
    Event->more.battery.batt_lvl = ATOI(token);

    if(Event->more.battery.batt_lvl <= BATT_UNDEFINED ||
            Event->more.battery.batt_lvl >= BATT_MAX_ENTRIES)
    {
        /* Not In Valid Range */
        Event = NULL;
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
        Event = NULL;
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
        Event = NULL;
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
        Event = NULL;
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
        default:
            /* No valid tag found, simply skip */
            break;
    };

  return Event;
}
