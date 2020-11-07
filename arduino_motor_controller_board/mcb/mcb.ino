
#include <SoftwareSerial.h>


/* Software Serial Defines */
#define ARDUINO_RX_PIN  2
#define ARDUINO_TX_PIN  3


/* UART Defines */
#define BAUDRATE        115200


SoftwareSerial BtSoftwareSerial(ARDUINO_RX_PIN, ARDUINO_TX_PIN); // RX, TX

void setup()
{
  /* Open serial communications and wait for port to open */
  Serial.begin( BAUDRATE );

  /* wait for serial port to connect. Needed for Physical USB port only */
  while (!Serial);

  /* Set the data rate for the BlueTooth SoftwareSerial port */
  BtSoftwareSerial.begin(BAUDRATE);

  Serial.println("Setup Complete...");
}

/* Run Infinitely */
void loop()
{
  /* If there is something to read on BT Serial Port, print it on serial port */
  if (BtSoftwareSerial.available())
    Serial.write(BtSoftwareSerial.read());

  /* If there is something on Serial Port (Physical), write it to Software Emulated BT port */
  if (Serial.available())
    BtSoftwareSerial.write(Serial.read());
}
