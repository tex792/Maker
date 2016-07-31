/*
 * This sketch uses a few basic functions as an introduction and test bed for XBee modules
 * 
 * This sketch requires an XBee, XBee Shield and another XBee tied to
your computer (via a USB Explorer). You can use XCTU's console, or
another serial terminal program (even the serial monitor!), to send
commands to the Arduino.

Hardware Hookup:
  The Arduino shield makes all of the connections you'll need
  between Arduino and XBee. Make sure the SWITCH IS IN THE 
  "DLINE" POSITION.
*/


// SoftwareSerial is used to communicate with the XBee
#include <SoftwareSerial.h>
// XBee's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
// XBee's DIN (RX) is connected to pin 3 (Arduino's Software TX)
SoftwareSerial XBee(2, 3); // Arduino RX, TX (XBee Dout, Din); This line declares 'XBee' as the indentifier for when we want to perform a serial action and sets
                           //the receive and transmit pins


void setup()
{
  // Initialize XBee Software Serial port. Make sure the baud
  // rate matches your XBee setting (9600 is default).
  XBee.begin(9600);
  printMenu(); // Print a helpful menu:
}


void loop()
{
  while (XBee.available() < 3); //The sketch will hold here until 3 bytes of data are available from the serial monitor
  char letter1 = XBee.read(); //Each time we read from the serial monitor, we grab the next byte of data (the next character)
  char letter2 = XBee.read();
  int letter3 = XBee.read();

  XBee.println(); //Print each variable
  XBee.print("Letter1 is ");
  XBee.println(letter1);
  XBee.print("Letter2 is ");
  XBee.println(letter2);
  XBee.print("Letter3 is ");
  XBee.println(letter3);
}


void printMenu() //This function prints a statement veryfying that the XBees are connected
{
  XBee.println();
  XBee.println("Your XBee explorer and shield are both talking and ready to rock :D");
}


