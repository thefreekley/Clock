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
void SmallDepiction(int value,int matrix, int shift=0);
int hum_array[9];
int delta;
byte Modes;
unsigned long  pressure_array[6], time_array[6];

#include <EEPROM.h> 

#include <FHT.h> 

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
iarduino_RTC time(RTC_DS1307);  

#include "LedControlMS.h"
LedControl lc=LedControl(12,11,10,8);
#include "BigTemperatureMode.h"
#include "AnimationBumber.h"
//void AnimationNumber(boolean off,int number,int matrix,int row,int ping)
#include "BigHumidityMode.h"
#include "BigClockMode.h"
#include "BigPresMode.h"
#include "Bolds.h"
#include "ComplexMode.h"
//SmallNumber[10][6] BigNumber[10][2][8]
boolean change_shine;
byte your_shine;
//****************PROGRAM**********************************//


 //- для вичеслення середнього значення вологості

void setup(){
      Modes=EEPROM.read(0); 
  change_shine=EEPROM.read(1);
  your_shine=EEPROM.read(2);
  
  dht.begin();
  Serial.begin(9600);
  Wire.begin();
  bme.begin();
  time.begin(); 
  
  for(int i=0;i<9;i++){
  hum_array[i]=dht.readHumidity();
  if(i==8)break;
  lc.shutdown(i,false);
  if(change_shine==0)lc.setIntensity(i,8);
  else lc.setIntensity(i,your_shine);
  lc.clearDisplay(i);
  
  }
  intro();
    for(int i=0;i<8;i++){
  lc.clearDisplay(i);
  
  }
  pinMode(6,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  pinMode(5,OUTPUT);
  pinMode(A2,INPUT);
  pinMode(LED,OUTPUT);
  analogWrite(LED,250);
   randomSeed(analogRead(A6));

  float temp(NAN), hum(NAN), pres(NAN);
   BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
   BME280::PresUnit presUnit(BME280::PresUnit_Pa);
   bme.read(pres, temp, hum, tempUnit, presUnit);
   
 for (byte i = 0; i < 6; i++) {   // счётчик от 0 до 5
    pressure_array[i] = pres;  // забить весь массив текущим давлением
    time_array[i] = i;             // забить массив времени числами 0 - 5
  }

}


void loop(){
  static boolean flag_zopka=0;
  
  BUTTON_UP.tick();
  BUTTON_DOWN.tick();
  
  if(BUTTON_UP.isDouble())flag_zopka=!flag_zopka;
  
  if(BUTTON_DOWN.isDouble()){
    change_shine=!change_shine;
    EEPROM.write(1,change_shine); 
  }
   
 
  if(BUTTON_UP.isSingle()){
  flag_zopka=0;
    if(Modes>=4)Modes=0;
    else Modes++;
    EEPROM.write(0,Modes); 
    for(int i=0;i<8;i++){lc.clearDisplay(i);}
  }
  
  if(BUTTON_DOWN.isSingle()){
    flag_zopka=0;
    if(Modes<=0)Modes=1;
    else Modes--;
    EEPROM.write(0,Modes);
    for(int i=0;i<8;i++){lc.clearDisplay(i);}
  }
  //Serial.println(flag_zopka);
if(flag_zopka==0){   
  switch(Modes){
    case 0: BigClockMode(); break;
    case 1: BigTemperatureMode(); break;
    case 2: BigHumidityMode(); break;
    case 3: BigPresMode(); break;
    case 4: ComplexMode1(); break;
  }
  }
  else{
    puzik();
  }
  
  GetWeather();
  
  if(change_shine==0){
    Shine();
    analogWrite(LED,250);
  }
  else{
    analogWrite(LED,0);
   if(BUTTON_UP.isHold()){
    if(your_shine>=15)your_shine=0;
    else your_shine++;
    EEPROM.write(2,your_shine);
    delay(200);
     for(int i=0;i<8;i++){
  lc.setIntensity(i,your_shine); 
  }  
   }
   if(BUTTON_DOWN.isHold()){
    if(your_shine<=0)your_shine=15;
    else your_shine--;
    EEPROM.write(2,your_shine);
    delay(200);
      for(int i=0;i<8;i++){
  lc.setIntensity(i,your_shine); 
  }
   }
   Serial.println(your_shine);
  }
 //  BigClockMode();
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
  return intensity;
}


void puzik(){
byte n[1][9][9]={
{
{B00100000,B00100000,B00100000,B11100000,B00100000,B00100000,B00100000,B00000000},
{B10010001,B10010001,B10010001,B10010001,B01110001,B00010001,B11100001,B00000000},
{B00111100,B00100100,B00100100,B00100100,B00111100,B00100100,B00100100,B00000000},
{B00011110,B00010010,B00010010,B00010010,B00111111,B00100001,B00100001,B00000000},
{B01110100,B00010100,B00010100,B01111100,B01010000,B01010000,B01011100,B00000000},
{B00100001,B00100001,B00100011,B00100101,B00101001,B00110001,B00100001,B00000000},
{B00111110,B00001000,B00001000,B00001000,B00001000,B00001000,B00001000,B00000000},
{B01111001,B00001001,B00001001,B01111111,B01001000,B01001000,B01001111,B00000000}
}
};
static unsigned long suka=0;
if(millis()-suka>4000){
for(int i=0;i<8;i++){
for(int g=0;g<8;g++){
lc.setRow(i,g,n[0][i][g]);
}
}
suka=millis();
}


}

void intro(){
byte n[9][9]={
{B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111},
{B00010001,B00001001,B00000011,B00000111,B11011111,B11111111,B11111111,B11111111},
{B01010000,B01010000,B01010000,B01110000,B00000000,B01111111,B11111111,B11111111},
{B01010001,B01010111,B01010100,B01110111,B00000000,B00000011,B00011111,B11111111},
{B11111000,B11111100,B11111100,B11111100,B11111110,B11111110,B11111111,B11111111},
{B00011111,B00111111,B10011001,B00110000,B00110000,B01000100,B00001000,B10000001},
{B00000000,B01010000,B01110000,B01100000,B01010000,B01010001,B00000000,B01110000},
{B00000000,B01110111,B00100100,B00100111,B00100100,B00100100,B00000000,B01110111}
};
for(int i=0;i<8;i++){
for(int g=0;g<8;g++){
lc.setRow(i,g,n[i][g]);
}
}
delay(4000);

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
void SmallDepiction(int value,int matrix, int shift=0){
    int tenthPart=int(value/10);
    int singlePart=value-(int(value/10))*10;
    for(int i=0;i<6;i++){
      byte siftSinglePart=SmallNumber[singlePart][i]>>4;
      byte example=SmallNumber[tenthPart][i]|siftSinglePart;
      if(shift>0)lc.setRow(matrix,i+1,example>>shift);
      else lc.setRow(matrix,i+1,example<<abs(shift));
    }
    
}
byte reflectByte(byte x){
     x = (x & 0x55) << 1 | (x & 0xAA) >> 1;
   x = (x & 0x33) << 2 | (x & 0xCC) >> 2;
   x = (x & 0x0F) << 4 | (x & 0xF0) >> 4;
   return x;
}



 void GetWeather(){
  
static unsigned long WheatherTimer=0;
static unsigned long pressure;
static unsigned long sumX, sumY, sumX2, sumXY;
static float a, b;

if(millis()-WheatherTimer>6000000){
      delay(200);
        float temp(NAN), hum(NAN), pres(NAN);
   BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
   BME280::PresUnit presUnit(BME280::PresUnit_Pa);
   bme.read(pres, temp, hum, tempUnit, presUnit); 
   
    pressure = pres;                          
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
    WheatherTimer=millis();

}               
}
