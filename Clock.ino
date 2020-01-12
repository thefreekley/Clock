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
  BUTTON_UP.tick();
  BUTTON_DOWN.tick();  
  if(BUTTON_UP.isSingle())Serial.println("UP");
  if(BUTTON_DOWN.isSingle())Serial.println("DOWN");
  Shine();
   BigTemperatureMode();



 
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

void phaseOne(int row,int MatrixNumber,int throw_){
  
  if(throw_<8){
    lc.setLed(MatrixNumber,7,row,LOW);
    lc.setLed(MatrixNumber+4,throw_,row,HIGH);
    if(throw_!=0)lc.setLed(MatrixNumber+4,throw_-1,row,LOW);
  }
  else{
    lc.setLed(MatrixNumber+4,7,row,LOW);
    lc.setLed(MatrixNumber,throw_-7,row,HIGH);
    if(throw_!=0)lc.setLed(MatrixNumber,throw_-7-1,row,LOW);
    
  }
}
void phaseTwo(int row,int MatrixNumber,int throw_){
  
  if(throw_<8){
    lc.setLed(MatrixNumber+4,0,row,LOW);
    lc.setLed(MatrixNumber,7-throw_,row,HIGH);
    if(throw_!=0)lc.setLed(MatrixNumber,7-throw_+1,row,LOW);
    
  }
  else{
    lc.setLed(MatrixNumber,0,row,LOW);
    lc.setLed(MatrixNumber+4,14-throw_,row,HIGH);
    if(throw_!=0)lc.setLed(MatrixNumber+4,14-throw_+1,row,LOW);
    
  }
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
   Serial.println(g);
   for(int i=0;i<8;i++){
  lc.setIntensity(i,g);
  }
  
  delay(50);
  }
  }
  else{
  for(int g=old_intensity;g<=intensity;g++){
   Serial.println(g);
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

byte reflectByte(byte x){
     x = (x & 0x55) << 1 | (x & 0xAA) >> 1;
   x = (x & 0x33) << 2 | (x & 0xCC) >> 2;
   x = (x & 0x0F) << 4 | (x & 0xF0) >> 4;
   return x;
}
void BigClockMod(){
    static boolean flag_privet=0;
    byte firstCheck=time.minutes;
    time.gettime();
    
    if(time.minutes!=firstCheck || flag_privet==0){
      // це треба виправить з мілліс ато костиль максимальний
    flag_privet=1;
    depiction((time.minutes-(int(time.minutes/10))*10),0,1);
    depiction(int(time.minutes/10),1,1);
    depiction((time.Hours-(int(time.Hours/10))*10),2,-1);
    depiction(int(time.Hours/10),3,-1);
    }
    static unsigned long time_for_change=0;
 static int throw_=0;
 static boolean flag_side=0;
 if(millis()-time_for_change>80){
  if(throw_<14)throw_+=1;
  else{ throw_=0; flag_side=!flag_side;}
  time_for_change=millis();
  
 if(flag_side==0){
  phaseOne(0,1,throw_);
  phaseTwo(7,2,throw_);
 }
 else{
  phaseOne(7,2,throw_);
  phaseTwo(0,1,throw_);
 }
 }
 

 
    /* lc.setLed(1,3,1,1);
    lc.setLed(1,4,1,1);
     lc.setLed(2,3,7,1);
    lc.setLed(2,4,7,1);
    lc.setLed(5,3,1,1);
    lc.setLed(5,4,1,1);
     lc.setLed(6,3,7,1);
    lc.setLed(6,4,7,1); */
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
void BigTemperatureMode(){

  byte animation[7][8]{
    {B00000000,B00000000,B00000000,B00011000,B00011000,B00000000,B00000000,B00000000},
    {B00000000,B00000000,B00111100,B00100100,B00100100,B00111100,B00000000,B00000000},
    {B00000000,B01111110,B01000010,B01000010,B01000010,B01000010,B01111110,B00000000},
    {B00000000,B00111100,B01100110,B01000010,B01000010,B01100110,B00111100,B00000000},
    {B00000000,B00000000,B00100100,B00011000,B00011000,B00100100,B00000000,B00000000},
    {B00000000,B00000000,B00011000,B00100100,B00100100,B00011000,B00000000,B00000000},
    {B00000000,B00000000,B00000000,B00011000,B00011000,B00000000,B00000000,B00000000},
  };
  static unsigned long time_for_change0=0;
  static unsigned int phase_time=0;
  if(millis()-time_for_change0>100){
    if(phase_time>5)phase_time=0;
    else phase_time++;
    if(phase_time==0)delay(500);
    for(int i=0;i<8;i++){
      lc.setRow(4,i,animation[phase_time][i]);
    }
    time_for_change0=millis();
  }
 static unsigned long time_for_change=0;
   if(millis()-time_for_change>1000){
    float temp(NAN), hum(NAN), pres(NAN);
   BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
   BME280::PresUnit presUnit(BME280::PresUnit_Pa);
   bme.read(pres, temp, hum, tempUnit, presUnit);
   
   if(temp>0)depiction(10,3,0);
   else depiction(11,3,0);
   depiction(int(temp/10),2,0);
   depiction(int(temp-int(temp/10)*10),1,0);
  // Serial.println(String(temp)+"  "+String(t));
   SmallDepiction(int(100*(temp-int(temp))),0);
   time_for_change=millis();
   }
}

void Information(){
  int h = dht.readHumidity();
  int t = dht.readTemperature();


   float temp(NAN), hum(NAN), pres(NAN);
   BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
   BME280::PresUnit presUnit(BME280::PresUnit_Pa);
   bme.read(pres, temp, hum, tempUnit, presUnit);

   Serial.print(h);
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

 
