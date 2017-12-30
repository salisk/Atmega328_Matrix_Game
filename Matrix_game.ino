#include "LedControl.h" 

LedControl lc=LedControl(8,7,6,1); // data/clk/load/nr of max

int menunumber = 0;
  //inputs
//int enter = 9;
int up = 13;
int down = 12;
int left = 9;
int right = 10;
//int shift = 6;
int buzzer = 11;
boolean sound;
int soundinput;

  //screens
  
int board[8][8] = {
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}};
  
int clearboard[8][8] = {
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}};
  
  //Menu Screens
  
int menuscreen1[8][8] = {
  {0,0,1,1,1,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,1,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,1,1,1,0,0}};
  
 int menuscreen2[8][8] = {
  {0,0,0,0,0,0,0,0},
  {0,0,0,1,1,0,0,0},
  {0,0,0,1,1,0,0,0},
  {0,0,1,1,1,1,0,0},
  {0,1,1,1,1,1,1,0},
  {0,0,0,1,1,0,0,0},
  {0,0,0,1,1,0,0,0},
  {0,0,0,1,1,0,0,0}};
  
 int menuscreen3[8][8] = {
  {0,0,0,0,0,1,1,1},
  {0,0,0,0,0,1,1,1},
  {1,0,0,0,0,1,1,1},
  {1,0,0,0,0,1,1,1},
  {1,0,1,0,0,1,1,1},
  {0,0,0,0,0,1,1,1},
  {0,0,0,0,0,1,1,1},
  {0,0,0,0,0,1,1,1}};
  
  // DDR screens
  
  int ddrup[8][8] = {
  {0,0,0,0,0,0,0,0},
  {0,0,0,1,0,0,0,0},
  {0,0,0,1,1,0,0,0},
  {1,1,1,1,1,1,1,0},
  {1,1,1,1,1,1,1,0},
  {0,0,0,1,1,0,0,0},
  {0,0,0,1,0,0,0,0},
  {0,0,0,0,0,0,0,0}};
  
  
  int ddrdown[8][8] = {
   {0,0,0,0,0,0,0,0},
  {0,0,0,0,1,0,0,0},
  {0,0,0,1,1,0,0,0},
  {0,1,1,1,1,1,1,1},
  {0,1,1,1,1,1,1,1},
  {0,0,0,1,1,0,0,0},
  {0,0,0,0,1,0,0,0},
  {0,0,0,0,0,0,0,0}};
  
  int ddrleft[8][8] = {
  {0,0,0,0,0,0,0,0},
  {0,0,0,1,1,0,0,0},
  {0,0,0,1,1,0,0,0},
  {0,0,1,1,1,1,0,0},
  {0,1,1,1,1,1,1,0},
  {0,0,0,1,1,0,0,0},
  {0,0,0,1,1,0,0,0},
  {0,0,0,1,1,0,0,0}};
 
  
  int ddrright[8][8] = {
   {0,0,0,1,1,0,0,0},
  {0,0,0,1,1,0,0,0},
  {0,0,0,1,1,0,0,0},
  {0,1,1,1,1,1,1,0},
  {0,0,1,1,1,1,0,0},
  {0,0,0,1,1,0,0,0},
  {0,0,0,1,1,0,0,0},
  {0,0,0,0,0,0,0,0}};
  
  
  int ddry[8][8] = {
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,1,0,0,0},
  {0,0,0,1,0,0,0,0},
  {0,0,1,0,0,0,0,0},
  {0,0,0,1,0,0,0,0},
  {0,0,0,0,1,0,0,0},
  {0,0,0,0,0,1,0,0},
  {0,0,0,0,0,0,0,0}};
  
  int ddrx[8][8] = {
  {1,0,0,0,0,0,0,1},
  {0,1,0,0,0,0,1,0},
  {0,0,1,0,0,1,0,0},
  {0,0,0,1,1,0,0,0},
  {0,0,0,1,1,0,0,0},
  {0,0,1,0,0,1,0,0},
  {0,1,0,0,0,0,1,0},
  {1,0,0,0,0,0,0,1}};
  
  
  
  // updatescreen
  
void updatescreen(){
   for(int i=0;i<8;i++){
     for(int j=0;j<8;j++){
       if(board[i][j]==1) lc.setLed(0,i,j,true);
       else lc.setLed(0,i,j,false);
      delay(2); 
     }
}
}

//gameover animation

void gameover(){
  
  gameovertone();
    
   for(int i = 0; i<8; i++){
         for(int j = 0; j<8; j++){
           board[i][j]=clearboard[i][j];}
         }
   for(int i = 7; i>=0; i--){
       for(int k=0;k<3;k++){
         for(int j=0;j<8;j++){
             if(i>=2)board[j][i-k]=1;}
       }
           
       updatescreen();
       delay(2);
       
       for(int j=0;j<8;j++){
         for(int k=0;k<3;k++){
           for(int j=0;j<8;j++){
               if(i>=2)board[j][i-k]=0;}}
       }}
       delay(300);
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

//Games

// PONG(1 player)

void game1(){
  boolean gameon = true;
  int ballx = 4;
  int bally = 4;
  int score = 0;
  int pad1 = 2;
  int pad2 = 2;
  int gamespeed = 5;
  int delaytime = 15;
  int time = 0;
  boolean u = true;
  boolean r = true;
  boolean rip = false;
  int ripcd = 0;
  int upre = 1;
  
  while(gameon){
    for(int i = 0; i<8; i++){
         for(int j = 0; j<8; j++){
           board[i][j]=clearboard[i][j];
         }}
          for(int i=0;i<3;i++){
      board[0][pad1+i]=1;
    }
    for(int i=0;i<3;i++){
      board[7][pad2+i]=1;
    }
    board[ballx][bally]= 1;
    if(digitalRead(up)==HIGH){
      pad1++;
      buzzshort();}
    if(digitalRead(down)==HIGH){ 
      pad1--;
      buzzshort();}
    
     pad2 = bally;

     if(pad1>5) pad1=5;
     if(pad1<0) pad1=0;
     if(pad2>5) pad2=5;
     if(pad2<0) pad2=0;
     
    //ball collision
    if(bally>6) u = false;
    if(bally<1) u = true;
    
    //ball vs player
    if(ballx>5) {
      r = false;
      u = random(2);}
      
    if(ballx==1 && r==false){
      
      if(u)upre = 1;
        else upre = - 1;
        
      if(pad1==bally+upre){
        r = true;
        u = false;}
      if(pad1+1==bally+upre){
        r = true;
        u = random(2);}
      if(pad1+2==bally+upre){
        r = true;
        u = true;}
      if(pad1!=bally+upre&&
      pad1+1!=bally+upre&&
      pad1+2!=bally+upre)
        rip = true;
    
    }
    //ball movement + speed 
    
      if(r) ballx++;
        else ballx--;
      if(u) bally++;
        else bally--;
    
    time++;
    updatescreen();
    delay(delaytime);
    if(rip) ripcd++;
    if(ripcd==2) gameon = false;
    
  }
  //gameover(not added)
  gameover();
  menu(menunumber);
}

//DDR

void game2(){
  boolean gameon = true;
  boolean turn = true;
  int time = 5;
  int speedy(400);
  int mistakes = 0;
  int score = 0;
    
  while(gameon){
      int currenttime = 0;
      int direct = random(1,5);
      int answer = true;
      int answerkey = 0;
      
      switch(direct){ // 1 - up  // 2 - right   // 3 - down  // 4 - left
            case 1:  
              for(int i=0;i<8;i++){
                for(int j=0;j<8;j++){
                  board[i][j]=ddrup[i][j];}}
                  updatescreen();
                  delay(10);     
              break;    
            case 2:  
             for(int i=0;i<8;i++){
                for(int j=0;j<8;j++){
                  board[i][j]=ddrright[i][j];}}
                  updatescreen();
                  delay(10);     
              break; 
            case 3:
              for(int i=0;i<8;i++){
                for(int j=0;j<8;j++){
                  board[i][j]=ddrdown[i][j];}}
                  updatescreen();
                  delay(10);     
              break; 
            case 4:
              for(int i=0;i<8;i++){
                for(int j=0;j<8;j++){
                  board[i][j]=ddrleft[i][j];}} 
                  updatescreen();
                  delay(10);    
              break;}
        currenttime=0;
        while(digitalRead(up)==LOW
        &&digitalRead(right)==LOW
        &&digitalRead(down)==LOW
        &&digitalRead(left)==LOW){
          if(time==currenttime) answer=false;
         currenttime++;
         delay(speedy);  
        }
       if(digitalRead(up)==HIGH) answerkey=1;
       if(digitalRead(right)==HIGH) answerkey=2;
       if(digitalRead(down)==HIGH) answerkey=3;
       if(digitalRead(left)==HIGH) answerkey=4;
       delay(5);
       if(answer==false||direct!=answerkey){
           for(int i=0;i<8;i++){
                for(int j=0;j<8;j++){
                  board[i][j]=ddrx[i][j];}} 
                  updatescreen();
                  mistakes++;
                  delay(100); }
        else{
        for(int i=0;i<8;i++){
                for(int j=0;j<8;j++){
                  board[i][j]=ddry[i][j];}} 
                  updatescreen();
                  score++;
                  delay(100); }
   if(mistakes==5) gameon=false;
  }
  menu(menunumber);
  gameover();
  // gameover screen + adds
}

//Breakout

void game3(){
  int pad = 2;
  boolean gameon = true;
  boolean u = true;
  boolean r = true;
  boolean rip = false;
  int ballx = 2;
  int bally = 2;
  int score = 0;
  int gamespeed = 5;
  int delaytime = 150;
  int time = 0;
  int ripcd = 0;
  int rpre = 1;
  //int a=0;
  int layout[8][8] = {
  {0,0,0,0,0,1,1,1},
  {0,0,0,0,0,1,0,1},
  {0,0,0,0,0,1,1,1},
  {0,0,0,0,0,1,1,0},
  {0,0,0,0,0,1,1,0},
  {0,0,0,0,0,1,1,1},
  {0,0,0,0,0,1,0,1},
  {0,0,0,0,0,1,1,1}};  
         
      while(gameon){
        
      for(int i = 0; i<8; i++){
         for(int j = 0; j<8; j++){
           board[i][j]=layout[i][j];
         }
       }  
    /*if(a==2){
      board[7][1]=1;
      board[6][1]=1;
      board[5][1]=1;}
      */
    if(digitalRead(right)==HIGH){
      pad++;
      buzzshort();}
    if(digitalRead(left)==HIGH){ 
      pad--;
      buzzshort();}

     if(pad>5) pad=5;
     if(pad<0) pad=0;
     
    //ball collision
    if(ballx>6) r = false;
    if(ballx<1) r = true;
    
    //ball vs collision
    if(u){
      if(r) rpre = 1;
        else rpre = -1;
      if(board[ballx+rpre][bally+1]==1){
         u=false;
         board[ballx+rpre][bally+1]=0;
         layout[ballx+rpre][bally+1]=0;  
      }
     }
     if(u==false&&bally>2){
      if(r) rpre = 1;
        else rpre = -1;
      if(board[ballx+rpre][bally-1]==1){
         u=true;
         board[ballx+rpre][bally-1]=0;
         layout[ballx+rpre][bally-1]=0;  
      }
     }
    
    if(bally>6) {
      u = false;
    }
     // player collision 
    if(bally==1 && u==false){
      
      if(r)rpre = 1;
        else rpre = - 1;
        
      if(pad==ballx+rpre){
        u = true;
        r = false;}
      if(pad+1==ballx+rpre){
        u = true;
        r = random(2);}
      if(pad+2==ballx+rpre){
        u = true;
        r = true;}
      if(pad!=ballx+rpre&&
      pad+1!=ballx+rpre&&
      pad+2!=ballx+rpre)
        rip = true;
    
    }
    //ball movement + speed 
    
      if(r) ballx++;
        else ballx--;
      if(u) bally++;
        else bally--;
        
        board[ballx][bally]= 1;
        
        for(int i=0;i<3;i++){
          board[pad+i][0]=1;
        }
     
      updatescreen();
      delay(delaytime);
      if(rip) ripcd++;
      if(ripcd==2) gameon = false;
     // a++;
    }
    gameovertone();
    gameover();
}

//menu

void menu(int screennumber){
  Serial.println("menu");
   Serial.println(screennumber);
 //int menunumber = screennumber;
  switch (screennumber){
     case 0:
     Serial.println("case 0");
     for(int i = 0; i<8; i++){
         for(int j = 0; j<8; j++){
           board[i][j]=menuscreen1[i][j];
           delay(2);}}
   while(digitalRead(up)== LOW && digitalRead(right)== LOW){
      Serial.println("right=");
       Serial.println(digitalRead(right));
       updatescreen();}
     if(digitalRead(up) == HIGH) game1();
       else { 
          Serial.println("return");
         buzz();
         menunumber++;
         delay(100);
         return ;
     }
     
      case 1:
        while(digitalRead(right)==HIGH||
          digitalRead(left)==HIGH)delay(50);
          
       while(digitalRead(up)==LOW && 
         digitalRead(right)==LOW &&
         digitalRead(left)==LOW) {
       for(int i = 0; i<8; i++){
         for(int j = 0; j<8; j++){
           board[i][j]=menuscreen2[i][j];
           delay(2);}}
           updatescreen();
     }
       if(digitalRead(left)== HIGH){
         buzz(); 
         menunumber--;
         delay(100);
        return;}
         else if(digitalRead(up)==HIGH) game2();
           else {
               delay(100);
               menunumber++;
               return;}
               
        case 2:
          while(digitalRead(right)==HIGH||
          digitalRead(left)==HIGH)delay(50);
          
           while(digitalRead(up)==LOW && 
                // digitalRead(right)==LOW &&
                 digitalRead(left)==LOW) {
               for(int i = 0; i<8; i++){
                 for(int j = 0; j<8; j++){
                   board[i][j]=menuscreen3[i][j];
                   delay(2);}}
                   updatescreen();
             }
               if(digitalRead(left)== HIGH){
                 buzz(); 
                 menunumber--;
                 delay(100);
                return;}
                 else if(digitalRead(up)==HIGH) game3();
                   else {
                       menunumber++;
                       return;}       
  }
}
void setup()
{
  // the zero refers to the MAX7219 number, it is zero for 1 chip
  lc.shutdown(0,false);// turn off power saving, enables display
  lc.setIntensity(0,8);// sets brightness (0~15 possible values)
  lc.clearDisplay(0);
  pinMode(up, INPUT);
  pinMode(down, INPUT);
  pinMode(left, INPUT);
  pinMode(right, INPUT);
  //pinMode(shift, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}

//loop
void loop(){
  Serial.println("on");
  Serial.println("pries menu");
  menu(menunumber);
}
  
  

