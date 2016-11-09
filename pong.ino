//Maddy McGee 10/14/16
//A game of single player pong for the 8x8 display using a joystick potentiometer
//Uses displays

const int X_pinA = 4; // analog pin connected to X output for joystick A
const int Y_pinA = 5; // analog pin connected to Y output for joystick A
const int xValue[8] = {0,1,2,3,4,5,6,14}; //on when HIGH
const int yValue[8] = {7,8,9,10,11,12,13,15}; // on when LOW
// value 14 is analog A0 and 15 is analog A1
int yVar = 4;
int lastY = 0;
int xBall = 3;
int yBall = 4;
int lastBallX = 3;
int lastBallY = 4;
int velocityX = 1;
int velocityY = 0;
int velocityPad;

//methods start
void positionDisplayPaddle(int y) //displays paddle as a 1x3 shape at xValue[7] with the given Y-value in the middle
{
  //y-value
  digitalWrite(yValue[y],LOW);
  digitalWrite(yValue[y+1],LOW);
  digitalWrite(yValue[y-1],LOW);
  digitalWrite(xValue[7],HIGH);
}

/*void clearLastPaddle(int Y)
{
  //last y off -> entire board should be off
  digitalWrite(yValue[Y],HIGH);
  digitalWrite(yValue[Y+1],HIGH);
  digitalWrite(yValue[Y-1],HIGH);
  digitalWrite(xValue[7],LOW);
}*/

void positionDisplayBall(int x,int y)
{
  digitalWrite(xValue[x], HIGH);
  digitalWrite(yValue[y], LOW);
}

/*void clearLastBall(int x, int y)
{
  digitalWrite(xValue[x], LOW);
  digitalWrite(yValue[y], HIGH);
}*/
void clearBoard()
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

int ballMoveX(int ball, int v)
{
  if (ball >= 0)
  {
    ball += v;
  }
  return ball;
}

int getVPad(int last, int y)
{
  return y-last;
}

int ballMoveY(int ball, int v)
{
  if (! ((v<0 && ball == 0) || (v>0 && ball == 7)))
  {
    ball += v;
  }
  return ball;
}

int getVX(int ball,int v, int ballY, int padY)
{
  if ((ball == 6) && (ballY == padY || ballY == padY+1 || ballY == padY-1))//deflect ball if at paddle
  {
      v = -1;
  }
  if (ball == 0)//deflect on wall
  {
    v = 1;
  }
  return v;
}

int getVY(int ballY,int v, int pad, int ballX, int vp)
{
  
  if ((ballX == 6) && (ballY == pad || ballY == pad+1 || ballY == pad-1))//deflection at paddle
  {
    v = vp;
    /*if (ballY == pad)//no verticle deflect if ball in center of paddle 
    {
      v = 0;
    }
    if (ballY == pad +1)//deflect up if ball at top of paddle
    {
      v = 1;
    }
    if (ballY == pad -1)//deflect down in ball at bottom of paddle
    {
      v = -1;
    }*/ //this code is physics based on ball's location relative to paddle, and is independant from paddle velocity
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
  lastY = 0;
  xBall = 3;
  yBall = 4;
  lastBallX = 3;
  lastBallY = 4;
  velocityX = 1;
  velocityY = 0;
  
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
  for (int cnt = 12; cnt >0; cnt--)
  {
  clearBoard();
  yVar = paddleMove(yVar);
  positionDisplayPaddle(yVar);
  lastY = yVar;
  delay(50);
  clearBoard();
  positionDisplayBall(3,4);
  delay(50);
  }
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
  
  //display paddle
  //clearLastPaddle(lastY);
  //clearLastBall(lastBallX,lastBallY);
  clearBoard();
  yVar = paddleMove(yVar);
  positionDisplayPaddle(yVar);
  velocityPad = getVPad(lastY,yVar);
  lastY = yVar;
  delay(50);

  //display ball
  clearBoard();
  //clearLastPaddle(lastY);
  //clearLastBall(lastBallX,lastBallY);
  velocityY = getVY(yBall, velocityY, yVar, xBall, velocityPad);
  velocityX = getVX(xBall, velocityX, yBall, yVar);
  yBall = ballMoveY(yBall, velocityY);
  xBall = ballMoveX(xBall, velocityX);
  positionDisplayBall(xBall,yBall);
  lastBallX = xBall;
  lastBallY = yBall;

  
  defeat(xBall);
  delay(50);
}


