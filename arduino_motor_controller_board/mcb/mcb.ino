
#include <SoftwareSerial.h>


/* Developer defined header files go here */
#include "configuration.h"
#include "SerialParser.h"

#define CR  0xD   /* \r */
#define LF  0xA   /* \n */

SoftwareSerial BtSoftwareSerial(ARDUINO_RX_PIN, ARDUINO_TX_PIN); // RX, TX

void setup()
{
  /* Open serial communications and wait for port to open */
  Serial.begin( BAUDRATE );

  /* wait for serial port to connect. Needed for Physical USB port only */
  while (!Serial);

  /* Set the data rate for the BlueTooth SoftwareSerial port */
  BtSoftwareSerial.begin( BAUDRATE );

  Serial.println("Motor Control Board Setup Complete...");
}

char uart_buffer[UART_BUFFER_LEN];
int uart_buffer_idx = 0;


/* Run Infinitely */
void loop()
{
  char read_char = 0;
  
  /* If there is something to read on BT Serial Port, print it on serial port */
  if (BtSoftwareSerial.available())
  {
    read_char = BtSoftwareSerial.read();
    
    if((read_char == CR || read_char == LF) && uart_buffer_idx) {
      // Line ending occured, parsed the data
      uart_buffer[uart_buffer_idx] = '\0';    // NULL terminate the string
      
      SerialParser().ParseSerialInput(uart_buffer);
      
      Serial.println(uart_buffer);
      
      uart_buffer_idx = 0;
    } else {
      // Add char to temp buffer
      uart_buffer[uart_buffer_idx++] = read_char;
    }
  }


  /* If there is something on Serial Port (Physical), 
    write it to Software Emulated BT port 
    - Not really used in this senario */
  if (Serial.available())
    BtSoftwareSerial.write(Serial.read());
}
