
#ifndef __CONFIGURATION_H_
#define __CONFIGURATION_H_


/* Software Serial Defines */
#define ARDUINO_RX_PIN  2
#define ARDUINO_TX_PIN  3


/* UART Defines */
#define BAUDRATE            115200
#define UART_BUFFER_LEN     50      /* Fix : In some cases when corrupted line is recieved on a serial connection, its lenght is 20+, so keeping a safe value */

/* FreeRTOS */
#define SERIALPARSER_THRD_STACK_SIZE   150   //128


/* Debug Flags */
#define SERIAL_EN           1
#define MOTOR_CONTROL_EN    0
#define OLED_SUPPORTED      0
#define PROXIMITY_RADAR_EN  0
#define SERIAL_PARSER_DEBUG 1

#endif  /* __CONFIGURATION_H_ */
