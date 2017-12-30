#include "LedControl.h" 

LedControl lc1=LedControl(4,3,2,1); // data/clk/load/nr of max
LedControl lc2=LedControl(8,7,6,1); // data/clk/load/nr of max 

int X[4];
int Y[4];
int Xa[4], Ya[4];
int minF, maxF;
int MAP[16][8];
 
int right = 10;
int left  = 9;
int down = 12;
int up = 13;
 
int piece;
int statesN;
int currentState = 1;
int statesX[4], statesY[4];

int score = 0;
int finalscore = 0;
boolean gameover = false;

int buzzer = 11;
boolean sound;

void setup(){

  lc1.shutdown(0,false);
  lc1.setIntensity(0,8);
  lc1.clearDisplay(0);
  
  lc2.shutdown(0,false);
  lc2.setIntensity(0,8);
  lc2.clearDisplay(0);
  
  pinMode(up, INPUT);
  pinMode(down, INPUT);
  pinMode(left, INPUT);
  pinMode(right, INPUT);
 
for(int i=0;i<16;i++)
        for(int j=0;j<8;j++)
                MAP[i][j]=0;
               
call_shape();
}
 
void loop(){
 
//game over

 for(int i=15; i>13; i--){
   for(int j=2; j<6; j++){
     if(MAP[i][j] == 1) gameover = true;
   }
 }
 if(gameover) {
   
 gameovertone();
   
 call_shape();
    for(int i=0;i<16;i++)
        for(int j=0;j<8;j++)
                MAP[i][j]=0;
    if(score!=0)finalscore = score;
    score = 0;
    gameover = false;
 }

  
  //board movement      
for(int i=0;i<15;i++)
        if((MAP[i][0]!=0)&&(MAP[i][1]!=0)&&(MAP[i][2]!=0)&&(MAP[i][3]!=0)&&(MAP[i][4]!=0)&&(MAP[i][5]!=0)&&(MAP[i][6]!=0)&&(MAP[i][7]!=0)){
                int kiek=15-i;
                
                for(int j=i;j<15;j++)
                        for(int k=0;k<8;k++)
                                MAP[j][k]=MAP[j+1][k];
                for(int j=0;j<8;j++)
                        MAP[15][j]=0;
                        
                        score++;
        }
 
// shapes movement
 
        //right left
        minF=15;
        for(int i=0;i<4;i++){
                if(Y[i]<minF) minF=Y[i];
        }
        maxF=0;
        for(int i=0;i<4;i++){
                if(Y[i]>maxF) maxF=Y[i];
        }      

keyPressed();


        //down
       
        int min2=7;
        for(int i=0;i<4;i++){
                if(X[i]<min2) min2=X[i];
        }
        int max2=0;
        for(int i=0;i<4;i++){
                if(X[i]>max2) max2=X[i];
        }
        boolean possible2=true;
    
        for(int i=max2;i>min2-1;i--){
                for(int j=0;j<4;j++){
                        if(Y[j]==0) possible2=false;
                        }
                if((possible2)&&(MAP[find_bottommost(i)-1][i]!=0)) possible2=false;
        }
        if(possible2){
                for(int i=0;i<4;i++){
                Y[i]=Y[i]-1;
                }
        }
        else{
         for(int i=0;i<4;i++){
          MAP[Y[i]][X[i]]=1;
          }        
          call_shape();
        }
        
draw_map();
delay(10);
 
}
void keyPressed(){
 
  if(digitalRead(right) == HIGH){
    
      buzzshort();
    
   //println("Desine");
   boolean possible=true;
                for(int i=maxF; i>minF-1; i--){
                        for(int j=0;j<4;j++){
                        if(X[j]==7) possible=false;
                        }
                        if((possible)&&(MAP[i][find_sidemost(i, false)+1]!=0)) possible=false;
 
                }
                if(possible){
                        for(int i=0;i<4;i++){
                                X[i]=X[i]+1;
                        }
              }
        }
 if(digitalRead(left) == HIGH){
   
     buzzshort();
   
   boolean possible=true;
        int minus;
        if(piece == 0) minus = 1;
          else minus = 0;
  
                for(int i=minF-minus; i<=maxF; i++){
                  
                  for(int j=0;j<4;j++){
                        if(X[j]==0) possible=false;
                        }
                        if((possible)&&(MAP[i][find_sidemost(i, true)-1]!=0)) possible=false;
                }
                if(possible){
                        for(int i=0;i<4;i++){
                                X[i]=X[i]-1;
                        }
        }
 } 
  // down key
  
  if(digitalRead(down) == HIGH){
    
    buzzshort();
    
    int min2=7;
        for(int i=0;i<4;i++){
                if(X[i]<min2) min2=X[i];
        }
        int max2=0;
        for(int i=0;i<4;i++){
                if(X[i]>max2) max2=X[i];
        }
    
    boolean possible3=true;
    
    while(possible3){
     
    
        for(int i=max2;i>min2-1;i--){
                for(int j=0;j<4;j++){
                        if(Y[j]==0) possible3=false;
                        }
                if((possible3)&&(MAP[find_bottommost(i)-1][i]!=0)) possible3=false;
        }
        if(possible3){
                for(int i=0;i<4;i++){
                Y[i]=Y[i]-1;
                }
        }
        else{
         for(int i=0;i<4;i++){
          MAP[Y[i]][X[i]]=1;
          }        
          call_shape();
        }
    }
  }
 
  // rotation
  
  if(digitalRead(up) == HIGH){
    
      buzzshort();
    
    switch(piece){
      case 0 : {
        if(currentState == statesN){
          statesX[0] = -1;
          statesY[0] = -1;
          statesX[1] = 0;
          statesY[1] = 0;
          statesX[2] = 1;
          statesY[2] = 1;
          statesX[3] = 2;
          statesY[3] = 2;
          
          if(rotation()){
           
          for(int i=0; i<4; i++){
            X[i] += statesX[i];
            Y[i] += statesY[i];
          }  
            
          currentState = 1;
        }
        }else{
          statesX[0] = 1;
          statesY[0] = 1;
          statesX[1] = 0;
          statesY[1] = 0;
          statesX[2] = -1;
          statesY[2] = -1;
          statesX[3] = -2;
          statesY[3] = -2;
          
          
          if(rotation()){
             
          for(int i=0; i<4; i++){
            X[i] += statesX[i];
            Y[i] += statesY[i];
          }  
            
          currentState++;
          }
        }
        break;
      }
      case 1:{
        break;
      }
      case 2:{
        if(currentState == 1){
          statesX[0] = 1;
          statesY[0] = 1;
          statesX[1] = 0;
          statesY[1] = 0;
          statesX[2] = -1;
          statesY[2] = -1;
          statesX[3] = -1;
          statesY[3] = 1;
          
          if(rotation()){
             
          for(int i=0; i<4; i++){
            X[i] += statesX[i];
            Y[i] += statesY[i];
          }  
            
          currentState++;
          }
        }
      else if(currentState == 2){
          statesX[0] = 1;
          statesY[0] = -1;
          statesX[1] = 0;
          statesY[1] = 0;
          statesX[2] = -1;
          statesY[2] = 1;
          statesX[3] = 1;
          statesY[3] = 1;
          
          if(rotation()){
             
          for(int i=0; i<4; i++){
            X[i] += statesX[i];
            Y[i] += statesY[i];
          }  
            
          currentState++;
          }     
      }
      else if(currentState == 3){
          statesX[0] = -1;
          statesY[0] = -1;
          statesX[1] = 0;
          statesY[1] = 0;
          statesX[2] = 1;
          statesY[2] = 1;
          statesX[3] = 1;
          statesY[3] = -1;
          
          if(rotation()){
             
          for(int i=0; i<4; i++){
            X[i] += statesX[i];
            Y[i] += statesY[i];
          }  
            
          currentState++;
          }
    }
     else if(currentState == statesN){
          statesX[0] = -1;
          statesY[0] = 1;
          statesX[1] = 0;
          statesY[1] = 0;
          statesX[2] = 1;
          statesY[2] = -1;
          statesX[3] = -1;
          statesY[3] = -1;
          
          if(rotation()){
             
          for(int i=0; i<4; i++){
            X[i] += statesX[i];
            Y[i] += statesY[i];
          }  
            
          currentState = 1;
          }
  }
   break;
}
   case 3:{
        if(currentState == 1){
          statesX[0] = 1;
          statesY[0] = 1;
          statesX[1] = 0;
          statesY[1] = 0;
          statesX[2] = -1;
          statesY[2] = -1;
          statesX[3] = -2;
          statesY[3] = 0;
          
          if(rotation()){
             
          for(int i=0; i<4; i++){
            X[i] += statesX[i];
            Y[i] += statesY[i];
          }  
            
          currentState++;
 
          }
        }
      else if(currentState == 2){
          statesX[0] = 1;
          statesY[0] = -1;
          statesX[1] = 0;
          statesY[1] = 0;
          statesX[2] = -1;
          statesY[2] = 1;
          statesX[3] = 0;
          statesY[3] = 2;
          
          if(rotation()){
             
          for(int i=0; i<4; i++){
            X[i] += statesX[i];
            Y[i] += statesY[i];
          }  
            
          currentState++;
          }     
      }
     else if(currentState == 3){
          statesX[0] = -1;
          statesY[0] = -1;
          statesX[1] = 0;
          statesY[1] = 0;
          statesX[2] = 1;
          statesY[2] = 1;
          statesX[3] = 2;
          statesY[3] = 0;
          
          if(rotation()){
             
          for(int i=0; i<4; i++){
            X[i] += statesX[i];
            Y[i] += statesY[i];
          }  
            
          currentState++;
          }
    }
     else if(currentState == statesN){
          statesX[0] = -1;
          statesY[0] = 1;
          statesX[1] = 0;
          statesY[1] = 0;
          statesX[2] = 1;
          statesY[2] = -1;
          statesX[3] = 0;
          statesY[3] = -2;
          
          if(rotation()){
             
          for(int i=0; i<4; i++){
            X[i] += statesX[i];
            Y[i] += statesY[i];
          }  
            
          currentState = 1;
          }
  }
   break;
}
case 4:{
        if(currentState == 1){
          statesX[0] = 1;
          statesY[0] = 1;
          statesX[1] = 0;
          statesY[1] = 0;
          statesX[2] = -1;
          statesY[2] = -1;
          statesX[3] = 0;
          statesY[3] = 2;
          
          if(rotation()){
             
          for(int i=0; i<4; i++){
            X[i] += statesX[i];
            Y[i] += statesY[i];
          }  
            
          currentState++;
          }
        }
     else if(currentState == 2){
          statesX[0] = 1;
          statesY[0] = -1;
          statesX[1] = 0;
          statesY[1] = 0;
          statesX[2] = -1;
          statesY[2] = 1;
          statesX[3] = 2;
          statesY[3] = 0;
          
          if(rotation()){          
             
          for(int i=0; i<4; i++){
            X[i] += statesX[i];
            Y[i] += statesY[i];
          }  
            
          currentState++;
          }     
      }
     else if(currentState == 3){
          statesX[0] = -1;
          statesY[0] = -1;
          statesX[1] = 0;
          statesY[1] = 0;
          statesX[2] = 1;
          statesY[2] = 1;
          statesX[3] = 0;
          statesY[3] = -2;
          
          if(rotation()){
             
          for(int i=0; i<4; i++){
            X[i] += statesX[i];
            Y[i] += statesY[i];
          }  
            
          currentState++;
          }
    }
    else if(currentState == statesN){
          statesX[0] = -1;
          statesY[0] = 1;
          statesX[1] = 0;
          statesY[1] = 0;
          statesX[2] = 1;
          statesY[2] = -1;
          statesX[3] = -2;
          statesY[3] = 0;
          
          if(rotation()){
             
          for(int i=0; i<4; i++){
            X[i] += statesX[i];
            Y[i] += statesY[i];
          }  
            
          currentState = 1;
          }
  }
   break;
}
  case 5 : {
        if(currentState == statesN){
          statesX[0] = -2;
          statesY[0] = -1;
          statesX[1] = -1;
          statesY[1] = 0;
          statesX[2] = 0;
          statesY[2] = -1;
          statesX[3] = 1;
          statesY[3] = 0;
          
          if(rotation()){
             
          for(int i=0; i<4; i++){
            X[i] += statesX[i];
            Y[i] += statesY[i];
          }  
            
          
          currentState = 1;
        }
        }else{
          statesX[0] = 2;
          statesY[0] = 1;
          statesX[1] = 1;
          statesY[1] = 0;
          statesX[2] = 0;
          statesY[2] = 1;
          statesX[3] = -1;
          statesY[3] = 0;
          
          
          if(rotation()){
             
          for(int i=0; i<4; i++){
            X[i] += statesX[i];
            Y[i] += statesY[i];
          }  
            
          currentState++;
          }
        }
        break;
      }
      case 6 : {
        if(currentState == statesN){
          statesX[0] = -1;
          statesY[0] = 0;
          statesX[1] = 0;
          statesY[1] = -1;
          statesX[2] = 1;
          statesY[2] = 0;
          statesX[3] = 2;
          statesY[3] = -1;
          
          if(rotation()){
          
          for(int i=0; i<4; i++){
            X[i] += statesX[i];
            Y[i] += statesY[i];
          }  
            
          currentState = 1;
        }
        }else{
          statesX[0] = 1;
          statesY[0] = 0;
          statesX[1] = 0;
          statesY[1] = 1;
          statesX[2] = -1;
          statesY[2] = 0;
          statesX[3] = -2;
          statesY[3] = 1;
          
          
          if(rotation()){
             
          for(int i=0; i<4; i++){
            X[i] += statesX[i];
            Y[i] += statesY[i];
          }  
            
          currentState++;
          }
        }
        break;
      }
    }
  }
}

void draw_map(){
  for(int i=0; i<8; i++){
    for(int j=0; j<8; j++){
       if(MAP[i][j] == 1) lc1.setLed(0, j, i, true);
         else lc1.setLed(0, j, i, false);
        delay(2); 
    }
  }
  for(int i=8; i<16; i++){
    for(int j=0; j<8; j++){
      if(MAP[i][j] == 1) lc2.setLed(0, j, i-8, true);
        else lc2.setLed(0, j, i-8, false);
      delay(2);
    }
  }
  for(int i=0;i<4;i++){
   if(Y[i] >= 8) lc2.setLed(0, X[i], Y[i]-8, true);
     else lc1.setLed(0, X[i], Y[i], true);
   delay(2);
}  
  
}
boolean rotation(){
  boolean possibru = true;

  for(int i=0; i<4; i++){
    if((Y[i] + statesY[i] < 0)||(Y[i] + statesY[i] > 15)) {
      return false;
    }
    if((X[i] + statesX[i] < 0)||(X[i] + statesX[i] > 7)){ 
      return false;
    }
  }
  
  for(int i=0; i<4; i++){
    if(MAP[Y[i] + statesY[i]][X[i] + statesX[i]] == 1) possibru = false; 
  }

return possibru;
}

int find_sidemost(int n, boolean left){
 
        if(left){
        int minXa=7;
        for(int i=0;i<4;i++){
        Xa[i]=8;
        if(Y[i]==n) Xa[i]=X[i];
        if(Xa[i]<minXa) minXa=Xa[i];
        }
        return minXa;
        }
        else{
        int maxXa=0;
        for(int i=0;i<4;i++){
        Xa[i]=-1;
        if(Y[i]==n) Xa[i]=X[i];
        if(Xa[i]>maxXa) maxXa=Xa[i];
        }
        return maxXa;
        }
}
int find_bottommost(int n){
        int minYa=15;
        for(int i=0;i<4;i++){
                Ya[i]=16;
                if(X[i]==n) Ya[i]=Y[i];
                if(Ya[i]<minYa) minYa=Ya[i];
        }
        return minYa;
}
void call_shape(){
        int shape = (int) random(6);
         currentState = 1;
        
        piece = shape;
        
        switch(shape){
                case 0: { X[0] = 2; X[1] = 3; X[2] = 4; X[3] = 5;
                          Y[0] = 15; Y[1] = 15; Y[2] = 15; Y[3] = 15;
                         statesN = 2;
                          break;}
                case 1: { X[0] = 3; X[1] = 4; X[2] = 3; X[3] = 4;
                          Y[0] = 15; Y[1] = 15; Y[2] = 14; Y[3] = 14;
                          statesN = 1;
                          break;}
                case 2: { X[0] = 2; X[1] = 3; X[2] = 4; X[3] = 3;
                          Y[0] = 15; Y[1] = 15; Y[2] = 15; Y[3] = 14;
                          statesN = 4;
                          break;}
                case 3: { X[0] = 2; X[1] = 3; X[2] = 4; X[3] = 4;
                          Y[0] = 15; Y[1] = 15; Y[2] = 15; Y[3] = 14;
                          statesN = 4;
                          break;}
                case 4: { X[0] = 2; X[1] = 3; X[2] = 4; X[3] = 2;
                          Y[0] = 15; Y[1] = 15; Y[2] = 15; Y[3] = 14;
                          statesN = 4;
                          break;}
                case 5: { X[0] = 2; X[1] = 3; X[2] = 3; X[3] = 4;
                          Y[0] = 15; Y[1] = 15; Y[2] = 14; Y[3] = 14;
                          statesN = 2;
                          break;}
                case 6: { X[0] = 2; X[1] = 3; X[2] = 3; X[3] = 4;
                          Y[0] = 14; Y[1] = 14; Y[2] = 15; Y[3] = 15;
                          statesN = 2;
                          break;}
       
}
}
//sounds

void buzz(){
  tone(buzzer, 500, 25); 
}
void buzzshort(){
  tone(buzzer, 300, 15);
}
void gameovertone(){
int note[] = {700, 600, 500, 400, 300, 200};
    for(int i = 0; i < 6; i++){
      tone(buzzer, note[i], 150);
      delay(200);
    }
  }
