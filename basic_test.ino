/* Photo Interrupter Module LM393 Comparator (FC-03) [S158] : http://rdiot.tistory.com/96 [RDIoT Demo] */

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
 
LiquidCrystal_I2C lcd(0x27,20,4);  

#define encdpin               2

volatile int count, countold;
unsigned long ignoremilli = 10;  
unsigned long oldtime = 0;
unsigned long time = 0;

void setup()
{
  
  lcd.init();                    
  
  lcd.backlight();
  
  count = 0;
  countold = 0; 
  oldtime = millis();
  
  pinMode(encdpin, INPUT);
  pinMode(13, OUTPUT); 
  attachInterrupt(digitalPinToInterrupt(encdpin), sensor1, FALLING);

  Serial.begin(9600); 
  Serial.println("start");
}

void loop()
{
  lcd.setCursor(0,0);
  lcd.print("S158:Photo Interr.");

  
  if (countold != count)
  {
    Serial.println(count);
    lcd.setCursor(0,1);
    lcd.print("CNT : "+(String)count+" ");
       countold = count;

  }
}

void sensor1()
{
  time = millis();
  
  if( (time - oldtime) > ignoremilli ) {
   count++; 
  }
  oldtime = millis();
  
}
