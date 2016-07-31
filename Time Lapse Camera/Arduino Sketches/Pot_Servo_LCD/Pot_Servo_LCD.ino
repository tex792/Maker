/*
  Control the position of a servo with a potentiometer
  Output position to an LCD
  Also displays to the serial monitor
	
Hardware connections:

  Potentiometer:
	
    Potentiometers have three pins. When we're using it as a
    voltage divider, we connect the outside pins to power and
    ground. The middle pin will be the signal (a voltage which
    varies from 0 Volts to 5 Volts depending on the position of
    the knob).

    Connect the middle pin to an ANALOG IN pin on the Arduino.
    Connect one of the outside pins to 5V.
    Connect the other outside pin to GND.

*/



int potPin = 0;    // The potentiometer is connected to this analog pin

#include <LiquidCrystal.h>  //LCD library

LiquidCrystal lcd(12,11,5,4,3,2); // Initialize the library with the pins we're using.

int potOld = 0; //Initialize

#include <Servo.h>  // servo library

Servo servo1;  // servo control object

int servoPin = 8; // Set the digital pin that the servo will be attached to


void setup()
{
  lcd.clear(); //Clear the LCD

  lcd.setCursor(0, 0); //Set the LCD cursor at the initial position

  Serial.begin(9600); //Initialize the port and set the baud rate (communication speed)

  servo1.attach(servoPin); // We'll now "attach" the servo1 object to a digital pin
}


void loop() 
{

  int potValue; // Declare  integer to store the value of the potentiometer:

  // The potentiometer is set up as a voltage divider, so that
  // when you turn it, the voltage on the center pin will vary
  // from 0V to 5V. We've connected the center pin on the
  // potentiometer to the Arduino's analog input 0.

  // The Arduino can read external voltages on the analog input
  // pins using a built-in function called analogRead(). This
  // function takes one input value, the analog pin we're using
  // (sensorPin, which we earlier set to 0). It returns an integer
  // number that ranges from 0 (0 Volts) to 1023 (5 Volts).
  // We're sticking this value into the sensorValue variable:

  potValue = analogRead(potPin); //read pot value
  potValue = map(potValue, 0, 1023, 7, 181); //map the pot value (ranged 0-1023) to a new range of 7-181
  potValue = constrain(potValue, 7, 181); //constrain the value between 7-181
  //The bottom value was constrained to 7 because the servo jumps
  //excessively with values between 0-6

  Serial.println(potValue); //output to serial display
  lcd.setCursor(0, 0); //Set the LCD cursor at the initial position
  lcd.print(potValue); //output to the lcd

  servo1.write(potValue);  // Move the servo to the position set by the pot
  
  //We only want to clear the LCD screen if we turn the pot to a new value
  //Otherwise the displated number with flash constantly
  if (potOld != potValue) //check if we have a new value 
  {
    lcd.clear(); //clear the lcd
    //Serial.println("clear"); //also print to the serial monitor as a debugging measure
    //The line above was commented out becuase it appears that writing too much to the serial
    //monitor causes the servo to jump excessively
  }

  potOld = potValue; //reset the potOld variable for the next loop
  
}

