//Maddy McGee 10/23/16
//Same logic as the pong code except optimized to run without the use of delays with 
//the padTime and ballTime variables representing the time in the millis function 
//which the 'ball' or 'paddle' are displayed

//ball and paddle must alternate because the board can not display the game correctly otherwise
//the millis() function replacing the delay reduces the strobe time allowing the game to 
//stobe less visibly to the human eye

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
unsigned long previousMillis = 0;//timer for display
unsigned long previousMillisCalc = 0;//timer for calculation
unsigned long previousMillisSpeed;//decrement calcTime to increase net speed
long ballTime = 10;
long padTime = 10;
long calcTime = 85;//initial game speed

boolean isBall = true; //alternate ball & paddle display variable

//methods start
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

int getVX(int ball,int v, int ballY, int padY) //calculates ball's X velocity
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

int getVY(int ballY,int v, int pad, int ballX, int vp) //calculates ball's Y velocity
{
  
  if ((ballX == 6) && (ballY == pad || ballY == pad+1 || ballY == pad-1))//deflection at paddle
  {
    v = vp;
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
 
  if((isBall) && (currentMillisReset - previousMillisReset >= ballTime))
  {
    // Remember the time
    previousMillisReset = currentMillisReset;  
    
    //update the pins & save position
    clearBoard();
    positionDisplayBall(3,4);
    
    isBall = false;//changes to paddle next
    cnt--; //countdown to end loop
  }
  else if ((!isBall) &&(currentMillisReset - previousMillisReset >= padTime))
  {
    
    // Remember the time
    previousMillisReset = currentMillisReset;   
    
    //update pins and save position
    clearBoard();
    positionDisplayPaddle(yVar);
    lastY = yVar;

    isBall = true;//changes to ball next
    cnt--;//countdown to end loop
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
  
    //calculate ball
    velocityY = getVY(yBall, velocityY, yVar, xBall, velocityPad);
    velocityX = getVX(xBall, velocityX, yBall, yVar);
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
 
  if((isBall) && (currentMillis - previousMillis >= ballTime))
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


    isBall = false;//changes to paddle next
  }
  else if ((!isBall) &&(currentMillis - previousMillis >= padTime))
  {
    
    // Remember the time
    previousMillis = currentMillis;   
    
    //update pins and save position
    clearBoard();
    positionDisplayPaddle(yVar);
    lastY = yVar;

    isBall = true;//changes to ball next
  }

  if((calcTime > 50)&&(currentMillis - previousMillisSpeed >= 5000))
  {
  
    calcTime--; //decrement of calcTime increases net speed of game 
    //faster games are more difficult so gradual increase of difficult w/ longer game
    
    // Remember the time
    previousMillisSpeed = currentMillis;  
  }
 
}


