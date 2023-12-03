//Working with 4.5[V]
#include <AFMotor.h>
//Functions
void forward(int motornumber);
void stops();
void backward(int motornumber);
//Not using M3 and M4 on the OWI arm
//Using M5,2,1
//+M1 --> Blue Wire on conveyor
//FORWARD is toward motor
AF_DCMotor motorConveyor(1); //Conveyor is on M1 on motor driver. 

//+M2 --> Yellow wire on OWI Gripper
//FORWARD = Closing gripper
AF_DCMotor motor2(2);// M1 on OWI (Gripper) is on M2 on motor driver.

//+M3 -->Orange wire on OWI Base
//-M3 -->Black on OWI Base
AF_DCMotor motor3(3); //M5 on OWI(Base Rotation)is on M3 on motor driver

//ignore
AF_DCMotor motor4(4); //M5 on OWI (Base Rotation) is on M4 on motor driver. Forward = Counterclock
//only be moving motor 3 and motor 1 and motor 2
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;
boolean go = 1;
void setup() {
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  
  
  if (Serial.available() > 0 && go ==1) {
    char color = Serial.read();
   // Serial.flush();
 
if(color == 'r'){
    go=0;
    forward(1); //moves conveyor
    delay(800);
    stops();
    delay(1000);
    
    forward(2);//closes gripeer
    delay(2000);
    stops();
    delay(1000);
    
    backward(3);//moves the base rotation clockwise
    delay(2000);
    stops();
    delay(1000);

    backward(2);//opens gripper
    delay(1800);
    stops();
    delay(1000);
    
    //Time to reset
    forward(3);//moves the base rotation clockwise
    delay(2000);
    stops();
    delay(1000);
    go=1;
}
 else if(color == 'g'){
  go=0;
      forward(1); //moves conveyor
    delay(800);
    stops();
    delay(1000);
    
    forward(2);//closes gripeer
    delay(2000);
    stops();
    delay(1000);
    
    backward(3);//moves the base rotation clockwise
    delay(4000);
    stops();
    delay(1000);

    backward(2);//opens gripper
    delay(1800);
    stops();
    delay(1000);
    
    //Time to reset
    forward(3);//moves the base rotation clockwise
    delay(4000);
    stops();
    delay(1000);
    go=1;
}

 else if(color == 'b'){
  go=0;
         forward(1); //moves conveyor
    delay(800);
    stops();
    delay(1000);
    
    forward(2);//closes gripeer
    delay(2000);
    stops();
    delay(1000);
    
    backward(3);//moves the base rotation clockwise
    delay(6000);
    stops();
    delay(1000);

    backward(2);//opens gripper
    delay(1800);
    stops();
    delay(1000);
    
    //Time to reset
    forward(3);//moves the base rotation clockwise
    delay(6100);
    stops();
    delay(1000);
    go=1;
}

    


}
}

void forward(int motornumber)
{
  switch(motornumber){
  case 1:
  motorConveyor.setSpeed(255);
  motorConveyor.run(FORWARD);
  break;
  case 2:
  motor2.setSpeed(255);
  motor2.run(FORWARD);
  break;
  case 3:
  motor3.setSpeed(255);
  motor3.run(FORWARD);
  break;  
  case 4:
  motor4.setSpeed(255);
  motor4.run(FORWARD);
  default:
  break;
  }
}

void backward(int motornumber)
{
    switch(motornumber){
  case 1:
  motorConveyor.setSpeed(255);
  motorConveyor.run(BACKWARD);
  break;
  case 2:
  motor2.setSpeed(255);
  motor2.run(BACKWARD);
  break;
  case 3:
  motor3.setSpeed(255);
  motor3.run(BACKWARD);
  break;  
  case 4:
  motor4.setSpeed(255);
  motor4.run(BACKWARD);
  default:
  break;
  }

}


void stops()
{
  
  motorConveyor.run(RELEASE);

  motor2.run(RELEASE);

  motor3.run(RELEASE);

  motor4.run(RELEASE);
}