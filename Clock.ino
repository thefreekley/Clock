#define CS_SLED 10
#define DIN_SLED 11
#define CLK_SLED 12

#define PHOTORESISTOR A2

#define BUTTON_UP 4
#define BUTTON_DOWN 6

#define SDA_RTC 3
#define SCL_RTC 9

#define LED 5

#define DHTPIN 2

#define pin_SW_SDA 3                                    
#define pin_SW_SCL 9 

//**********************LIBRARARY***************************//

#include "DHT.h"
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

#include <BME280I2C.h>
#include <Wire.h>
BME280I2C bme;



#include <iarduino_RTC.h>                                  
iarduino_RTC time(RTC_DS3231);  

#include "LedControlMS.h"
LedControl lc=LedControl(12,11,10,8);

#include "AnimationBumber.h"
//void AnimationNumber(boolean off,int number,int matrix,int row,int ping)

#include "Bolds.h"
//SmallNumber[10][6] BigNumber[10][2][8]

//****************PROGRAM**********************************//




void setup(){
  dht.begin();
  Serial.begin(9600);
  Wire.begin();
  bme.begin();
  time.begin(); 
  
  for(int i=0;i<8;i++){
  lc.shutdown(i,false);
  lc.setIntensity(i,8);
  lc.clearDisplay(i);
  }
  
}


void loop(){
  int h = dht.readHumidity();
  int t = dht.readTemperature();


   float temp(NAN), hum(NAN), pres(NAN);
   BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
   BME280::PresUnit presUnit(BME280::PresUnit_Pa);
   bme.read(pres, temp, hum, tempUnit, presUnit);
   AnimationNumber(1,2,1,1,50);
   AnimationNumber(1,0,1,5,50);
   AnimationNumber(1,2,0,1,50);
   AnimationNumber(1,0,0,5,50);
    delay(6000);
     AnimationNumber(0,2,1,1,50);
   AnimationNumber(0,0,1,5,50);
   AnimationNumber(0,2,0,1,50);
   AnimationNumber(0,0,0,5,50);
    /*
  time.Hours
  time.minutes
  time.seconds
  time.day
  time.weekday
  time.month
  time.year
    */
    
}

 
