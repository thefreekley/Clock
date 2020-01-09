void LedAnimation1(boolean Off,int row,int matrix){
    for(int i=1;i<8;i++){
  lc.setLed(matrix+4,i,row,Off);
  delay(50);
  }
  for(int i=0;i<7;i++){
  lc.setLed(matrix,i,row,Off);
  delay(50);
  }
    
}

void HorizontalRigthLine(boolean OFF,byte matrix, byte row, byte column, byte length_, int ping){ //OFF - включать, виключать пиксели
  for(int i=0;i<length_;i++){
    lc.setLed(matrix,column,i+row,OFF);
    delay(ping);
  }
}
 void HorizontalLeftLine(boolean OFF,byte matrix, byte row, byte column, byte length_, int ping){ //OFF - включать, виключать пиксели
  for(int i=length_-1;i>=0;i--){
    lc.setLed(matrix,column,i+row,OFF);
    delay(ping);
  }
}
 void VerticalUpLine(boolean OFF,byte matrix, byte row, byte column, byte length_, int ping){ //OFF - включать, виключать пиксели
  for(int i=length_-1;i>=0;i--){
    lc.setLed(matrix,column+i,row,OFF);
    delay(ping);
  }
}
 void VerticalDownLine(boolean OFF,byte matrix, byte row, byte column, byte length_, int ping){ //OFF - включать, виключать пиксели
  for(int i=0;i<length_;i++){
    lc.setLed(matrix,column+i,row,OFF);
    delay(ping);
  }
}

void AnimationNumber(boolean off,int number,int matrix,int row,int ping){
  switch(number){
   case 1:LedAnimation1(off,row,matrix); break;
   case 2:
   HorizontalRigthLine(off,matrix+4,row-1,1,3,ping);
   VerticalDownLine(off,matrix+4,row+1,1,7,ping);
   HorizontalLeftLine(off,matrix+4,row-1,7,3,ping);
   VerticalDownLine(off,matrix,row-1,0,6,ping);
   HorizontalRigthLine(off,matrix,row-1,6,3,ping);
   break;
  case 3:
   HorizontalRigthLine(off,matrix+4,row-1,1,3,ping);
   VerticalDownLine(off,matrix+4,row+1,1,7,ping);
   VerticalDownLine(off,matrix,row+1,0,6,ping);
   HorizontalLeftLine(off,matrix,row-1,6,3,ping);
   HorizontalLeftLine(off,matrix+4,row-1,7,3,ping);
   break; 
   case 4:
   VerticalDownLine(off,matrix+4,row+1,1,7,ping);
   HorizontalLeftLine(off,matrix,row-1,0,3,ping);
   VerticalUpLine(off,matrix+4,row-1,1,7,ping);
   VerticalDownLine(off,matrix,row+1,0,7,ping);
   break;
   case 5:
    HorizontalLeftLine(off,matrix+4,row-1,1,3,ping);
    VerticalDownLine(off,matrix+4,row-1,1,7,ping);
    HorizontalRigthLine(off,matrix+4,row-1,7,3,ping);
    VerticalDownLine(off,matrix,row+1,0,6,ping);
    HorizontalLeftLine(off,matrix,row-1,6,3,ping);
    break;
   case 6:
    HorizontalLeftLine(off,matrix+4,row-1,1,3,ping);
    VerticalDownLine(off,matrix+4,row-1,1,7,ping);
    VerticalDownLine(off,matrix,row-1,0,7,ping);
    HorizontalRigthLine(off,matrix,row-1,6,3,ping);
    VerticalUpLine(off,matrix,row+1,0,7,ping);
    HorizontalLeftLine(off,matrix+4,row-1,7,3,ping);
    break;
    case 7:
    HorizontalRigthLine(off,matrix+4,row-1,1,3,ping);
    VerticalDownLine(off,matrix+4,row+1,1,7,ping);
    VerticalDownLine(off,matrix,row+1,0,7,ping);
   break;
   case 8:
   HorizontalRigthLine(off,matrix+4,row-1,1,3,ping);
    VerticalDownLine(off,matrix+4,row+1,1,7,ping);
    VerticalDownLine(off,matrix,row+1,0,7,ping);
    HorizontalLeftLine(off,matrix,row-1,6,3,ping);
    VerticalUpLine(off,matrix,row-1,0,7,ping);
    VerticalUpLine(off,matrix+4,row-1,1,7,ping);
    HorizontalLeftLine(off,matrix+4,row-1,7,3,ping);
    break;
    case 9:
      HorizontalLeftLine(off,matrix,row-1,0,3,ping);
       VerticalUpLine(off,matrix+4,row-1,1,7,ping);
       HorizontalRigthLine(off,matrix+4,row-1,1,3,ping);
       VerticalDownLine(off,matrix+4,row+1,1,7,ping);
    VerticalDownLine(off,matrix,row+1,0,7,ping);
    HorizontalLeftLine(off,matrix,row-1,6,3,ping);
    break;
    case 0:
       HorizontalRigthLine(off,matrix+4,row-1,1,3,ping);
    VerticalDownLine(off,matrix+4,row+1,1,7,ping);
    VerticalDownLine(off,matrix,row+1,0,7,ping);
    HorizontalLeftLine(off,matrix,row-1,6,3,ping);
    VerticalUpLine(off,matrix,row-1,0,7,ping);
    VerticalUpLine(off,matrix+4,row-1,1,7,ping);

    break;
  }
}


