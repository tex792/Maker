/*


This sketch has an LCD screen that displays one message when
a button is held pressed down, and another message when it is
not pressed.

The portion of the sketch for the LCD is based on the Sparkfun Inventor's
Kit example sketch #15.
*/


//Load the LiquidCrystal library, which will give us
// commands to interface to the LCD:

#include <LiquidCrystal.h>

// Initialize the library with the pins we're using.
// (Note that you can use different pins if needed.)
// See http://arduino.cc/en/Reference/LiquidCrystal
// for more information:

LiquidCrystal lcd(12,11,5,4,3,2);

// Set the push button as connected to pin 13

const int buttonPin = 13;

//clearLCD is a variable that will store a 1 or 0 and governs when the
//LCD screen needs to be cleared. It is used in the loop portion of the
//sketch but is initialized here so that it doesn't reset whenever the
//loop runs.

int clearLCD = 0; 

void setup()
{

  lcd.clear(); //Clear the LCD

  lcd.setCursor(0, 0); //Set the LCD cursor at the initial position

  //set the push button pin as an input

  pinMode(buttonPin, INPUT);

  // Serial display is added to this sketch as an extra feature, but 
  // isn't necessary for the sketch's main operation.
  
  // We use the Serial.begin() function to initialize the port
  // and set the communications speed.
  
  // The speed is measured in bits per second, also known as
  // "baud rate". 9600 is a very commonly used baud rate,
  // and will transfer about 10 characters per second.

  Serial.begin(9600);
  
}


void loop()
{

  //Initialize the variable for the state of the button (pressed or
  //not pressed)

  int buttonState;

  //Read the state of the button. If it is not pressed, the state will be
  //read as HIGH (minimal current flows and the pullup resistor pulls the
  //voltage up to ~5V). If the button is pressed, the state will be read
  //as LOW (the circuit is closed, allowing current to flow and the
  //voltage drops)

  buttonState = digitalRead(buttonPin);

  Serial.println(buttonState); //output to serial display

  lcd.setCursor(0, 0); //Set the LCD cursor at the initial position

  if (buttonState == LOW)
  {
    while (clearLCD == 0)//If we enter this 'if' statement for the first
                         //time, clear LCD will be set as 0. We will then
                         //clear the screen and set clearLCD to 1 using
                         //this 'while' statement. We only want to clear
                         //the screen once so that the text on the LCD
                         //doesn't blink.
    {
    lcd.clear();
    clearLCD=clearLCD+1;
    }
    lcd.print("I'm on :)");
  }
  else
  {
    clearLCD = 0; //We will reset clearLCD to 0 here so that when the
                  //button is pressed again, we will go into the 'while'
                  //statement that clears the LCD.
    lcd.print("I'm off :(");
  }
  
}

