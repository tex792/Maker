// Tell servo to go from 0 to 180 degrees, stepping by one degree
//Servo position is displayed in the serial monitor
//Also displays position to an LCD

#include <Servo.h>  // servo library

Servo servo1;  // servo control object

int servoPin = 8; // Set the digital pin that the servo will be attached to

int servoDelay = 50; //Set the delay between steps

#include <LiquidCrystal.h>  //LCD library

LiquidCrystal lcd(12,11,5,4,3,2); // Initialize the library with the pins we're using.

int clearLCD = 0; //clearLCD is a variable that will store a 1 or 0 and governs when the
                  //LCD screen needs to be cleared.


void setup()
{
 
  servo1.attach(servoPin); // We'll now "attach" the servo1 object to a digital pin

  lcd.clear(); //Clear the LCD

  lcd.setCursor(0, 0); //Set the LCD cursor at the initial position

  Serial.begin(9600); //Initialize the port and set the baud rate (communication speed)

}


void loop()
{
  int position;  //Initialize variable to store the servo position

  for(position = 180; position >= 0; position -= 1) // Tell servo to go to 0 degrees, stepping by one degree
  {                                
    Serial.println(servo1.read()); //output to serial display
    servo1.write(position);  // Move to next position
    lcd.print(position);
    delay(servoDelay); // Short pause to allow it to move, uses global variable 'servoDelay'
    lcd.clear(); //Clear the LCD
  }
}

