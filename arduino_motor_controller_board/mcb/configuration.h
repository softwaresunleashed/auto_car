#ifndef __CONFIGURATION_H_
#define __CONFIGURATION_H_



#define UNO   1
#define MEGA  2

#define CURRENT_BOARD   MEGA

/******************************************************************************** 
Limitations of SoftwareSerial library
=====================================
The library has the following known limitations:

- If using multiple software serial ports, only one can receive data at a time.
- Not all pins on the Mega and Mega 2560 support change interrupts, 
      -- so only the following can be used for RX: 10, 11, 12, 13, 14, 15, 50, 
         51, 52, 53, A8 (62), A9 (63), A10 (64), A11 (65), A12 (66), A13 (67), 
         A14 (68), A15 (69).
- Not all pins on the Leonardo and Micro support change interrupts,
      -- so only the following can be used for RX: 8, 9, 10, 11, 14 (MISO), 
         15 (SCK), 16 (MOSI).
- On Arduino or Genuino 101 the current maximum RX speed is 57600bps
- On Arduino or Genuino 101 RX doesn't work on Pin 13
********************************************************************************/
/* Software Serial RX-TX Defines...Refer text above as per your board used */
#if (CURRENT_BOARD == UNO)          /* Arduino UNO Configuration */
  #warning "CURRENT_BOARD is Arduino Uno"
  #define ARDUINO_RX_PIN  2
  #define ARDUINO_TX_PIN  3
#elif (CURRENT_BOARD == MEGA)    /* Arduino MEGA Configuration */
  #warning "CURRENT_BOARD is Arduino Mega"
  #define ARDUINO_RX_PIN  69  //A15
  #define ARDUINO_TX_PIN  3
#else
  #error "Select Board by defining CURRENT_BOARD in configuration.h"
#endif

/* Wheel Driver */
#define INITIAL_SPEED     200


/* UART Defines */
#define BAUDRATE            115200
#define UART_BUFFER_LEN     200      /* Fix : In some cases when corrupted line is recieved on a serial connection, its lenght is 20+, so keeping a safe value */

/* FreeRTOS */
#define SERIALPARSER_THRD_STACK_SIZE   300   //128
#define WHEELDRIVER_THRD_STACK_SIZE    300   //128


/* Debug Flags */
#define SERIAL_EN           1
#define MOTOR_CONTROL_EN    0
#define OLED_SUPPORTED      0
#define PROXIMITY_RADAR_EN  0
#define SERIAL_PARSER_DEBUG 1

#endif  /* __CONFIGURATION_H_ */
