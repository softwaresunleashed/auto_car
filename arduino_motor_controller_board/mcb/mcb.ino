/*
  MCB - Motor Controller Board

  Developed for Arduino Uno / Mega. This is the main starting file for MCB which controls the motors 
*/

#include <SoftwareSerial.h>
#include <Arduino_FreeRTOS.h>   // Include Arduino FreeRTOS library

/* Developer defined header files go here */
#include "configuration.h"
#include "global_defs.h"




/*================================================Serial Parser================================================*/
#include "SerialParser.h"

/* Global Variables */
SoftwareSerial BtSoftwareSerial(ARDUINO_RX_PIN, ARDUINO_TX_PIN); // RX, TX

void PrintEventMsg(EventMsg_t * event)
{
    switch (event->event_type) {
        case KT_BATT_STATUS:
            Serial.print("Battery Level = "); 
            Serial.println(event->more.battery.batt_lvl);
            break;
        case KT_LEFT_JOYSTICK:
            Serial.print("JoyStick (Left) x = "); 
            Serial.print(event->more.coordinate.x); 
            Serial.print(" y = "); 
            Serial.println(event->more.coordinate.y);
            break;
        case KT_RIGHT_JOYSTICK:
            Serial.print("JoyStick (Right) x = ");
            Serial.print(event->more.coordinate.x);
            Serial.print(" y = ");
            Serial.println(event->more.coordinate.y);
            break;
        case KT_NONE:    
        default:
            /* No valid tag found, simply skip */
            Serial.println("Invalid Packet");
            break;
    };
}

void SerialParserThread(void *pvParameters)
{
#if SERIAL_EN  
  Serial.println("[SP] Starting SerialParser Thread...");
#endif

  char uart_buffer[UART_BUFFER_LEN];
  int uart_buffer_idx = 0, mark_end_of_line = 0;
  EventMsg_t *event_msg = new EventMsg_t;

  /* Set the data rate for the BlueTooth SoftwareSerial port */
  BtSoftwareSerial.begin( BAUDRATE );

  /* Get Singleton instance of Serial Parser */
  SerialParser *mySerialParser = SerialParser::getInstance();

  /* Thread Loop */
  while(1)
  {
    char read_char = 0;
    
    /* Start with a clean event - everytime!! */
    memset(event_msg, 0, sizeof(EventMsg_t));

    
    /* If there is something to read on BT Serial Port, print it on serial port */
    if(BtSoftwareSerial.available())
    {
      read_char = BtSoftwareSerial.read();
      switch (read_char) {
            case CR:        /* Simply skip \r character */
                break;
            case LF:        /* Look only for \n to mark serial data complete */
                mark_end_of_line = 1;
                break;
            default:
                /* Add char to temp buffer */
                uart_buffer[uart_buffer_idx++] = read_char;
                mark_end_of_line = 0;
                break;
        };

        if(mark_end_of_line)
        {
            /* Line ending occured, parsed the data */
            uart_buffer[uart_buffer_idx] = '\0';    /* NULL terminate the string */

#if SERIAL_PARSER_DEBUG
            Serial.print("["); Serial.print(uart_buffer); Serial.println("]");
#endif 
            /* Parse UART buffer and make a EventMsg to post to Motor Controller thread */
            event_msg = mySerialParser->ParseSerialInput(uart_buffer, event_msg);

#if SERIAL_PARSER_DEBUG
            if(event_msg == NULL)
            {
                Serial.println("event_msg is NULL");  
            } else {
                Serial.print("event_msg type = ");
                Serial.println(event_msg->event_type);
            }
#endif 

            /* Push JoyStick Events to Queues */
            if(event_msg != NULL)
            {
                PrintEventMsg(event_msg);
            }

            /* Re-initialize stuff for next serial data input */
            mark_end_of_line = 0;
            uart_buffer_idx = 0;

            /* TODO : Delete event_msg after consuming in Motor Controller code */
            //delete event_msg;
        }
    } /* if(BtSoftwareSerial.available()) ends */
  };  /* while(1) ends */
}

void initSerialParserThread()
{
#if SERIAL_EN
  Serial.print("Creating Serial Parser Task...");
#endif

  xTaskCreate(SerialParserThread, "Serial Parser Thread", SERIALPARSER_THRD_STACK_SIZE, NULL, 1, NULL);

#if SERIAL_EN
  Serial.println("[Done]");
#endif  
}
/*------------------------------------------------------------------------------------------------------------*/


/*================================================Wheel Driver================================================*/
#include "WheelDriver.h"
#include "global_queue.h"

/* Global Variables */


void WheelDriverThread(void *pvParameters)
{
#if SERIAL_EN  
  Serial.println("[WD] Starting Wheel Driver Thread...");
#endif

  /* Create Queue and wait on it */
  xKeyEventQueue = xQueueCreate( KEY_EVENT_QUEUE_LEN, sizeof( EventMsg_t ) );
  if( xKeyEventQueue == 0 )
  {
    // Queue was not created and must not be used.
    #if SERIAL_EN  
      Serial.println("[WD] [Err] Queue couldn't be created...Halting WheelDriver Thread.");
    #endif
  
    return;
  }

  /* Get Singleton instance of Wheel Driver */
  WheelDriver *myWheelDriver = WheelDriver::getInstance();
  myWheelDriver->InitMotorSpeeds();
  
  /* Consumer Thread Loop */
  while(1)
  {

    /* Wait on a queue and get the event msg */


    /* Send commands to WheelDriver to move vehicle as per input */
    Serial.println("[WD] Move Wheels Forward...");
    myWheelDriver->MoveForward();

    delay(2000);

    Serial.println("[WD] Move Wheels Backward...");
    myWheelDriver->MoveBackward();

    delay(2000);
  
    Serial.println("[WD] Move Wheels Left...");
    myWheelDriver->MoveLeft();

    delay(2000);

    Serial.println("[WD] Move Wheels Right...");
    myWheelDriver->MoveRight();

    delay(2000);
  };  /* while(1) ends */
}


void initWheelDriverThread()
{
#if SERIAL_EN
  Serial.print("Creating Wheel Driver Task...");
#endif

  xTaskCreate(WheelDriverThread, "Wheel Driver Thread", WHEELDRIVER_THRD_STACK_SIZE, NULL, 1, NULL);

#if SERIAL_EN
  Serial.println("[Done]");
#endif  
}
/*------------------------------------------------------------------------------------------------------------*/

void createSystemThreads()
{
  
  initSerialParserThread();   /* Serial Parser Thread */
  //initWheelDriverThread();    /* Wheel Driver Thread */
}


void setup()
{
  /* Open serial communications and wait for port to open */
  Serial.begin( BAUDRATE );

  /* wait for serial port to connect. Needed for Physical USB port only */
  while (!Serial);

  Serial.println("  "); Serial.println("  "); Serial.println("  ");
  Serial.println("===================================="); 
  Serial.println("Motor Control Board Setup...[BEGIN]");

  /* Initialize Threads */
  createSystemThreads();  

  Serial.println("Motor Control Board Setup...[DONE]");
  Serial.println("===================================="); 
}



/* Run Infinitely */
void loop()
{
  /* If there is something on Serial Port (Physical), write it to Software Emulated BT port 
      - Not really used in this senario 
   */
  if (Serial.available())
    BtSoftwareSerial.write(Serial.read());
}
