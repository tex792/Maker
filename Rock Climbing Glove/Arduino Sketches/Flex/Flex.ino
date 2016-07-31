/*
  Read the output from a flex sensor and transmit it across an XBee network
*/

const int flexpin = 0;  //Define the analog input pin to measure flex sensor position
#include <SoftwareSerial.h> //SoftwareSerial is used to communicate with the XBee
// XBee's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
// XBee's DIN (RX) is connected to pin 3 (Arduino's Software TX)
SoftwareSerial XBee(2, 3); // Arduino RX, TX (XBee Dout, Din); This line declares 'XBee' as the indentifier for when we want to perform a serial action and sets
                           //the receive and transmit pins

void setup() 
{ 
  XBee.begin(9600); //Initialize XBee Software Serial port. Make sure the baud rate matches your XBee setting (9600 is default).
  printMenu(); // Print a helpful menu
} 


void loop() 
{ 
  int flexposition;    // Input value from the analog pin.
  
  flexposition = analogRead(flexpin);  //Read the position of the flex sensor (0 to 1023)

  //The voltage divider circuit only returns a portion of the 0-1023 range of analogRead(). The flex sensors we use are usually in the 600-900 range.
  //To help tune our program, we'll use the serial port to print out our values to the serial monitor window and then map values approppriately.
  //Serial.print("sensor: ");
  //Serial.println(flexposition);

  XBee.println(flexposition); //Print the flex sensor's position to the XBee network
}


void printMenu()
{
  // Everything is "F()"'d -- which stores the strings in flash.
  // That'll free up SRAM for more importanat stuff.
  XBee.println();
  XBee.println(F("Arduino XBee Flex Sensor!"));
  delay(2000);
}


