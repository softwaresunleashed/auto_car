/*
  MCB - Motor Controller Board

  Developed for Arduino Uno / Mega. This is the main starting file for MCB which controls the motors 
*/

#include <SoftwareSerial.h>
#include <Arduino_FreeRTOS.h>   // Include Arduino FreeRTOS library

/* Developer defined header files go here */
#include "configuration.h"
#include "global_defs.h"



/*================================================ System Queues ================================================*/
#include "global_queue.h"
#include "event_msg.h"

void createKeyEventsQueue()
{
#if SERIAL_EN
  Serial.print("-----> Creating Key Event Queue...");
#endif
  
  /* Create Key Event Queue */
  xKeyEventQueue = xQueueCreate( KEY_EVENT_QUEUE_LEN, sizeof( EventMsg_t ) );
  if( xKeyEventQueue == 0 )
  {
    // Queue was not created and must not be used.
    #if SERIAL_EN  
      Serial.println("[Err] Queue couldn't be created...Halting system.");
    #endif
  
    while(1);     // Halt forever
  }  

#if SERIAL_EN
  Serial.println("[DONE]");
#endif
  
}

/*------------------------------------------------------------------------------------------------------------*/





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

            /* Push JoyStick Events to KeyEvent Queue */
            if(event_msg != NULL)
            {
#if SERIAL_PARSER_DEBUG
                Serial.print("[SP] "); PrintEventMsg(event_msg);
#endif
                xQueueSend(xKeyEventQueue, event_msg, portMAX_DELAY); /* Send key message to Receiver thread */
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
  Serial.print("-----> Creating Serial Parser Task...");
#endif

  xTaskCreate(SerialParserThread,
              "Serial Parser Thread",
              SERIALPARSER_THRD_STACK_SIZE,
              NULL,
              SERIALPARSER_THRD_PRIO,
              NULL);

#if SERIAL_EN
  Serial.println("[Done]");
#endif  
}
/*------------------------------------------------------------------------------------------------------------*/





/*================================================Wheel Driver================================================*/
#include "WheelDriver.h"


/* Global Variables */


void NavigateWheels(EventMsg_t *event_msg)
{
  

}


void WheelDriverThread(void *pvParameters)
{
#if SERIAL_EN  
  Serial.println("[WD] Starting Wheel Driver Thread...");
#endif

    EventMsg_t wd_key_event_msg;


  /* Get Singleton instance of Wheel Driver */
  WheelDriver *myWheelDriver = WheelDriver::getInstance();
  myWheelDriver->InitMotorSpeeds();
  
  /* Consumer Thread Loop */
  while(1)
  {
    /* Wait on a queue and get the event msg */
    if (xQueueReceive(xKeyEventQueue, &wd_key_event_msg, portMAX_DELAY) == pdPASS) {
#if SERIAL_EN 
        Serial.print("[WD] ");
        PrintEventMsg(&wd_key_event_msg);
#endif
        /* Navigate Wheels as per inputs recieved */
    switch (wd_key_event_msg.event_type) {
        case KT_BATT_STATUS:
            /* TBD : Need to decide what to do on Low Battery Status */
            break;
        case KT_LEFT_JOYSTICK:
            /* If x is negative, move left */
            if(wd_key_event_msg.more.coordinate.x < 0)
            {
              Serial.println("[WD] Move Wheels Left...");
              myWheelDriver->MoveLeft();
            }

            /* If x is positive, move right */
            if(wd_key_event_msg.more.coordinate.x > 0)
            {
              Serial.println("[WD] Move Wheels Right...");
              myWheelDriver->MoveRight();
            }
            break;
        case KT_RIGHT_JOYSTICK:
            /* If y is negative, move Forward */
            if(wd_key_event_msg.more.coordinate.y < 0)
            {
              Serial.println("[WD] Move Wheels Forward...");
              myWheelDriver->MoveForward();
            }

            /* If y is positive, move Backward */
            if(wd_key_event_msg.more.coordinate.y > 0)
            {

              Serial.println("[WD] Move Wheels Backward...");
              myWheelDriver->MoveBackward();
            }
            break;
        case KT_NONE:    
        default:
            /* No valid tag found, simply skip */
            Serial.println("Invalid Packet");
            break;
    };


        /* Mark previous event as consumed - KT_NONE */
        wd_key_event_msg.event_type = KT_NONE;
    }
    
  };  /* while(1) ends */
}


void initWheelDriverThread()
{
#if SERIAL_EN
  Serial.print("-----> Creating Wheel Driver Task...");
#endif

  xTaskCreate(WheelDriverThread, 
              "Wheel Driver Thread",
              WHEELDRIVER_THRD_STACK_SIZE,
              NULL,
              WHEELDRIVER_THR_PRIO,
              NULL);

#if SERIAL_EN
  Serial.println("[Done]");
#endif  
}
/*------------------------------------------------------------------------------------------------------------*/

void InitSysEnv()
{
  /* Initialize Queues */
#if SERIAL_EN  
  Serial.println("[SYS] Creating System Queues...");
#endif

  createKeyEventsQueue();
  
#if SERIAL_EN 
  Serial.println("[SYS] Creating System Queues...[DONE]");
#endif

  /* Threads Go next */
#if SERIAL_EN  
  Serial.println("[SYS] Creating System Threads...");
#endif

  initSerialParserThread();   /* Serial Parser Thread */
  initWheelDriverThread();    /* Wheel Driver Thread */

#if SERIAL_EN  
  Serial.println("[SYS] Creating System Threads...[DONE]");
#endif
}


void setup()
{
  /* Open serial communications and wait for port to open */
  Serial.begin( BAUDRATE );

  /* wait for serial port to connect. Needed for Physical USB port only */
  while (!Serial);

  Serial.println("  "); Serial.println("  "); Serial.println("  ");
  Serial.println("============================================");
  Serial.println("Motor Control Board Initialization...[BEGIN]");
  Serial.println("============================================");
  
  /* Initialize System Environment - Threads, Queues */
  InitSysEnv();  
  
  Serial.println("============================================");
  Serial.println("Motor Control Board Initialization...[DONE] ");
  Serial.println("============================================");
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
