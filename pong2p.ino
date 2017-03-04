//Maddy McGee 10/23/16
//Pong for 2 people

const int X_pinA = 4; // analog pin connected to X output for joystick A
const int X_pinB = 5; // analog pin connected to X output for joystick B
const int xValue[8] = {0,1,2,3,4,5,6,14}; //on when HIGH
const int yValue[8] = {7,8,9,10,11,12,13,15}; // on when LOW
// value 14 is analog A0 and 15 is analog A1
int yVar = 4;
int yVar2 = 4;
int lastY = 0;
int lastY2 = 0;
int xBall = 3;
int yBall = 4;
int lastBallX = 3;
int lastBallY = 4;
int velocityX = 1;
int velocityY = 0;
int velocityPad;
int velocityPad2;
unsigned long previousMillis = 0;//timer for display
unsigned long previousMillisCalc = 0;//timer for calculation
unsigned long previousMillisSpeed;//decrement calcTime to increase net speed
long ballTime = 8;
long padTime = 8;
long calcTime = 90;//initial game speed

boolean isBall = true; //alternate ball & paddle display variable
boolean isPad2 = false; //adds second paddle to the mix

int pts1; //player one points, controller of paddle/paddle one on right
int pts2;//player two points, controller of paddle two on left
//methods start
void positionDisplayPaddle(int y) //displays paddle as a 1x3 shape at xValue[7] with the given Y-value in the middle
{
  //y-value
  digitalWrite(yValue[y],LOW);
  digitalWrite(yValue[y+1],LOW);
  digitalWrite(yValue[y-1],LOW);
  digitalWrite(xValue[7],HIGH);
}

void positionDisplayPaddle2(int y) //displays paddle as a 1x3 shape at xValue[7] with the given Y-value in the middle
{
  //y-value
  digitalWrite(yValue[y],LOW);
  digitalWrite(yValue[y+1],LOW);
  digitalWrite(yValue[y-1],LOW);
  digitalWrite(xValue[0],HIGH);
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

int paddleMove2(int b) 
{
  //joystick control of paddle
  if (analogRead(X_pinB)< 212)
  {
    if (b < 6)
    {
      b ++;
    }
  }
    if (analogRead(X_pinB) > 812)
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

int getVX(int ball,int v, int ballY, int padY, int padY2) //calculates ball's X velocity
{
  if ((ball == 6) && (ballY == padY || ballY == padY+1 || ballY == padY-1))//deflect ball if at paddle
  {
      v = -1;
  }
  if ((ball == 1) && (ballY == padY2 || ballY == padY2+1 || ballY == padY2-1))//deflect ball at paddle two
  {
    v = 1;
  }
  return v;
}

int getVY(int ballY,int v, int pad, int pad2, int ballX, int vp, int vp2) //calculates ball's Y velocity
{
  
  if ((ballX == 6) && (ballY == pad || ballY == pad+1 || ballY == pad-1))//deflection at paddle
  {
    v = vp;
  }
  if ((ballX == 1) && (ballY == pad2 || ballY == pad2+1 || ballY == pad2-1))//deflection at paddle two
  {
    v = vp2;
  }
  if ( ballY == 7 || ballY == 0)//deflection at walls
  {
    v = -v;
  }
  return v;
}


void reset()
{
  //variable reset
  yVar = 4;
  yVar2 = 4;
  lastY = 0;
  lastY2 = 0;
  xBall = 3;
  yBall = 4;
  lastBallX = 3;
  lastBallY = 4;
  velocityX = 1;
  velocityY = 0;
  calcTime = 85;//speed returned to initial speed
  unsigned long previousMillisReset = 0;
  unsigned long previousMillisResetCalc = 0;
  
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
  positionDisplayPaddle2(4);

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
    yVar2 = paddleMove2(yVar);
    velocityPad = getVPad(lastY,yVar);
    velocityPad2 = getVPad(lastY2, yVar2);
    
    // Remember the time
    previousMillisResetCalc = currentMillisReset; 
  }
 
  if((isBall && !isPad2) && (currentMillisReset - previousMillisReset >= ballTime))
  {
    // Remember the time
    previousMillisReset = currentMillisReset;  
    
    //update the pins & save position
    clearBoard();
    positionDisplayBall(3,4);
    
    isBall = false;
    isPad2 = false;//changes to paddle one next
    cnt--; //countdown to end loop
  }
  else if ((!isBall && !isPad2) &&(currentMillisReset - previousMillisReset >= padTime))
  {
    
    // Remember the time
    previousMillisReset = currentMillisReset;   
    
    //update pins and save position
    clearBoard();
    positionDisplayPaddle(yVar);
    lastY = yVar;

    isBall = false;
    isPad2 = true;//changes to paddle two next
    cnt--;//countdown to end loop
  }
  else if ((!isBall && isPad2) &&(currentMillisReset - previousMillisReset >= padTime))
  {
    
    // Remember the time
    previousMillisReset = currentMillisReset;   
    
    //update pins and save position
    clearBoard();
    positionDisplayPaddle2(yVar2);
    lastY2 = yVar2;

    isBall = true;
    isPad2 = false;//changes to ball next
    cnt--;//countdown to end loop
  }
  
  }//end of reset loop
  
}

void defeat(int d)
{
  if (d == 7)
  {
    pts2 ++;
    if(pts2 >= 9)
    {
      two();
    }
    else
    {
      score();
      reset();
    }
  }
  else if(d == 0)
  {
    pts1 ++;
    if(pts1 >= 9)
    {
      one();
    }
    else
    {
      score();
      reset();
    }
  }
}

void score()
{
  for(int t = 0; t <=10; t++){
  clearBoard();
  digitalWrite(4,HIGH);
  digitalWrite(5,HIGH);
  digitalWrite(6,HIGH);
  digitalWrite(14,HIGH);
  if(pts1 >= 1)
  {
    digitalWrite(7, LOW);
  }
  if(pts1 >= 2)
  {
    digitalWrite(8, LOW);
  }
  if(pts1 >= 3)
  {
    digitalWrite(9, LOW);
  }
  if(pts1 >= 4)
  {
    digitalWrite(10, LOW);
  }
  if(pts1 >= 5)
  {
    digitalWrite(11, LOW);
  }
  if(pts1 >= 6)
  {
    digitalWrite(12, LOW);
  }
  if(pts1 >= 7)
  {
   digitalWrite(13, LOW); 
  }
  if(pts1 == 8)
  {
    digitalWrite(15, LOW);
  }

  delay(50);
  clearBoard();
  digitalWrite(0,HIGH); 
  digitalWrite(1,HIGH);
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  if(pts2 >= 1)
  {
    digitalWrite(7, LOW);
  }
  if(pts2 >= 2)
  {
    digitalWrite(8, LOW);
  }
  if(pts2 >= 3)
  {
    digitalWrite(9, LOW);
  }
  if(pts2 >= 4)
  {
    digitalWrite(10, LOW);
  }
  if(pts2 >= 5)
  {
    digitalWrite(11, LOW);
  }
  if(pts2 >= 6)
  {
    digitalWrite(12, LOW);
  }
  if(pts2 >= 7)
  {
   digitalWrite(13, LOW); 
  }
  if(pts2 == 8)
  {
    digitalWrite(15, LOW);
  }
  delay(50);
  }
  
}

void one()
{
  while(true == true)
  {
  clearBoard();
  digitalWrite(3, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(12, LOW);
  delay(50);
  clearBoard();
  digitalWrite(4,HIGH);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  delay(50);
  clearBoard();
  digitalWrite(5,HIGH);
  digitalWrite(9, LOW);
  delay(50);
  }
}

void two()
{
  while(true == true)
  {
  clearBoard();
  digitalWrite(2,HIGH);
  digitalWrite(5,HIGH);
  digitalWrite(9, LOW);
  digitalWrite(12,LOW);
  delay(50);
  clearBoard();
  digitalWrite(3,HIGH);
  digitalWrite(9,LOW);
  digitalWrite(10, LOW);
  digitalWrite(13, LOW);
  delay(50);
  clearBoard();
  digitalWrite(4, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(11,LOW);
  digitalWrite(13, LOW);
  delay(50);
  }
}

//driver code  
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
  pts1 = 0;
  pts2 = 0;
}

void loop() 
{
  unsigned long currentMillis = millis();
  
  if((currentMillis - previousMillisCalc >= calcTime))
  {
    //calculate ball
    velocityY = getVY(yBall, velocityY, yVar,yVar2, xBall, velocityPad, velocityPad2);
    velocityX = getVX(xBall, velocityX, yBall, yVar, yVar2);
    yBall = ballMoveY(yBall, velocityY);
    xBall = ballMoveX(xBall, velocityX);

    //read joystick and calculate movement/velocity
    yVar = paddleMove(yVar);
    yVar2 = paddleMove2(yVar2);
    velocityPad2 = getVPad(lastY2,yVar2);
    velocityPad = getVPad(lastY,yVar);
    
    // Remember the time
    previousMillisCalc = currentMillis;  
    
    //test for loss & run defeat sequence
    defeat(xBall);
  }
 
  if((isBall && !isPad2) && (currentMillis - previousMillis >= ballTime))
  {
    // Remember the time
    previousMillis = currentMillis;  
    
    //update the pins & save position
    clearBoard();
    positionDisplayBall(xBall,yBall);
    lastBallX = xBall;
    lastBallY = yBall;
    
    isBall = false;
    isPad2 = false;//changes to paddle one next
  }
  else if ((!isBall && !isPad2) &&(currentMillis - previousMillis >= padTime))
  {
    // Remember the time
    previousMillis = currentMillis;   
    
    //update pins and save position
    clearBoard();
    positionDisplayPaddle(yVar);
    lastY = yVar;

    isBall = false;
    isPad2 = true;//paddle two displayed next
  }
  else if ((!isBall && isPad2) &&(currentMillis - previousMillis >= padTime))
  {
    // Remember the time
    previousMillis = currentMillis;   
    
    //update pins and save position
    clearBoard();
    positionDisplayPaddle2(yVar2);
    lastY2 = yVar2;

    isBall = true;
    isPad2 = false;//ball displayed next
  }

  if((calcTime > 60)&&(currentMillis - previousMillisSpeed >= 5000))
  {
    calcTime--; //decrement of calcTime increases net speed of game 
    //faster games are more difficult so gradual increase of difficult w/ longer game
    
    // Remember the time
    previousMillisSpeed = currentMillis;  
  } 
}


