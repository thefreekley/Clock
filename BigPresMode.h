
void pump(byte matrix){
   
byte   arr[7][8]{
  {B10101000,B11111000,B10001000,B10001000,B10001000,B10001000,B10001000,B10001000},
  {B10101000,B10101000,B11111000,B10001000,B10001000,B10001000,B10001000,B10001000},
  {B10101000,B10101000,B10101000,B11111000,B10001000,B10001000,B10001000,B10001000},
  {B10101000,B10101000,B10101000,B10101000,B11111000,B10001000,B10001000,B10001000},
  {B10101000,B10101000,B10101000,B10101000,B10101000,B11111000,B10001000,B10001000},
  {B10101000,B10101000,B10101000,B10101000,B10101000,B10101000,B11111000,B10001000},
  {B10101000,B10101000,B10101000,B10101000,B10101000,B10101000,B10101000,B11111000},
  };
  static unsigned long millis_pump=0;
  static byte phase=0;
  static byte high;
  if(millis()-millis_pump>100){
    
     int angle = map(delta, -250, 250, 0, 7);  
    angle = constrain(angle, 0, 7);  
    
    if(phase>13)phase=0;
    else if(phase<7){
      if(phase==6){
        if(high<angle+1)high++;
      else {
        high=0;
        for(int i=0; i<7;i++){
    lc.setLed(matrix,i,7,0);
    delay(20);
    }
      }
      }
      for(int i=0;i<8;i++){
        lc.setRow(matrix,i,arr[phase][i]>>1);
      }
      phase++;
    }
    else if(phase>=7){
       for(int i=0;i<8;i++){
        lc.setRow(matrix,i,arr[13-phase][i]>>1);
      }
      phase++;
    }
    millis_pump=millis();
  }
     for(int i=0; i<high;i++){
    lc.setLed(matrix,7-i,7,1);
    }
}

void BigPresMode(){
  

    
  pump(0);
static unsigned long millis_pres=10001;
       float temp(NAN), hum(NAN), pres(NAN);
   BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
   BME280::PresUnit presUnit(BME280::PresUnit_Pa);
   bme.read(pres, temp, hum, tempUnit, presUnit);
   if(millis()-millis_pres>10000){
boolean bag_deleter[10][6]{
  //{1.2.3.4.5.6}
    {1,1,1,1,1,1},
    {0,0,0,0,0,0},
    {1,0,1,1,1,1},
    {1,0,1,0,0,1},
    {1,1,1,1,0,0},
    {1,1,1,0,0,1},
    {1,1,1,1,1,1},
    {1,0,0,0,0,0},
    {1,1,1,1,1,1},
    {1,1,1,0,0,1},
   };
float   press_rt_stovp=pres/133.3224;
   int bag_deleter_helper=int(pres)- 100*(int(pres/100));
      SmallDepiction(int(pres/10000),7,-1);
   SmallDepiction(int(pres/100)- 100*(int(pres/10000)),6,-1);
   SmallDepiction(bag_deleter_helper,5,-1);
   SmallDepiction(100*(pres-int(pres)),4,1);
   lc.setLed(5,6,7,1);

  // Serial.println(press_rt_stovp);
   SmallDepiction(int(press_rt_stovp/100)*10+1,3,3);
   SmallDepiction(int(press_rt_stovp)-int(press_rt_stovp/100)*100,2,-1);
   SmallDepiction(press_rt_stovp*100-int(press_rt_stovp)*100,1,1);
   lc.setLed(2,6,7,1);
   for(int i=1;i<7;i++){
   lc.setLed(3,i,7,bag_deleter[int((int(press_rt_stovp)-int(press_rt_stovp/100)*10)/100)][i-1]);
   lc.setLed(6,i,7,bag_deleter[int(bag_deleter_helper/10)][i-1]);
   lc.setLed(7,i,7,bag_deleter[int((int(pres/100)- 100*(int(pres/10000)))/10)][i-1]);
   }
   millis_pres=millis();
   }
}
