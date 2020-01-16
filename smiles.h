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
void arrowUp(byte matrix){
  static unsigned long prekol=0;
  static int phase=0;
byte  arr[8]{B00001000,B00011100,B00001000,B00001000,B00001000,B00001000,B00001000,B00000000};
  if(millis()-prekol>100){
    if(phase>13)phase=0;
    else phase++;
    byte interval=8;
    if(phase>11)interval=4;
         for(int i=(7-phase);i<interval;i++){lc.setRow(matrix,i,arr[abs(7-i-phase)]);}
    prekol=millis();
  

  }
}
void arrowDown(byte matrix){
  static unsigned long prekol=0;
  static int phase=0;
byte  arr[8]{B00000000,B00001000,B00001000,B00001000,B00001000,B00001000,B00011100,B00001000};
  if(millis()-prekol>100){
    if(phase>13)phase=0;
    else phase++;
  }
}
}
