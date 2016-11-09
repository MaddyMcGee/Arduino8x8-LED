//Maddy McGee 5/23/16
//Uses potentiometer joystick to move a 'pong' paddle up and 
//down

// Arduino pin numbers
const int SW_pinA = 2; // digital pin connected to switch output for joystick A
const int SW_pinB = 3; // digital pin connected to switch output for joystick B
const int X_pinA = 4; // analog pin connected to X output for joystick A
const int X_pinB = 2; // analog pin connected to X output for joystick B
const int Y_pinA = 5; // analog pin connected to Y output for joystick A
const int Y_pinB = 3; // analog pin connected to Y output for joystick B
int AX,AY,BX,BY;
 
void setup() 
{
  pinMode(SW_pinA, INPUT);
  digitalWrite(SW_pinA, HIGH);
  pinMode(SW_pinB, INPUT);
  digitalWrite(SW_pinB, HIGH);
  Serial.begin(9600);
  /*Serial.print("Switch A:  ");
  Serial.println(digitalRead(SW_pinA));
  Serial.print("X-axis A: ");
  Serial.println(analogRead(X_pinA));
  Serial.print("Y-axis A: ");
  Serial.println(analogRead(Y_pinA));
  Serial.print("Switch B:  ");
  Serial.println(digitalRead(SW_pinB));
  Serial.print("X-axis B: ");
  Serial.println(analogRead(X_pinB));
  Serial.print("Y-axis B: ");
  Serial.println(analogRead(Y_pinB));
  Serial.print("\n\n"); */
}
 
void loop() 
{
  AX=1;
  AY=1;
  BX=1;
  BY=1;
  Serial.print("Joystick A:");
  if (analogRead(X_pinA)< 212)
  {
    Serial.print("forward ");
  }
  else
  {
    if (analogRead(X_pinA) > 812)
    {
      Serial.print("backward ");
    }
    else
    {
      AX=0;
    }
  }
  if (analogRead(Y_pinA)< 212)
  {
    Serial.print("right ");
  }
  else
  {
    if (analogRead(Y_pinA) > 812)
    {
      Serial.print("left ");
    }
    else
    {
      AY=0;
    }
  }
  if(AX==0 && AY==0)
  {
    Serial.print("center ");
  }
  if (digitalRead(SW_pinA) == LOW)
  {
    Serial.println("on");
  }
  else
  {
    Serial.println("off");
  }
  
  Serial.print("Joystick B:");
  if (analogRead(X_pinB)< 212)
  {
    Serial.print("forward ");
  }
  else
  {
    if (analogRead(X_pinB) > 812)
    {
      Serial.print("backward ");
    }
    else
    {
      BX=0;
    }
  }
  if (analogRead(Y_pinB)< 212)
  {
    Serial.print("right ");
  }
  else
  {
    if (analogRead(Y_pinB) > 812)
    {
      Serial.print("left ");
    }
    else
    {
      BY=0;
    }
  }
  if(BX==0 && BY==0)
  {
    Serial.print("center ");
  }
  if (digitalRead(SW_pinB) == LOW)
  {
    Serial.println("on");
  }
  else
  {
    Serial.println("off");
  }
  delay(5000);
}
