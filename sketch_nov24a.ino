/*Keypad example
    by miliohm.com */

#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

char data;
String pad;
char keypressed;
const byte numRows = 4;
const byte numCols = 4;

char keymap[numRows][numCols] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
//------------------------------------------------------------
byte rowPins[numRows] = {2,3,5,4};
byte colPins[numCols] = {6,7,8,10};

Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols); //mapping keypad

void setup() 
{
  Serial.begin(9600); //Permet d'initialiser le moniteur série à 9600 bauds 
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Keypad");
  lcd.setCursor(0, 1);
  lcd.print("Test");
  delay(1000);
  lcd.clear();
}

void loop() 
{
  readKeypad();
  lcd.setCursor(0, 0);
  lcd.print(pad);
  
  if (keypressed == '#') 
  {
    if (pad.length() > 0) 
    {
      Serial.print(pad);
      pad = ""; // Clear the pad after sending the password
    }
  }

  if (keypressed == '*') 
  {
    pad = "";
    lcd.clear();
  }
  if (Serial.available() > 0)  // Vérifie si des données sont disponibles dans le tampon de réception série
  {
    char receivedChar = Serial.read();  // Lit un caractère du tampon de réception série
    
    if(receivedChar == '1')
    {
      pad = "";
      lcd.clear();
      lcd.print("Taxi On the Way");
    }
    else if(receivedChar == '0')
    {
      pad = "";
      lcd.clear();
      lcd.print("Need to Sign Up");
    }
  }
  delay(100);
}

void readKeypad() {
  keypressed = myKeypad.getKey(); //deteksi penekanan keypad
  if (keypressed != '#') 
  {
    String konv = String(keypressed);
    pad += konv;
  }
}
