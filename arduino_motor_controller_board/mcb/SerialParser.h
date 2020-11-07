/* Need to define functions in extern C within Arduiino IDE to
compile functions spanning multiple files 
*/

class SerialParser{

public:
  SerialParser();
  ~SerialParser();
  
  int ParseSerialInput(char *SerialInput);
  
};
