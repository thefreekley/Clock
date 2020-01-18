/*smiles[5][8]{
  {
    {B00000000,B00000000,B01110111,B01000100,B00000000,B00111000,B00101000,B00000000},
    {B00000000,B00000000,B01110111,B00100010,B00000000,B00011100,B00010100,B00000000},
    {B00000000,B00000000,B01110111,B00010001,B00000000,B00001110,B00001010,B00000000},
  },
  {

  {
    {B01100110,B01100110,B01100110,B00000000,B00000000,B00000000,B00111100,B01000010},
    {B10000001,B01000010,B00100100,B00011000,B00011000,B00100100,B01000010,B10000001},
    {B11100111,B01000010,B01000010,B00000000,B00000000,B00000000,B00111100,B01000010},
  }
}*/


void GoodSmile(int matrix){
byte  ArrGoodSmile[7][8]{
   {B00010000,B01010000,B00110000,B01011100,B00110100,B00011100,B00011000,B00011000}, //ok
  {B00000000,B01111100,B01000000,B01000000,B01111100,B01000100,B01000100,B01111100}, //baldej
  {B00000000,B01111100,B01000100,B01000100,B01111100,B01000100,B01000100,B01000100},
  {B00000000,B00111000,B01000100,B01000100,B01000100,B01000100,B01000100,B01000100},
  {B00000000,B00111000,B00101000,B00101000,B00101000,B00101000,B01111100,B01000100},
  {B00000000,B01111100,B01000000,B01000000,B01111100,B01000000,B01000000,B01111100},
  {B00000000,B01010100,B01010100,B00111000,B00010000,B00111000,B01010100,B01010100},
  };
  
  static unsigned long GoodSmileMillis=0;
  static int GoodSmilePeriod=0;

  if(GoodSmilePeriod<8){
    for(int i=(7-GoodSmilePeriod);i<8;i++){lc.setRow(matrix,i,ArrGoodSmile[0][abs(7-i-GoodSmilePeriod)]);}
  }
  
   else if(GoodSmilePeriod>46 && GoodSmilePeriod<47+8){
    lc.setRow(matrix,abs(47-GoodSmilePeriod),B00000000);
    for(int i=abs(46-GoodSmilePeriod);i<8;i++){lc.setRow(matrix,i,ArrGoodSmile[0][i-abs(46-GoodSmilePeriod)]);}
  }
   else if(GoodSmilePeriod>90+10 && GoodSmilePeriod<10+91+8){
      
    lc.setRow(matrix,abs(91+10-GoodSmilePeriod),B00000000);
    for(int i=abs(90+10-GoodSmilePeriod);i<8;i++){lc.setRow(matrix,i,ArrGoodSmile[6][i-abs(90+10-GoodSmilePeriod)]);}
  }
  else if(GoodSmilePeriod>55 && GoodSmilePeriod<55+8){
     for(int i=(55+7-GoodSmilePeriod);i<8;i++){lc.setRow(matrix,i,ArrGoodSmile[1][abs(55+7-i-GoodSmilePeriod)]);}
  }
  switch(GoodSmilePeriod){
  //case 63: for(int i=0;i<8;i++){lc.setRow(matrix,i,ArrGoodSmile[1][i]);} break;
  case 75: for(int i=0;i<8;i++){lc.setRow(matrix,i,ArrGoodSmile[2][i]);} break;
  case 80: for(int i=0;i<8;i++){lc.setRow(matrix,i,ArrGoodSmile[3][i]);} break;
  case 85: for(int i=0;i<8;i++){lc.setRow(matrix,i,ArrGoodSmile[4][i]);} break;
  case 90: for(int i=0;i<8;i++){lc.setRow(matrix,i,ArrGoodSmile[5][i]);} break;
  case 95: for(int i=0;i<8;i++){lc.setRow(matrix,i,ArrGoodSmile[6][i]);} break;
  
  } 
    if(millis()-GoodSmileMillis>100){
    if(GoodSmilePeriod>120)GoodSmilePeriod=0;
    else GoodSmilePeriod++;
   GoodSmileMillis=millis();
  }
}

void RestlessSmile(int matrix){
byte  RestlessSmileArr[3][8]{
    {B00000000,B00000000,B01110111,B01000100,B00000000,B00111000,B00101000,B00000000},
    {B00000000,B00000000,B01110111,B00100010,B00000000,B00011100,B00010100,B00000000},
    {B00000000,B00000000,B01110111,B00010001,B00000000,B00001110,B00001010,B00000000},
  };
  
  static unsigned long RestlessSmileMillis=0;
  static byte RestlessSmilePhase=0;
  if(millis()-RestlessSmileMillis>4000){
    if(RestlessSmilePhase>1)RestlessSmilePhase=0;
    else RestlessSmilePhase++;
    RestlessSmileMillis=millis();
    for(int i=0;i<8;i++){lc.setRow(matrix,i,RestlessSmileArr[RestlessSmilePhase][i]);}
  }
  
}
void TeriblSmile(int matrix){
byte  TeriblSmileArr[3]{B00011000,B00111100,B01111110};
for(int i=5;i<8;i++){lc.setRow(matrix,i,TeriblSmileArr[abs(5-i)]);}
static unsigned long pp=0;
if(millis()-pp>10){
static byte last_value_column=0;
static byte last_value_row=0;
lc.setLed(matrix,last_value_column,last_value_row,0);
last_value_column=random(0, 7);
last_value_row=random(0, 7);

lc.setLed(matrix,last_value_column,last_value_row,1);
pp=millis();
}
}
void arrowUp(byte matrix,int speed=100){
  static unsigned long prekol=0;
  static int phase=0;
byte  arr[8]{B00001000,B00011100,B00001000,B00001000,B00001000,B00001000,B00001000,B00000000};
  if(millis()-prekol>speed){
    if(phase>13)phase=0;
    else phase++;
    byte interval=8;
    if(phase>11)interval=14-interval;
         for(int i=(7-phase);i<interval;i++){
          lc.setRow(matrix,i,arr[abs(7-i-phase)]);
          if(abs(7-i-phase)>7)break;
          }
    prekol=millis();
  

  }
}

void arrowDown(byte matrix,int speed=100){
  static unsigned long prekol=0;
  static int phase=0;
byte  arr[8]{B00001000,B00011100,B00001000,B00001000,B00001000,B00001000,B00001000,B00000000};
  if(millis()-prekol>speed){
    if(phase>14)phase=0;
    else phase++;
   /* if(phase>6){
      lc.setRow(matrix,abs(8-phase),B00000000);
    for(int i=abs(7-phase);i<8;i++){lc.setRow(matrix,i,arr[i-abs(7-phase)]);}
    }
    else{
      
    }*/
     //lc.clearDisplay(matrix);
    for(int i=0;i<phase;i++){
      if(abs(phase-i-1)>7 || i>7 )continue;
      lc.setRow(matrix,i,arr[abs(phase-i-1)]);
     // Serial.println(String(i) + "-i," + String(abs(phase-i-1)) + "-phase + i");
    }
    //Serial.println("_______________");
    prekol=millis();
  }
}
void Equals(int matrix){
byte  EqualsArr[8]{ B00000000,B11100000,B00010001,B00001110,B00000000,B11100000,B00010001,B00001110};
  
  
  static unsigned long EqualsMillis=0;
  static byte EqualsPhase=0;
  
  if(millis()-EqualsMillis>100){
    if(EqualsPhase>7)EqualsPhase=0;
    else EqualsPhase++;
    EqualsMillis=millis();
    for(int i=0;i<8;i++){lc.setRow(matrix,i,(EqualsArr[i]<<EqualsPhase)| (EqualsArr[i]>>8-EqualsPhase)) ;}
  }
  
}

void QuestionMark(int matrix){
  byte arr[8]{B00000000,B00011000,B00100100,B00100100,B00001000,B00010000,B00000000,B00010000};
    for(int i=0;i<8;i++){lc.setRow(matrix,i,arr[i]);}
}
void BigHumidityMode(){
    static unsigned long test=0;

int angle=0;
static int old_angle;
static int delta=400;
static byte check_out=0;
    
    if(millis()-test>3000){
  
      depiction(int(dht.readHumidity()/10), 3, 1);
  depiction(dht.readHumidity()-(int(dht.readHumidity()/10))*10, 2, 1);
  depiction(12,1,0);
  
      if(check_out>8){
        check_out=0;
        for(int i=0;i<9;i++){angle+=hum_array[i];}
        delta=angle-old_angle;
        old_angle=angle;
      }
      else check_out++;
                                
    for (byte i = 0; i < 8; i++) {                  
      hum_array[i] = hum_array[i + 1];     
    }
    hum_array[8] = dht.readHumidity();                   
    test=millis();
    }
    
   if(delta==0)Equals(0);
    else if(delta<0)arrowDown(0,100-(20*abs(delta)));
    else if(delta>300)QuestionMark(0);
    else arrowUp(0,100-(20*(delta)));  
  
  
 if(dht.readHumidity()>40 && dht.readHumidity()<= 60)GoodSmile(4);
 else if((dht.readHumidity()>30 && dht.readHumidity()<=40) || (dht.readHumidity()>60 && dht.readHumidity()< 70))RestlessSmile(4);
 else if(dht.readHumidity()<=30 || dht.readHumidity()>=70)TeriblSmile(4);
}
