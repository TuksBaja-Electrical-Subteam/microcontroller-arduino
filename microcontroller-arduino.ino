#include <LCD-I2C.h>
#include <Wire.h>
LCD_I2C lcd(0x27, 16, 2);
int sensorRead;
int lim = 409;
int count = 0;

void setup() 
{
  Serial.begin(9600);
  pinMode(A0, INPUT);
  Wire.begin();
  lcd.begin(&Wire);
  lcd.display();
  lcd.backlight();
}

void loop() 
{

  sensorRead = analogRead(A0);
  if(sensorRead < 409)
  {
    count = count + 1;
    lcd.print(count);
    Serial.print(" ");
    Serial.print(count);
  }
  delay(160);
}

