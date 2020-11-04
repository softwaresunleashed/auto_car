

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

}

void loop() // run over and over
{
  // Read from the Serial Monitor and send to the Bluetooth module  
  if (Serial.available())
  {
    // Read one char at a time from UART
    c = Serial.read();

    // Echo whatever we type on Serial Port
    Serial.write(c);
  }
  
}
