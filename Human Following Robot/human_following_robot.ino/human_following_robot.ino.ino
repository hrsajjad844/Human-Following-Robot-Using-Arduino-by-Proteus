@hrsajjad844
#include<Servo.h>
#include<AFMotor.h>
#define LEFT A0
#define echopin A1 // echo pin
#define trigpin A2 // Trigger pin
#define RIGHT A3

AF_DCMotor Motor1(1,MOTOR12_1KHZ);
AF_DCMotor Motor2(2,MOTOR12_1KHZ);
AF_DCMotor Motor3(3,MOTOR34_1KHZ);
AF_DCMotor Motor4(4,MOTOR34_1KHZ);

Servo myservo;
 
int pos =0;
long time;

void setup(){

Serial.begin(9600);
myservo.attach(10);

for(pos = 90; pos <= 180; pos += 1){
myservo.write(pos);
delay(15);
}
 
for(pos = 180; pos >= 0; pos-= 1) {
myservo.write(pos);
delay(15);
}

for(pos = 0; pos<=90; pos += 1) {
myservo.write(pos);
delay(15);
}

pinMode(RIGHT, INPUT);
pinMode(LEFT, INPUT);

pinMode(trigpin, OUTPUT);
pinMode(echopin, INPUT);

}

void loop(){
unsigned int distance = read_cm();

int Right_Value = digitalRead(RIGHT);
int Left_Value  = digitalRead(LEFT);

Serial.print("R= ");
Serial.print(Right_Value);
Serial.print(" L= ");
Serial.print(Left_Value);
Serial.print(" D= ");
Serial.println(distance);

     if((Right_Value==1) && (distance>=10 && distance<=30)&&(Left_Value==1)){forword();}
else if((Right_Value==0) && (Left_Value==1)){turnRight();}
else if((Right_Value==1) && (Left_Value==0)){turnLeft();}
else if((Right_Value==1) && (Left_Value==1)){stop();}
else if(distance > 5 && distance < 10){stop();}
else if(distance < 5){backword();}

delay(50);
}

long read_cm(){
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  time = pulseIn (echopin, HIGH);
  return time / 29 / 2;
}

void forword(){// turn it on going forward
Motor1.setSpeed(120);
Motor1.run(FORWARD);
Motor2.setSpeed(120);
Motor2.run(FORWARD);
Motor3.setSpeed(120);
Motor3.run(FORWARD);
Motor4.setSpeed(120);
Motor4.run(FORWARD);
}

void backword(){ // the other way
Motor1.setSpeed(120);
Motor1.run(BACKWARD); 
Motor2.setSpeed(120);
Motor2.run(BACKWARD);
Motor3.setSpeed(120);
Motor3.run(BACKWARD); 
Motor4.setSpeed(120);
Motor4.run(BACKWARD); 
}

void turnRight(){ // the other right
Motor1.setSpeed(200);
Motor1.run(FORWARD);
Motor2.setSpeed(200);
Motor2.run(FORWARD);
Motor3.setSpeed(100);
Motor3.run(BACKWARD);
Motor4.setSpeed(100);
Motor4.run(BACKWARD);
}

void turnLeft(){ // turn it on going left
Motor1.setSpeed(100);
Motor1.run(BACKWARD);
Motor2.setSpeed(100);
Motor2.run(BACKWARD);
Motor3.setSpeed(200);
Motor3.run(FORWARD);
Motor4.setSpeed(200);
Motor4.run(FORWARD);
}

void stop(){ // stopped
Motor1.setSpeed(0);  
Motor1.run(RELEASE);
Motor2.setSpeed(0);
Motor2.run(RELEASE);
Motor3.setSpeed(0);
Motor3.run(RELEASE);
Motor4.setSpeed(0);
Motor4.run(RELEASE);  
}
