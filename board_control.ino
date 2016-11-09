//Maddy McGee 6/7/16
//Uses potentiometer joystick to move one LED on in both X
//and Y directions

const int X_pinA = 4; // analog pin connected to X output for joystick A
const int Y_pinA = 5; // analog pin connected to Y output for joystick A
const int xValue[8] = {0,1,2,3,4,5,6,14}; //on when HIGH
const int yValue[8] = {7,8,9,10,11,12,13,15}; // on when LOW
int lastX = 0;
int xVar = 0;
int yVar = 0;
int lastY = 0;
// value 14 is analog A0 and 15 is analog A1

//methods start
void positionDisplay(int x,int y)
{
  //x-value 
  digitalWrite(xValue[x],HIGH);
  //y-value
  digitalWrite(yValue[y],LOW);
}

void clearLast(int Y,int X)
{
  //last x off
  digitalWrite(xValue[X],LOW);
  //last y off
  digitalWrite(yValue[Y],HIGH);
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
}

void loop() 
{
  if (analogRead(X_pinA)< 212)
  {
    if (yVar < 7)
    {
      yVar ++;
    }
  }
  else
  {
    if (analogRead(X_pinA) > 812)
    {
      if(yVar > 0)
      {
        yVar --;
      }
    }
  }
  if (analogRead(Y_pinA)< 212)
  {
    if (xVar < 7)
    {
      xVar ++;
    }
  }
  else
  {
    if (analogRead(Y_pinA) > 812)
    {
      if(xVar > 0)
      {
        xVar --;
      }
    }
  }
  clearLast(lastY,lastX);
  positionDisplay(xVar,yVar);
  lastY = yVar;
  lastX = xVar;
  delay(50);
}


