#include "Keyboard.h"
/*
The arduino promicro acts as a gateway between the serial data sent from the ESP and the destination device.
It will type the password to the destination device.
TODO: 
* Implement CRC32 of the password
* Receive the data as a JSON string, containing the password and the CRC
* Add changelayout command
*/
// String that is going to be received from the ESP32
String inStr;
void setup() {
  // start serial port at 115200 bps and wait for port to open:
  // Serial1 is on ports TXO and RXI of the Pro-Micro
  Serial1.begin(115200);
}

void loop() {
  // If there's data on the serial buffer
  if (Serial1.available() > 0) {
    // Read string until the first line break.
    inStr = Serial1.readStringUntil("\r\n");
    // Set the keyboard layout and enable HID mode
    Keyboard.begin(KeyboardLayout_es_ES);
    // Type the password on the destination device, removing the line breaks. I know, this could be handled differently, but it works right?
    Keyboard.print(removeLineBreaks(inStr));
    // Exit HID mode. TEST: Will it work on windows when the mode changes?
    Keyboard.end();
  }
}

// Function to remove line breaks from a string, I think I tested ".trim()" but something was wrong with that. But also maybe not, I will try it again once this is gitted.
String removeLineBreaks(String inputString) {
  String outputString = "";

  for (int i = 0; i < inputString.length(); i++) {
    char currentChar = inputString.charAt(i);

    // Check if the current character is not a newline or carriage return
    if (currentChar != '\n' && currentChar != '\r') {
      outputString += currentChar;
    }
  }
  return outputString;
}