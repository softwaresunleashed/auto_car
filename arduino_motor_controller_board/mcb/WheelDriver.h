/* System Defined Header Files */
#include <AFMotor.h>

#include "key_events.h"
#include "event_msg.h"
#include "configuration.h"


class WheelDriver{

private:

    static WheelDriver *instance;


    
    WheelDriver();
    ~WheelDriver();

public:

    static WheelDriver * getInstance() {
        if (!instance)
            instance = new WheelDriver;
        return instance;
    }

    void InitMotorSpeeds();
    void MoveForward();
    void MoveBackward();
    void MoveLeft();
    void MoveRight();
    void Halt();
    
};
