void MidleCircleDepiction(int phase,int matrix, boolean off){
  lc.setLed(matrix,3,3,1);
  lc.setLed(matrix,3,4,1);
  lc.setLed(matrix,4,3,1);
  lc.setLed(matrix,4,4,1);
  switch(phase){
    case 0: lc.setLed(matrix,1,2,off); break;
    case 1: lc.setLed(matrix,1,3,off); break;
    case 2: lc.setLed(matrix,1,4,off); break;
    case 3: lc.setLed(matrix,1,5,off); break;
    case 4: lc.setLed(matrix,2,6,off); break;
    case 5: lc.setLed(matrix,3,6,off); break;
    case 6: lc.setLed(matrix,4,6,off); break;
    case 7: lc.setLed(matrix,5,6,off); break;
    case 8: lc.setLed(matrix,6,5,off); break;
    case 9: lc.setLed(matrix,6,4,off); break;
    case 10: lc.setLed(matrix,6,3,off); break;
    case 11: lc.setLed(matrix,6,2,off); break;
    case 12: lc.setLed(matrix,5,1,off); break;
    case 13: lc.setLed(matrix,4,1,off); break;
    case 14: lc.setLed(matrix,3,1,off); break;
    case 15: lc.setLed(matrix,2,1,off); break;

  }
}
void BigCircleDepiction(int phase,int matrix, boolean off){
    switch(phase){
    case 0: lc.setLed(matrix,0,2,off); break;
    case 1: lc.setLed(matrix,0,3,off); break;
    case 2: lc.setLed(matrix,0,4,off); break;
    case 3: lc.setLed(matrix,0,5,off); break;
    case 4: lc.setLed(matrix,1,6,off); break;
    case 5: lc.setLed(matrix,2,7,off); break;
    case 6: lc.setLed(matrix,3,7,off); break;
    case 7: lc.setLed(matrix,4,7,off); break;
    case 8: lc.setLed(matrix,5,7,off); break;
    case 9: lc.setLed(matrix,6,6,off); break;
    case 10: lc.setLed(matrix,7,5,off); break;
    case 11: lc.setLed(matrix,7,4,off); break;
    case 12: lc.setLed(matrix,7,3,off); break;
    case 13: lc.setLed(matrix,7,2,off); break;
    case 14: lc.setLed(matrix,6,1,off); break;
    case 15: lc.setLed(matrix,5,0,off); break;
    case 16: lc.setLed(matrix,4,0,off); break;
    case 17: lc.setLed(matrix,3,0,off); break;
    case 18: lc.setLed(matrix,2,0,off); break;
    case 19: lc.setLed(matrix,1,1,off); break;
    }
    
}

void BigTemperatureMode(){

  static unsigned long time_for_change0=0;
  static unsigned int phase_time=0;
  if(millis()-time_for_change0>40){
    if(phase_time>15)phase_time=0;
    else phase_time++;
    
     MidleCircleDepiction(phase_time,4,1);
    if(phase_time==0) MidleCircleDepiction(15,4,0);
    else  MidleCircleDepiction(phase_time-2,4,0);    
    time_for_change0=millis();
  }

  static unsigned long time_for_change1=0;
  static unsigned int phase_time1=0;
  if(millis()-time_for_change1>50){
    if(phase_time1>19)phase_time1=0;
    else phase_time1++;
    
    BigCircleDepiction(phase_time1,4,1);
    if(phase_time1==0)BigCircleDepiction(19,4,0);
    else BigCircleDepiction(phase_time1-2,4,0);    
    time_for_change1=millis();
  }
  
 static unsigned long time_for_change=0;
   if(millis()-time_for_change>4000){
    float temp(NAN), hum(NAN), pres(NAN);
   BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
   BME280::PresUnit presUnit(BME280::PresUnit_Pa);
   bme.read(pres, temp, hum, tempUnit, presUnit);
   temp=temp-3;
   if(temp>0)depiction(10,3,0);
   else depiction(11,3,0);
   depiction(int(temp/10),2,0);
   depiction(int(temp-int(temp/10)*10),1,0);
  // Serial.println(String(temp)+"  "+String(t));
   SmallDepiction(int(100*(temp-int(temp))),0);
   time_for_change=millis();
   }
}
