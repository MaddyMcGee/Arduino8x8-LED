//Maddy McGee 11/4/16
//Code under construction
//a modification of my pong file to a game of 'breakout'
//goal to 'destroy' all the lights in rows 1 & 2
//physics of reflection are currently wonky

//I am annotating a printed copy of this code during my study hall to try and determine how to do my physics 
//but if anyone sees this and has suggestions they would be much appreciated

const int X_pinA = 4; // analog pin connected to X output for joystick A
const int Y_pinA = 5; // analog pin connected to Y output for joystick A
const int xValue[8] = {0,1,2,3,4,5,6,14}; //on when HIGH
const int yValue[8] = {7,8,9,10,11,12,13,15}; // on when LOW
boolean row1[8] = {true,true,true,true,true,true,true,true};
boolean row2[8] = {true,true,true,true,true,true,true,true};
// value 14 is analog A0 and 15 is analog A1
int yVar = 4;
int lastY = 0;
int xBall = 3;
int yBall = 4;
int lastBallX = 3;
int lastBallY = 4;
int velocityX = 1;//positive is towards pad, negative towards walls(rows)
int velocityY = 0;
int velocityPad;
unsigned long previousMillis = 0;//timer for display
unsigned long previousMillisCalc = 0;//timer for calculation
unsigned long previousMillisSpeed;//decrement calcTime to increase net speed
long timer = 5;
long calcTime = 85;//initial game speed

int component = 1; //alternate components displayed

//methods start
void calcRow1(boolean row[8], int x, int y, int vx, int vy)
{
  if(x == 1)
  {
    row[y] = false;
  }
}
void calcRow2(boolean row[8], int x, int y, int vx, int vy)
{
  if((x == 2 ) || (x==1))
  {
    row[y] = false;
  }
}
void displayRow1(boolean row[8])
{
  digitalWrite(xValue[0], HIGH);
  for(int cnt = 0; cnt < 8; cnt ++)
  {
    if (row[cnt])
      digitalWrite(yValue[cnt], LOW);
  }
}
void displayRow2(boolean row[8])
{
  digitalWrite(xValue[1], HIGH);
  for(int cnt = 0; cnt < 8; cnt ++)
  {
    if (row[cnt])
      digitalWrite(yValue[cnt], LOW);
  }
}
void positionDisplayPaddle(int y) //displays paddle as a 1x3 shape at xValue[7] with the given Y-value in the middle
{
  //y-value
  digitalWrite(yValue[y],LOW);
  digitalWrite(yValue[y+1],LOW);
  digitalWrite(yValue[y-1],LOW);
  digitalWrite(xValue[7],HIGH);
}
void positionDisplayBall(int x,int y)
{
  digitalWrite(xValue[x], HIGH);
  digitalWrite(yValue[y], LOW);
}

void clearBoard() //turns all pins to be "off"
{
  digitalWrite(0,LOW);
  digitalWrite(1,LOW);
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH);
  digitalWrite(11,HIGH);
  digitalWrite(12,HIGH);
  digitalWrite(13,HIGH);
  digitalWrite(14,LOW);
  digitalWrite(15,HIGH);
}

int paddleMove(int b) 
{
  //joystick control of paddle
  if (analogRead(X_pinA)< 212)
  {
    if (b < 6)
    {
      b ++;
    }
  }
    if (analogRead(X_pinA) > 812)
    {
      if(b > 1)
      {
        b --;
      }
    }
    return b;
}

int ballMoveX(int ball, int v) //calculates ball's X position 
{
  if (ball >= 0)
  {
    ball += v;
  }
  return ball;
}

int getVPad(int last, int y) //calculates velocity of paddle
{
  return y-last;
}

int ballMoveY(int ball, int v) //calculates ball's Y position 
{
  if (! ((v<0 && ball == 0) || (v>0 && ball == 7)))
  {
    ball += v;
  }
  return ball;
}

int getVX(int ball,int v, int ballY, int padY, boolean firstRow[8],boolean secondRow[8]) //calculates ball's X velocity
{
  if ((ball == 6) && (ballY == padY || ballY == padY+1 || ballY == padY-1))//deflect ball if at paddle
  {
      v = -1;
  }
  if (ball == 0 || (ball == 1 && firstRow[ballY]) || (ball == 2 && secondRow[ballY]))//deflect on wall/rows
  {
    v = 1;
  }
  return v;
}

int getVY(int ballY,int v, int pad, int ballX, int vp, boolean firstRow[8],boolean secondRow[8]) //calculates ball's Y velocity
{
  
  if ((ballX == 6) && (ballY == pad || ballY == pad+1 || ballY == pad-1))//deflection at paddle
  {
    v = vp;//set equal to velocity of paddle
  }
  if ( ballY == 7 || ballY == 0 || (ballX == 1 && firstRow[ballY]) || (ballX == 2 && secondRow[ballY]))//deflection at walls
  {
    v = -v;
  }
  return v;
}


void reset()
{
  //variable reset
  yVar = 4;
  lastY = 0;
  xBall = 3;
  yBall = 4;
  lastBallX = 3;
  lastBallY = 4;
  velocityX = 1;
  velocityY = 0;
  calcTime = 85;//speed returned to initial speed
  unsigned long previousMillisReset = 0;
  unsigned long previousMillisResetCalc = 0;
  for(int cnt = 0; cnt<8; cnt++)
    row1[cnt] = true;
  for(int cnt = 0; cnt<8; cnt++)
    row2[cnt] = true;
  
  digitalWrite(0,LOW);
  digitalWrite(1,LOW);
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH);
  digitalWrite(11,HIGH);
  digitalWrite(12,HIGH);
  digitalWrite(13,HIGH);
  digitalWrite(14,LOW);
  digitalWrite(15,HIGH);
  delay(500);
  digitalWrite(0,HIGH);
  digitalWrite(1,HIGH);
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(5,HIGH);
  digitalWrite(6,HIGH);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
  digitalWrite(13,LOW);
  digitalWrite(14,HIGH);
  digitalWrite(15,LOW);
  delay(500);
  digitalWrite(0,LOW);
  digitalWrite(1,LOW);
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH);
  digitalWrite(11,HIGH);
  digitalWrite(12,HIGH);
  digitalWrite(13,HIGH);
  digitalWrite(14,LOW);
  digitalWrite(15,HIGH);

  positionDisplayBall(3,4);
  positionDisplayPaddle(4);

  int cnt = 60;
  while ( cnt >0)
  {
    /*
  clearBoard();
  yVar = paddleMove(yVar);
  positionDisplayPaddle(yVar);
  lastY = yVar;
  delay(50);
  clearBoard();
  positionDisplayBall(3,4);
  delay(50);
  */

  unsigned long currentMillisReset = millis();
  
  if((currentMillisReset - previousMillisResetCalc >= calcTime))
  {
    //read joystick and calculate movement/velocity
    yVar = paddleMove(yVar);
    velocityPad = getVPad(lastY,yVar);
    
    // Remember the time
    previousMillisResetCalc = currentMillisReset; 
  }
 
  if((component == 1) && (currentMillisReset - previousMillisReset >= timer))
  {
    // Remember the time
    previousMillisReset = currentMillisReset;  
    
    //update the pins & save position
    clearBoard();
    positionDisplayBall(3,4);
    
    component = 2;//changes to paddle next
    cnt--; //countdown to end loop
  }
  else if ((component == 2) &&(currentMillisReset - previousMillisReset >= timer))
  {
    
    // Remember the time
    previousMillisReset = currentMillisReset;   
    
    //update pins and save position
    clearBoard();
    positionDisplayPaddle(yVar);
    lastY = yVar;

    component = 3;//changes to ball next
    cnt--;//countdown to end loop
  }else if ((component == 3) &&(currentMillisReset - previousMillisReset >= timer))
  {
    // Remember the time
    previousMillisReset = currentMillisReset;   
    
    //update pins and save position
    clearBoard();
    displayRow2(row2);

    component = 4;//changes to row 1
  }
  else if ((component == 4) &&(currentMillisReset - previousMillisReset >= timer))
  {
    // Remember the time
    previousMillisReset = currentMillisReset;   
    
    //update pins and save position
    clearBoard();
    displayRow1(row1);

    component = 1;//changes to ball
  }
  
  }//end of reset loop
  
}

void defeat(int d)
{
  if (d == 7)
  {
    reset();
  }
}




//code
  
  void setup() 
{
  pinMode(0,OUTPUT);
  pinMode(1,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(14,OUTPUT);
  pinMode(15,OUTPUT);
  reset();
}

void loop() 
{
  
  unsigned long currentMillis = millis();
  
  
  if((currentMillis - previousMillisCalc >= calcTime))
  {
  
    //calculate ball velocity
    velocityY = getVY(yBall, velocityY, yVar, xBall, velocityPad, row1, row2);
    velocityX = getVX(xBall, velocityX, yBall, yVar, row1, row2);

    //calcualte rows
    calcRow1(row1, xBall, yBall, velocityX, velocityY);
    calcRow2(row2, xBall, yBall, velocityX, velocityY);

    //calculate new ball position
    yBall = ballMoveY(yBall, velocityY);
    xBall = ballMoveX(xBall, velocityX);

    //read joystick and calculate movement/velocity
    yVar = paddleMove(yVar);
    velocityPad = getVPad(lastY,yVar);

    
    // Remember the time
    previousMillisCalc = currentMillis;  
    
    //test for loss & run defeat sequence
    defeat(xBall);
  }
 
  if((component == 1) && (currentMillis - previousMillis >= timer))
  {
    
    // Remember the time
    previousMillis = currentMillis;  
    
    //update the pins & save position
    clearBoard();
    positionDisplayBall(xBall,yBall);
    lastBallX = xBall;
    lastBallY = yBall;

    
    //test for loss & run defeat sequence
    //defeat(xBall);


    component = 2;//changes to paddle next
  }
  else if ((component == 2) &&(currentMillis - previousMillis >= timer))
  {
    
    // Remember the time
    previousMillis = currentMillis;   
    
    //update pins and save position
    clearBoard();
    positionDisplayPaddle(yVar);
    lastY = yVar;

    component = 3;//changes to row 2
  }
  else if ((component == 3) &&(currentMillis - previousMillis >= timer))
  {
    // Remember the time
    previousMillis = currentMillis;   
    
    //update pins and save position
    clearBoard();
    displayRow2(row2);

    component = 4;//changes to row 1
  }
  else if ((component == 4) &&(currentMillis - previousMillis >= timer))
  {
    // Remember the time
    previousMillis = currentMillis;   
    
    //update pins and save position
    clearBoard();
    displayRow1(row1);

    component = 1;//changes to ball
  }

  if((calcTime > 50)&&(currentMillis - previousMillisSpeed >= 5000))//acceleration code
  {
  
    calcTime--; //decrement of calcTime increases net speed of game 
    //faster games are more difficult so gradual increase of difficult w/ longer game
    
    // Remember the time
    previousMillisSpeed = currentMillis;  
  }
 
}


