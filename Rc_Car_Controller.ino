/*  L298N_Dual_H_Bridge

This program controls 2 separate DC motors using the L298N 
H Bridge Chip. 

The controls would be controlled based on inputs recieved by bluetooth from an android device

          *THE SUBROUTINES WORK AS FOLLOWS*

motorA(mode, speed)
% replace A with B to control motor B %

mode is a number 0 -> 3 that determines what the motor 
will do.
0 = coast/disable the H bridge
1 = turn motor clockwise
2 = turn motor counter clockwise
3 = brake motor

speed is a number 0 -> 100 that represents percentage of
motor speed.
0 = off
50 = 50% of full motor speed
100 = 100% of full motor speed

EXAMPLE
Say you need to have motor A turn clockwise at 33% of its
full speed.  The subroutine call would be the following...
motorA(1, 33);
*/

#define ENA 6  //enable A on pin 6 (needs to be a pwm pin)
#define ENB 5  //enable B on pin 5 (needs to be a pwm pin)
#define IN1 2  //IN1 on pin 2 conrtols one side of bridge A
#define IN2 3  //IN2 on pin 3 controls other side of A
#define IN3 7  //IN3 on pin 7 conrtols one side of bridge B
#define IN4 8  //IN4 on pin 8 controls other side of B

#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX
char incomingByte;  // incoming data

void setup()
{
    // Open serial communications and wait for port to open:
  Serial.begin(57600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("Press 1 for LED ON or 0 for LED OFF");
  //set all pins for the L298N as outputs
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  if (mySerial.available() > 0) {  // if the data came
    incomingByte = mySerial.read(); // read byte
    //  move forward
    if(incomingByte == '0'){ 
       motorA(1, 100);  //have motor A turn clockwise at 100% speed
       motorB(1, 100);  //have motor B turn clockwise at 100% speed
      delay(20000);
      motorA(3,50);
      delay(10000);
      motorB(3,30);
      delay(10000); 
        //drive_forward();
    }
    
    // move backward
     else if(incomingByte == '1') {
      motorA(2, 100);  //have motor A turn counter-clockwise at 100% speed
      motorB(1, 100);  //have motor B turn counter-clockwise at 100% speed
      delay(20000);
      motorA(3,50);
      delay(10000);
      motorB(3,30);
      delay(10000); 
       // drive_backward();
     }
     
     //turn left
     else if (incomingByte == '2'){
         //turn_left();
     }
     
     //turn right
      else if (incomingByte == '3'){
          //turn_right();
      }
  } 
}

//******************   Motor A control   *******************
void motorA(int mode, int percent)
{
  
  //change the percentage range of 0 -> 100 into the PWM
  //range of 0 -> 255 using the map function
  int duty = map(percent, 0, 100, 0, 255);
  
  switch(mode)
  {
    case 0:  //disable/coast
      digitalWrite(ENA, LOW);  //set enable low to disable A
      break;
      
    case 1:  //turn clockwise
      //setting IN1 high connects motor lead 1 to +voltage
      digitalWrite(IN1, HIGH);   
      
      //setting IN2 low connects motor lead 2 to ground
      digitalWrite(IN2, LOW);  
      
      //use pwm to control motor speed through enable pin
      analogWrite(ENA, duty);  
      
      break;
      
    case 2:  //turn counter-clockwise
      //setting IN1 low connects motor lead 1 to ground
      digitalWrite(IN1, LOW);   
      
      //setting IN2 high connects motor lead 2 to +voltage
      digitalWrite(IN2, HIGH);  
      
      //use pwm to control motor speed through enable pin
      analogWrite(ENA, duty);  
      
      break;
      
    case 3:  //brake motor
      //setting IN1 low connects motor lead 1 to ground
      digitalWrite(IN1, LOW);   
      
      //setting IN2 high connects motor lead 2 to ground
      digitalWrite(IN2, LOW);  
      
      //use pwm to control motor braking power 
      //through enable pin
      analogWrite(ENA, duty);  
      
      break;
  }
}
//**********************************************************


//******************   Motor B control   *******************
  void motorB(int mode, int percent)
{
  
  //change the percentage range of 0 -> 100 into the PWM
  //range of 0 -> 255 using the map function
  int duty = map(percent, 0, 100, 0, 255);
  
  switch(mode)
  {
    case 0:  //disable/coast
      digitalWrite(ENB, LOW);  //set enable low to disable B
      break;
      
    case 1:  //turn clockwise
      //setting IN3 high connects motor lead 1 to +voltage
      digitalWrite(IN3, HIGH);   
      
      //setting IN4 low connects motor lead 2 to ground
      digitalWrite(IN4, LOW);  
      
      //use pwm to control motor speed through enable pin
      analogWrite(ENB, duty);  
      
      break;
      
    case 2:  //turn counter-clockwise
      //setting IN3 low connects motor lead 1 to ground
      digitalWrite(IN3, LOW);   
      
      //setting IN4 high connects motor lead 2 to +voltage
      digitalWrite(IN4, HIGH);  
      
      //use pwm to control motor speed through enable pin
      analogWrite(ENB, duty);  
      
      break;
      
    case 3:  //brake motor
      //setting IN3 low connects motor lead 1 to ground
      digitalWrite(IN3, LOW);   
      
      //setting IN4 high connects motor lead 2 to ground
      digitalWrite(IN4, LOW);  
      
      //use pwm to control motor braking power 
      //through enable pin
      analogWrite(ENB, duty);  
      
      break;
  }
}

void drive_forward(){
  //right motor move clockwise
  //left motor move counterclockwise
   motorA(2, 100);  //have motor A turn counter-clockwise at 100% speed
   motorB(1, 100);  //have motor B turn clockwise at 100% speed
   delay(20000);
}

void drive_backward(){
    //right motor move clockwise
  //left motor move counterclockwise
   motorA(1, 100);  //have motor A turn clockwise at 100% speed
   motorB(2, 100);  //have motor B turn counter-clockwise at 100% speed
   delay(20000);
}
//**********************************************************
