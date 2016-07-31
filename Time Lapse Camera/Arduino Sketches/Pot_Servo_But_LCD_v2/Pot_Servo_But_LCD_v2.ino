/*
  Control the position of a servo with a potentiometer
  Output position to an LCD
  Also displays to the serial monitor
  Press a button to set the servo initial then final postion
  Finally step the servo from initial to final postion
  
	
Hardware connections:

  Potentiometer
  Servo
  LCD (w/ contrast servo)
  Button

*/



int potPin = 0;    // The potentiometer is connected to this analog pin
int potOld = 0; //Initialize variable that will help control when we clear the LCD

#include <LiquidCrystal.h>  //LCD library
LiquidCrystal lcd(12,11,5,4,3,2); // Initialize the LCD library with the pins we're using

#include <Servo.h>  // servo library
Servo servo1;  // servo control object
int servoPin = 8; // Set the digital pin that the servo will be attached to

int buttonPin = 10;  // Set pushbutton pin


void setup()
{
  lcd.begin(16,2); //Specify th dimension of the LCD (width, height)
  lcd.clear(); //Clear the LCD
  lcd.setCursor(0, 0); //Set the LCD cursor at the initial position

  Serial.begin(9600); //Initialize the port and set the baud rate (communication speed)
  
  servo1.attach(servoPin); // We'll now "attach" the servo object to a digital pin

  pinMode(buttonPin, INPUT); // Set up the pushbutton pins to be an input:
}


void loop() 
{
  int startServo = setServo(); //Set the initial position for the servo by using the setServo function
  //Serial.print("startServo was set as "); //Display the startServo value to the serial monitor
  //Serial.println(startServo);

  delay(2000); //Hold the sketch so we can see the output to the serial monitor

  int endServo = setServo(); //Set the final postion for the servo by using the setServo function
  //Serial.print("endServo was set as "); //Display the endServo value to the serialMonitor
  //Serial.println(endServo); //Troubleshoot

  delay(2000); //Hold the sketch so we can see the output to the serial monitor

  int timeMove = setTime(); //Set the time to move from start to end position using the setTime function
  //Serial.print("timeMove was set as "); //Display the endServo value to the serialMonitor
  //Serial.println(timeMove); //Troubleshoot

  moveServo(startServo, endServo, timeMove); //UPDATE THIS AND THE FUNCTION TO ACCEPT SETTIME

  while(!Serial.available()) //This empty loop is holding the sketch still here. Serial.available() returns 'true' if data has been sent to
  {                          //the board through the serial monitor, which we haven't done. So we add the '!' to make the statement true
                             //and stay within the loop.
  }
}


int setServo() //This function lets you adjust the servo position with the pot, and
               //when you hit the button, the function returns the value where the servo is at
{
  int potValue; // Declare integer to store the value of the potentiometer
  int buttonState = digitalRead(buttonPin); //declare integer to store the button state

  while(buttonState==HIGH) //While the button is NOT pressed (i.e. reading HIGH for 5V), this function will keep running
                           //We press the button when we reach the desired servo position
  {
    buttonState = digitalRead(buttonPin); //Read the button position
    
    potValue = analogRead(potPin); //read pot value
    potValue = map(potValue, 0, 1023, 7, 161); //map the pot value (ranged 0-1023) to a new range of 7-161
    potValue = constrain(potValue, 7, 161); //constrain the value between 7-161
    //The bottom value was constrained to 7 because the servo becomes
    //twitchy with values between 0-6. The top value was constrained 
    //to 160 because this servo's real range doesn't go all the way to 180

    Serial.println(potValue); //output to serial display
    Serial.println(buttonState); //output to serial display
    
    lcd.setCursor(0, 0); //Set the LCD cursor at the initial position
    lcd.print(potValue); //output to the lcd
    
    servo1.write(potValue);  // Move the servo to the position set by the pot
  
    //We only want to clear the LCD screen if we turn the pot to a new value
    //Otherwise the displated number with flash constantly
    if (potOld != potValue) //check if we have a new value
    {
    lcd.clear(); //clear the lcd
    }

    potOld = potValue; //reset the potOld variable for the next loop
    
  }

  int positionServo = potValue; //After we press the button and exit the loop above, we store the desired servo position here
  
  return positionServo; //Return the desired servo position
}


int setTime()
{
  int potValue; // Declare integer to store the value of the potentiometer
  int buttonState = digitalRead(buttonPin); //declare integer to store the button state

  while(buttonState==HIGH) //While the button is NOT pressed (i.e. reading HIGH for 5V), this function will keep running
                           //We press the button when we reach the desired servo position
  {
    buttonState = digitalRead(buttonPin); //Read the button position
    
    potValue = analogRead(potPin); //read pot value
    potValue = map(potValue, 0, 1023, 0, 181); //map the pot value (ranged 0-1023) to a new range of 0-180
    potValue = constrain(potValue, 0, 181); //constrain the value between 0-180

    Serial.println(potValue); //output to serial display
    Serial.println(buttonState); //output to serial display
    
    lcd.setCursor(0, 0); //Set the LCD cursor at the initial position
    lcd.print(potValue); //output to the lcd
  
    //We only want to clear the LCD screen if we turn the pot to a new value
    //Otherwise the displated number with flash constantly
    if (potOld != potValue) //check if we have a new value
    {
    lcd.clear(); //clear the lcd
    }

    potOld = potValue; //reset the potOld variable for the next loop
  }

  int timeMove = potValue; //After we press the button and exit the loop above, we store the desired servo position here
  
  return timeMove;
}


void moveServo(int startServo, int endServo, int timeMove) //This function receives the desired start and end servo positions and 
                                                           //steps the servo slowly from one to the other 
{
  int position; //initialize the variable for the servo's position

  //The variable to determine to delay length must be declared as a 'long' variable. For ATMega based boards (in this case the RedBoard), you can only store
  //int values in the range of -32,768 to 32,767 (16-bit (2-byte) value). For this sketch, our 'delay' value has the potential be over that limit.
  //See Arduino website's full explanation of 'int' for more detail.
  //Notice that at least one of the values must be followed by an 'L'. In this case it is right after 60000.
  long servoDelay = ((timeMove*60000L)/abs(startServo-endServo)); //Set the delay between servo steps

  lcd.clear(); //Clear the LCD
  lcd.setCursor(0, 0); //Set the LCD cursor at the initial position
  lcd.print(startServo); //Then next few lines display on the LCD the positions that the servo will move from and to and the total time
  lcd.print(" to "); 
  lcd.print(endServo);
  lcd.print(", ");
  lcd.print(timeMove);
  lcd.print("m");
  lcd.setCursor(0, 1); //Set the LCD cursor at the 1st column, 2nd row)
  lcd.print(servoDelay); //Next we display on the LCD the total delay between movements
  lcd.print("ms del");
  delay(5000); //Delay a bit to allow time to user to read and verify the settings
   
  if((startServo-endServo)<0) //We need different loops for scenarios where the start position is lower than
                              //end position or visa versa.
  {
    for(position = startServo; position <= endServo; position += 1) // Tell servo to go from start to finish by steupping one degree UP
    {                                
      servo1.write(position);  // Move servo to next position
      lcd.clear(); //Clear the LCD
      lcd.print(servo1.read()); //Display to LCD
      Serial.println(servo1.read()); //Display to serial display
      delay(servoDelay); // Short pause between steps, uses global variable 'servoDelay'
    }
  }
  else
  {
    for(position = startServo; position >= endServo; position -= 1) // Tell servo to go from start to finish by stepping one degree DOWN
    {                                
      servo1.write(position);  // Move to next position
      lcd.clear(); //Clear the LCD
      lcd.print(servo1.read()); //Display to LCD
      Serial.println(servo1.read()); //Display to serial display
      delay(servoDelay); // Short pause between steps, uses global variable 'servoDelay'
    }
  }
}

