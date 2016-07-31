/*
SparkFun Inventor's Kit
Example sketch 05

PUSH BUTTONS

  Use pushbuttons for digital input

  Previously we've used the analog pins for input, now we'll use
  the digital pins for input as well. Because digital pins only
  know about HIGH and LOW signals, they're perfect for interfacing
  to pushbuttons and switches that also only have "on" and "off"
  states.
  
  We'll connect one side of the pushbutton to GND, and the other
  side to a digital pin. When we press down on the pushbutton,
  the pin will be connected to GND, and therefore will be read
  as "LOW" by the Arduino.
  
  But wait - what happens when you're not pushing the button?
  In this state, the pin is disconnected from everything, which 
  we call "floating". What will the pin read as then, HIGH or LOW?
  It's hard to say, because there's no solid connection to either
  5 Volts or GND. The pin could read as either one.
  
  To deal with this issue, we'll connect a small (10K, or 10,000 Ohm)
  resistance between the pin and 5 Volts. This "pullup" resistor
  will ensure that when you're NOT pushing the button, the pin will
  still have a weak connection to 5 Volts, and therefore read as
  HIGH.
  
  (Advanced: when you get used to pullup resistors and know when
  they're required, you can activate internal pullup resistors
  on the ATmega processor in the Arduino. See
  http://arduino.cc/en/Tutorial/DigitalPins for information.)

Hardware connections:

  Pushbuttons:
  
    Pushbuttons have two contacts that are connected if you're
    pushing the button, and disconnected if you're not.
    
    The pushbuttons we're using have four pins, but two pairs
    of these are connected together. The easiest way to hook up
    the pushbutton is to connect two wires to any opposite corners.

    Also connect 10K resistors (brown/black/red) between
    digital pin and GND. These are called "pullup"
    resistors. They ensure that the input pin will be either
    5V (unpushed) or GND (pushed), and not somewhere in between.
    (Remember that unlike analog inputs, digital inputs are only
    HIGH or LOW.)

*/

const int buttonPin = 10;  // pushbutton pin

void setup()
{
  
  pinMode(buttonPin, INPUT); //Set up the pushbutton pin to be an input

  Serial.begin(9600); //Initialize the port and set the baud rate (communication speed)
}
 


void loop()
{
  int buttonState;

  // Since a pushbutton has only two states (pushed or not pushed),
  // we've run it into a digital input. To read an input, we'll
  // use the digitalRead() function. This function takes one
  // parameter, the pin number, and returns either HIGH (5V)
  // or LOW (GND).

  buttonState = digitalRead(buttonPin); //Read the current pushbutton states into a variable

  // Remember that if the button is being pressed, it will be
  // connected to GND. If the button is not being pressed,
  // the pullup resistor will connect it to 5 Volts.

  // So the state will be LOW when it is being pressed,
  // and HIGH when it is not being pressed.

  Serial.println(buttonState); //Display to serial monitor
  
}
