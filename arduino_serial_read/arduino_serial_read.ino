
#include <SoftwareSerial.h>


// Create a software serial port to listen to BT messages
SoftwareSerial mySoftwareSerial(2, 3); // RX, TX

#define BAUDRATE    115200



char c=' ';
boolean NL = true;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(BAUDRATE);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Native USB only
  }

  Serial.println("\n\r ");
  Serial.print("Sketch: "); Serial.println(__FILE__);
  Serial.print("Uploaded: "); Serial.println(__DATE__);
  Serial.println(" ");



  // set the data rate for the SoftwareSerial port
  mySoftwareSerial.begin(BAUDRATE);
  mySoftwareSerial.println("Software Serial Initiliazed");

}

void loop() // run over and over
{

  /* Display contents received from BT dongle */
  if (mySoftwareSerial.available())
    Serial.write(mySoftwareSerial.read());

  /* Send data from serial port to BT dongle */
  if (Serial.available())
  {
    // Read one char at a time from UART
    c = Serial.read();

    // Send data to BT dongle
    mySoftwareSerial.write(c);

    // Echo whatever we type on Serial Port
    Serial.write(c);
  }
  
#if 0
  // Read from the Serial Monitor and send to the Bluetooth module  
  if (Serial.available())
  {
    // Read one char at a time from UART
    c = Serial.read();

    // Echo whatever we type on Serial Port
    Serial.write(c);
  }
#endif

}
