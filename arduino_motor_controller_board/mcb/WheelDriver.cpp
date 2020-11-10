


/* Developer Defined Header Files */
#include "WheelDriver.h"



/*
            MOTOR CONTROL LOGIC
            ===================

          |--------Front----------|
   [W2]<--|----[M2]--------[M1]---|-->[W1]
          |           |           |        
          |           |           |  
   [W3]<--|----[M3]--------[M4]---|-->[W4]
          |--------Back-----------|
      
*/
/*
Valid Values :
------------
Motor 1 & 2 : MOTOR12_64KHZ | MOTOR12_8KHZ  | MOTOR12_2KHZ  | MOTOR12_1KHZ
Motor 3 & 4 : MOTOR34_64KHZ | MOTOR34_8KHZ  |  ----------   | MOTOR34_1KHZ
*/
AF_DCMotor motor1(1, MOTOR12_1KHZ); // create motor #1, 64KHz pwm
AF_DCMotor motor2(2, MOTOR12_1KHZ); // create motor #2, 64KHz pwm
AF_DCMotor motor3(3, MOTOR34_1KHZ); // create motor #3, 64KHz pwm
AF_DCMotor motor4(4, MOTOR34_1KHZ); // create motor #4, 64KHz pwm


/* Constructor */
WheelDriver::WheelDriver() {

}

/* Destructor */
WheelDriver::~WheelDriver(){

}

WheelDriver *WheelDriver::instance = 0;


// Set Speed of Individual Motors
void WheelDriver::InitMotorSpeeds()
{
  // Valid speeds are between 0 to 255
  motor1.setSpeed( INITIAL_SPEED );     // set the speed to 200/255
  motor2.setSpeed( INITIAL_SPEED );     // set the speed to 200/255
  motor3.setSpeed( INITIAL_SPEED );     // set the speed to 200/255
  motor4.setSpeed( INITIAL_SPEED );     // set the speed to 200/255
}


// Forward
void WheelDriver::MoveForward()
{
  // Valid speeds are between 0 to 255
  motor1.run( FORWARD );
  motor2.run( FORWARD );
  motor3.run( FORWARD );
  motor4.run( FORWARD );
}


// Backward
void WheelDriver::MoveBackward()
{
  // Valid speeds are between 0 to 255
  motor1.run( BACKWARD );
  motor2.run( BACKWARD );
  motor3.run( BACKWARD );
  motor4.run( BACKWARD );
}

// Left
void WheelDriver::MoveLeft()
{
  // Valid speeds are between 0 to 255
  motor1.run( FORWARD );
  motor2.run( RELEASE );
  motor3.run( RELEASE );
  motor4.run( FORWARD );
}

// Right
void WheelDriver::MoveRight()
{
  // Valid speeds are between 0 to 255
  motor1.run( RELEASE );
  motor2.run( FORWARD );
  motor3.run( FORWARD );
  motor4.run( RELEASE );
}

// Halt / Break
void WheelDriver::Halt()
{
  // Valid speeds are between 0 to 255
  motor1.run( RELEASE );
  motor2.run( RELEASE );
  motor3.run( RELEASE );
  motor4.run( RELEASE );
}
