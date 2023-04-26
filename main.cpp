#include <Arduino.h>

#define SW_DOWN 8
#define SW_LEFT 9
#define SW_RIGHT 10
#define SW_UP 11

// Global Variables
int UP = 0;
int DOWN = 0;
int LEFT = 0;
int RIGHT = 0;
int speed = 0;
char Sensor[7];
String SR;
String SL;
boolean messageUP = false;
boolean messageRIGHT = false;
boolean messageLEFT = false;
boolean messageVirar = false;
boolean parar = false;
boolean avanca = false;
int oldvelR = 0;
int oldvelL = 0;
int velR;
int velL;

// Prototypes
void advance();
void Read_sw();
void moveAuto();
void read_Sensors();

// Functions

// char CustomDelay(int ms)
// {
//   for (int i = 0; i < ms; i++)
//   {
//     delay(1);

//   }
//   return 'n';
// }

void read_Sensors()
{
  Read_sw();
  for (byte i = 0; i < 5; i++)
  {
    if (Serial.available() > 0)
    {
      Sensor[i] = Serial.read();
      Read_sw();
      if (UP == 1 && avanca == false)
      {
        Serial.print("m");
        Serial.print(9);
        Serial.print(9);
        avanca = true;
        parar = false;
      }
      if (DOWN == 1 && parar == false)
      {
        Serial.print("m");
        Serial.print(0);
        Serial.print(0);
        parar = true;
        avanca = false;
      }
    }
    else
    {
      i--;
      Read_sw();
      if (UP == 1 && avanca == false)
      {
        Serial.print("m");
        Serial.print(9);
        Serial.print(9);
        avanca = true;
        parar = false;
      }
      if (DOWN == 1 && parar == false)
      {
        Serial.print("m");
        Serial.print(0);
        Serial.print(0);
        parar = true;
        avanca = false;
      }
      // if (messageUP == false && messageVirar == false && parar == false && messageLEFT == false && messageRIGHT == false)
      // {
      //   Serial.print("m");
      //   Serial.print(9);
      //   Serial.print(9);
      //   messageUP = true;
      //   messageLEFT = false;
      //   messageRIGHT = false;
      // }
    }
  }

  if (Sensor[0] == 'R' && parar == false)
  {
    String SensorR;
    for (byte r = 1; r < 5; r++)
    {
      SensorR += Sensor[r];
    }
    SR = SensorR;
    if (SR.toDouble() > 0.24)
    {
      SR = "0.30";
    }
    moveAuto();
  }

  if (Sensor[0] == 'L' && parar == false)
  {
    String SensorL;
    for (byte l = 1; l < 5; l++)
    {
      SensorL += Sensor[l];
    }
    SL = SensorL;
    if (SL.toDouble() > 0.24)
    {
      SL = "0.30";
    }
    moveAuto();
  }
}

void moveAuto()
{

  // Right
  if (Sensor[0] == 'R')
  {

    if (SR.toDouble() < 0.23 && parar == false)
    {
      if (35 * SR.toDouble() + 1 > 9)
      {
        velR = 8;
      }
      else
      {
        velR = (35 * SR.toDouble() + 1);
      }
      if (oldvelR != velR)
      {
        oldvelR = velR;
        Serial.print("m");
        Serial.print(9);
        Serial.print(velR);
        messageRIGHT = true;
        messageUP = false;
        messageLEFT = false;
      }
    }

    if (SR.toDouble() >= 0.25 && messageUP == false && messageLEFT == false && parar == false)
    {
      Serial.print("m");
      Serial.print(9);
      Serial.print(9);
      messageUP = true;
      messageRIGHT = false;
      messageLEFT = false;
    }
  }

  // Left
  if (Sensor[0] == 'L')
  {

    if (SL.toDouble() < 0.23 && parar == false)
    {
      if (35 * SL.toDouble() + 1 > 9)
      {
        velL = 8;
      }
      else
      {
        velL = (35 * SL.toDouble() + 1);
      }
      if (oldvelL != velL)
      {
        oldvelL = velL;
        Serial.print("m");
        Serial.print(velL);
        Serial.print(9);
        messageLEFT = true;
        messageUP = false;
        messageRIGHT = false;
      }
    }

    if (SL.toDouble() >= 0.25 && messageUP == false && messageRIGHT == false && parar == false)
    {
      Serial.print("m");
      Serial.print(9);
      Serial.print(9);
      messageUP = true;
      messageLEFT = false;
      messageRIGHT = false;
    }
  }

  if (messageVirar == false && parar == false && SR.toDouble() < 0.15 && SR.toDouble() >= 0.1 && SL.toDouble() < 0.15 && SL.toDouble() >= 0.1)
  {

    Serial.print("m");
    Serial.print(9);
    Serial.print(-7);
    messageVirar = true;
    messageRIGHT = false;
    messageUP = false;
    messageLEFT = false;
    delay(850);
  }
}

void Read_sw()
{
  UP = digitalRead(11);
  DOWN = digitalRead(8);
  LEFT = digitalRead(9);
  RIGHT = digitalRead(10);
}

// void advance()
// {
//   while (1)
//   {
//     delay(200);
//     Read_sw();
//     if (UP == 1)
//     {
//       if (speed < 9)
//       {
//         speed++;
//       }
//       Serial.print("m");
//       Serial.print(speed);
//       Serial.print(speed);
//     }
//     else if (DOWN == 1)
//     {
//       speed--;
//       Serial.print("m");
//       Serial.print(speed);
//       Serial.print(speed);
//     }
//     else if (LEFT == 1)
//     {
//       Serial.print("m");
//       Serial.print(speed);
//       Serial.print(speed - 1);
//       delay(150);
//       Serial.print("m");
//       Serial.print(speed);
//       Serial.print(speed);
//     }
//     else if (RIGHT == 1)
//     {
//       Serial.print("m");
//       Serial.print(speed - 1);
//       Serial.print(speed);
//       delay(150);
//       Serial.print("m");
//       Serial.print(speed);
//       Serial.print(speed);
//     }
//   }
// }

void setup()
{
  // put your setup code here, to run once:

  // Input
  pinMode(SW_DOWN, INPUT);
  pinMode(SW_LEFT, INPUT);
  pinMode(SW_RIGHT, INPUT);
  pinMode(SW_UP, INPUT);

  Serial.begin(9600);
}

void loop()
{
  // put your main code here, to run repeatedly:
  // Read_sw();
  read_Sensors();

  // advance();
}