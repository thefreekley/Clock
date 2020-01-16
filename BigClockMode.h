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
void BigClockMode(){
   // static boolean flag_privet=0;
   static unsigned long millis_for_clock=0;
    byte firstCheck=time.minutes;
    time.gettime();
    
    if(millis()-millis_for_clock>100 || firstCheck!=time.minutes){
       depiction((time.minutes-(int(time.minutes/10))*10),0,1);
    depiction(int(time.minutes/10),1,1);
    depiction((time.Hours-(int(time.Hours/10))*10),2,-1);
    depiction(int(time.Hours/10),3,-1);
    }
//Serial.println(millis()-millis_for_clock);
    
    static unsigned long time_for_change=0;
 static int throw_=0;
 static boolean flag_side=0;
 
 if(millis()-time_for_change>15+throw_*3){
  if(throw_<14)throw_+=1;
  else{
    throw_=0;
    flag_side=!flag_side;
    }
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
  millis_for_clock=millis();
}
