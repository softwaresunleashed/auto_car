#include "key_events.h"
#include "event_msg.h"



class SerialParser{

private:
    SerialParser();
    ~SerialParser();

    static SerialParser *instance;

    char * GetToken(char *StringInput);
    eKeyType ConvertTagToKeyType(char *Tag);
    EventMsg_t * GetCoOrdinates(char *SerialInput, EventMsg_t *Event);
    EventMsg_t * GetBatteryLevel(char *SerialInput, EventMsg_t *Event);


public:
    static SerialParser * getInstance() {
        if (!instance)
            instance = new SerialParser;
        return instance;
    }

    EventMsg_t * ParseSerialInput(char *SerialInput, EventMsg_t *Event);
};
