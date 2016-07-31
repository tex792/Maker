/*
 * This is a simple sketch to practice displaying information to the LCD
 */


#include <LiquidCrystal.h>  //LCD library
LiquidCrystal lcd(12,11,5,4,3,2); // Initialize the LCD library with the pins we're using

void setup()
{

  lcd.begin(16,2); //Specify th dimension of the LCD (width, height)
  lcd.clear(); //Clear the LCD
  lcd.setCursor(0, 0); //Set the LCD cursor at the initial position

  Serial.begin(9600); //Initialize the port and set the baud rate (communication speed)

}

void loop()
{
  int var1 = 1;
  int var2 = 2;
  lcd.print(var1);
  lcd.print(" to ");
  lcd.print(var2);
  lcd.setCursor(0,1);
  lcd.print("My name is LCD");
  Serial.print(var1);
  Serial.println(" donut");
  //lcd.setCursor(0, 1); //Set the LCD cursor at the 1st column, 2nd row
  //lcd.print("My name is LCD");
  
  while(!Serial.available()) //This empty loop is holding the sketch still here. Serial.available() returns 'true' if data has been sent to
  {                          //the board through the serial monitor, which we haven't done. So we add the '!' to make the statement true
                             //and stay within the loop.
  }

}
