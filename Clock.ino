#define CS_SLED 10
#define DIN_SLED 11
#define CLK_SLED 12

#define PHOTORESISTOR A2

#define BUTTON_UP_PIN 6
#define BUTTON_DOWN_PIN 4

#define SDA_RTC 3
#define SCL_RTC 9

#define LED 5

#define DHTPIN 2

#define pin_SW_SDA 3                                    
#define pin_SW_SCL 9 

//**********************LIBRARARY***************************//
void depiction(int index, int matrix, int shift);
void SmallDepiction(int value,int matrix);
//
#include "DHT.h"
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

#include <BME280I2C.h>
#include <Wire.h>
BME280I2C bme;

#include "GyverButton.h"
GButton BUTTON_UP(BUTTON_UP_PIN);
GButton BUTTON_DOWN(BUTTON_DOWN_PIN);

#include <iarduino_RTC.h>                                  
iarduino_RTC time(RTC_DS3231);  

#include "LedControlMS.h"
LedControl lc=LedControl(12,11,10,8);

#include "AnimationBumber.h"
//void AnimationNumber(boolean off,int number,int matrix,int row,int ping)
#include "BigTemperatureMode.h"
#include "BigClockMode.h"
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
  pinMode(6,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  pinMode(5,OUTPUT);
  pinMode(A2,INPUT);
  pinMode(LED,OUTPUT);
  analogWrite(LED,250);
}


void loop(){
  /*
  BUTTON_UP.tick();
  BUTTON_DOWN.tick();
  static byte Modes;  
  if(BUTTON_UP.isSingle()){
    if(Modes>=1)Modes=0;
    else Modes++;
    for(int i=0;i<8;i++){lc.clearDisplay(i);}
  }
  
  if(BUTTON_DOWN.isSingle()){
    if(Modes<0)Modes=1;
    else Modes--;
    for(int i=0;i<8;i++){lc.clearDisplay(i);}
  }

  switch(Modes){
    case 0: BigClockMode(); break;
    case 1: BigTemperatureMode(); break;
  }
  */
  GetWeather();
  Shine();
  
 // Serial.println(digitalRead(BUTTON_UP_PIN));


 
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


int Shine(){
  static byte old_intensity=0;
  static byte intensity=8;
  static long flag1=0;
  
  old_intensity=intensity;
  
  if(millis()-flag1>5000){
  
  intensity= map(analogRead(PHOTORESISTOR),20,800,0,13);
  
  
  //Serial.println(intensity);
  if(old_intensity>=intensity){
  for(int g=old_intensity;g>=intensity;g--){
  // Serial.println(g);
   for(int i=0;i<8;i++){
  lc.setIntensity(i,g);
  }
  
  delay(50);
  }
  }
  else{
  for(int g=old_intensity;g<=intensity;g++){
  // Serial.println(g);
   for(int i=0;i<8;i++){
  lc.setIntensity(i,g);
  }
  
  delay(50);
  }
  }
  
  flag1=millis();
  }
}
void depiction(int index, int matrix, int shift){
 
  
 byte example;
 static byte points=B00000001;
 
 for(int g=0;g<2;g++){
  for(int i=0;i<8;i++){
    if(shift>0)example=BigNumber[index][g][i]>>shift;
    else example=BigNumber[index][g][i]<<abs(shift);
    
    //if((matrix==2 || matrix==6) && (i==3 || i==4))example=example|points;
    
    //if((matrix==1 || matrix==5) && (i==4 || i==3))example=example|reflectByte(points);

    
    lc.setRow(matrix+g*4,i,example);
    
  }
  }
  
}
void SmallDepiction(int value,int matrix){
    int tenthPart=int(value/10);
    int singlePart=value-(int(value/10))*10;
    for(int i=0;i<6;i++){
      byte siftSinglePart=SmallNumber[singlePart][i]>>4;
      byte example=SmallNumber[tenthPart][i]|siftSinglePart;
      lc.setRow(matrix,i+1,example);
    }
    
}
byte reflectByte(byte x){
     x = (x & 0x55) << 1 | (x & 0xAA) >> 1;
   x = (x & 0x33) << 2 | (x & 0xCC) >> 2;
   x = (x & 0x0F) << 4 | (x & 0xF0) >> 4;
   return x;
}


void BigHumidityMode(){
    
   
//  float int = dht.readHumidity();
 // Serial.println(int();
}



static int angle, delta;
static unsigned long pressure, aver_pressure, pressure_array[6], time_array[6];
static unsigned long sumX, sumY, sumX2, sumXY;
static float a, b;

 int GetWeather(){
static unsigned long WheatherTimer=0;
if(millis()-WheatherTimer>60000){
      delay(200);
    pressure = aver_sens();                          
    for (byte i = 0; i < 5; i++) {                  
      pressure_array[i] = pressure_array[i + 1];     
    }
    pressure_array[5] = pressure;                   

    sumX = 0;
    sumY = 0;
    sumX2 = 0;
    sumXY = 0;
    for (int i = 0; i < 6; i++) {                  
      sumX += time_array[i];
      sumY += (long)pressure_array[i];
      sumX2 += time_array[i] * time_array[i];
      sumXY += (long)time_array[i] * pressure_array[i];
    }
    a = 0;
    a = (long)6 * sumXY;  
    a = a - (long)sumX * sumY;
    a = (float)a / (6 * sumX2 - sumX * sumX);
    delta = a * 6;                   
    angle = map(delta, -250, 250, 0, 100);
    angle = constrain(angle, 0, 100);  
    Serial.println(angle);
    WheatherTimer=millis();
    return angle;
}               
}


long aver_sens() {
   float temp(NAN), hum(NAN), pres(NAN);
   BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
   BME280::PresUnit presUnit(BME280::PresUnit_Pa);
   bme.read(pres, temp, hum, tempUnit, presUnit);

  pressure = 0;
  for (byte i = 0; i < 10; i++) {
    pressure += pres;
  }
  aver_pressure = pressure / 10;
  return aver_pressure;
}

void Information(){
  
  int t = dht.readTemperature();


   float temp(NAN), hum(NAN), pres(NAN);
   BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
   BME280::PresUnit presUnit(BME280::PresUnit_Pa);
   bme.read(pres, temp, hum, tempUnit, presUnit);

//   Serial.print(h);
   Serial.print(" -hum DHT ");
   Serial.print(t);
   Serial.print ("-  temp DHT ");
   Serial.print(pres);
   Serial.print(" -pres BME280 ");
   Serial.print(temp);
   Serial.print(" -temp BME280 ");
   Serial.print(analogRead(A2));
   Serial.print(" - shine ");
   Serial.print(digitalRead(6));
   Serial.print(" ");
   Serial.print(digitalRead(4));
   Serial.print(" ");
    Serial.print(time.seconds);
   Serial.println(" -seconds ");
 
}

 
