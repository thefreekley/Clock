void bad_weather(int matrix,int ping=50, boolean animation=1,boolean thunder=1);
void sun(int matrix,boolean animation=1);


 /*void sun(int matrix,boolean animation=1){

   byte arr[5][8]{
    {B00000000,B00000000,B00011000,B00111100,B00111100,B00011000,B00000000,B00000000},
    {B00000000,B00000000,B00111100,B00111100,B00111100,B00111100,B00000000,B00000000},
    {B00000000,B01000010,B00011000,B00111100,B00111100,B00011000,B01000010,B00000000},
    {B10000001,B00000000,B00011000,B00111100,B00111100,B00011000,B00000000,B10000001},
     {B00000000,B00000000,B00011000,B00111100,B00111100,B00011000,B00000000,B00000000},
   };
   static unsigned long millis_sun=0;
   static byte period_=0;
   //static byte stress=0;
   
   if(millis()-millis_sun>100){
    if(period_>=9)period_=0;
    else period_++;
    if(period_<5){
    for(int i=0;i<8;i++){
      if(animation==false && period_!=0)break;
     lc.setRow(matrix,i,arr[period_][i]);   
    }
    }
    millis_sun=millis();
   }
   
 } */

void sun(int matrix,boolean animation){
  for(int i=2;i<6;i++){
    lc.setLed(matrix,1,i,1);
    lc.setLed(matrix,2,i,1);
    lc.setLed(matrix,3,i,1);
    lc.setLed(matrix,4,i,1);
  }
  static unsigned long mil=0;
  static byte aa=0;
  if(animation){
  if(millis()-aa>100){
    if(aa>20)aa=0;
    else aa++;
    switch(aa){
      case 0:
      lc.setLed(matrix,5,1,1);
      lc.setLed(matrix,5,6,1);
      break;
      case 1:
      lc.setLed(matrix,6,0,1);
      lc.setLed(matrix,6,7,1);
      break;
      case 2:
      lc.setLed(matrix,5,1,0);
      lc.setLed(matrix,5,6,0);
      break;
      case 3:
      lc.setLed(matrix,6,0,0);
      lc.setLed(matrix,6,7,0);
      break;
    }
    mil=millis();
  }
  }
}
 void bad_weather(int matrix,int ping=50, boolean animation=1,boolean thunder=1){

   byte arr_sky[4]{B00111100,B01111110,B11111111,B11111111};
   
    for(int i=0;i<4;i++){
     lc.setRow(matrix,i,arr_sky[i]);   
    }
    if(animation){
      byte arr[8]{B10000000,B01000000,B00100000,B00010000,B00001000,B00000100,B00000010,B00000001};
   static unsigned long millis_bad=0;
   static byte period_=0;
   //static byte stress=0;
   static byte arrFall[4];
   static byte old_rand=0;
   static byte thunder_time=0;
   if(millis()-millis_bad>ping){

    arrFall[3]=arrFall[2];
    arrFall[2]=arrFall[1];
    arrFall[1]=arrFall[0];
    byte some_rand;
    while(1){
      some_rand=random(0, 7);
      if(some_rand!=old_rand && some_rand!=old_rand-1 && some_rand!=old_rand+1)break;
    }
   
   // Serial.println(String(old_rand)+"    "+String(some_rand));
    old_rand=some_rand;
    
    arrFall[0]=arr[some_rand];

    for(int i=4;i<8;i++){
      lc.setRow(matrix,i,arrFall[i-4]);
    }
    
    millis_bad=millis();
   }
    }
 }

void darkly(int matrix){
byte  EqualsArr[8]{B01110000,B11111000,B11111000,B00000000,B00001110,B00011111,B00011111,B00000000};
  

  static unsigned long EqualsMillis=0;
  static byte EqualsPhase=0;
  
  if(millis()-EqualsMillis>140){
    if(EqualsPhase>7)EqualsPhase=0;
    else EqualsPhase++;
    EqualsMillis=millis();
    for(int i=0;i<8;i++){lc.setRow(matrix,i,(EqualsArr[i]<<EqualsPhase)| (EqualsArr[i]>>8-EqualsPhase)) ;}
  }
  
}
void other_time(byte day_,byte mounth,byte weekday_){
   
  for(int i=0; i<int(day_/7);i++){
  for(byte j=0;j<7;j++){
    lc.setLed(3,i,j,1);
  }
  }
  for(byte j=0;j<day_%7;j++){
    lc.setLed(3,int(day_/7),j,1);
  } 

      for(int i=0; i<int(mounth/7);i++){
  for(byte j=0;j<7;j++){
    lc.setLed(3,7-i,j,1);
  }
  }
  for(byte j=0;j<mounth%7;j++){
    lc.setLed(3,7-int(mounth/7),j,1);
  } 

  if(weekday_==0)weekday_=7;
  
for(byte j=0;j<weekday_;j++){
    lc.setLed(3,5,j,1);
}
  
}

 /*if(period_>=5){
      period_=0;
      if(stress>=3)stress=0;
      else stress++;
    }
    else period_++;
    if(stress==0)lc.setLed(matrix,1,period_,0);
    else if(stress==1)lc.setLed(matrix,period_,6,0);
    else if(stress==2)lc.setLed(matrix,6,7-period_,0);
    else if(stress==3)lc.setLed(matrix,7-period_,1,0);
    millis_sun=millis();
   }
      if(stress==0)lc.setLed(matrix,1,period_+1,1);
    else if(stress==1)lc.setLed(matrix,period_+1,6,1);
    else if(stress==2)lc.setLed(matrix,6,6-period_,1);
    else if(stress==3)lc.setLed(matrix,6-period_,1,1);
    */



    void ComplexMode1(){
  
   
  int angle = map(delta, -250, 250, -2, 2);  
  switch (angle){
    case -2: bad_weather(7,50,1,0); break;
    case -1: bad_weather(7,100,1,0); break;
    case 0:darkly(7); break;
    case 1: sun(7,0); break;
    case 2: sun(7,1); break;
   } 
   
 
  int minutes1=(time.minutes-(int(time.minutes/10))*10);
    int minutes10=int(time.minutes/10);
    int Hours1=(time.Hours-(int(time.Hours/10))*10);
    int Hours10=int(time.Hours/10);
  time.gettime();

    
    static unsigned long time_for_change=0;
 static int throw_=0;
 static boolean flag_side=0;
 static byte show_concept=0;
 if(millis()-time_for_change>15+throw_*3){
  if(throw_<14)throw_+=1;
  else{
    throw_=0;
    flag_side=!flag_side;
    SmallDepiction(dht.readTemperature(),4,1);
    SmallDepiction(dht.readHumidity(),0,1);
    other_time(time.day,time.month,time.weekday);
    }
  
  
 if(flag_side==0){
  phaseOne(0,1,throw_);
  phaseTwo(7,2,throw_);
 }
 else{
  phaseOne(7,2,throw_);
  phaseTwo(0,1,throw_);
 }
 }
//bad_weather(7);
byte delaying=250;
   static unsigned long millis_for_clock=0;
   unsigned long deltaint=millis()- millis_for_clock;
  //Serial.println(deltaint);
  if(minutes1!=(time.minutes-(int(time.minutes/10))*10) ||deltaint>delaying){
    AnimationNumber(0,minutes1,1,6,20);
    AnimationNumber(1,time.minutes-(int(time.minutes/10))*10,1,6,20);
  }
  if(minutes10!=int(time.minutes/10) || deltaint>delaying){
    AnimationNumber(0,minutes10,1,2,20);
    AnimationNumber(1,int(time.minutes/10),1,2,20);
  }
  if(Hours1!=(time.Hours-(int(time.Hours/10))*10) ||deltaint>delaying){
        AnimationNumber(0,Hours1,2,5,20);
    AnimationNumber(1,time.Hours-(int(time.Hours/10))*10,2,5,20);
  }
  if(Hours10!=int(time.Hours/10) || deltaint>delaying){
       AnimationNumber(0,Hours10,2,1,20);
    AnimationNumber(1,int(time.Hours/10),2,1,20);
  }
  millis_for_clock=millis();
  
}
