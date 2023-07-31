#include <Servo.h>. 

Servo myServo1; 
//Servo myServo2; 
const int trigPin1  = 8 ;
const int echoPin1  = 9 ;
const int trigPin2  = 10 ;
const int echoPin2  = 11 ;
const int maxCount  = 5;
const int LED_RED   = 7;
const int LED_GREEN = 6;
const int LR= 0;
const int closeAngle = 0;
const int openAngle = 90;
long durationInt ;
long durationOut ;
int distanceInt ;
int distanceOut ;
int contador = 0;
bool aforoState = 0;
bool securityState = 0;  
int maxDistance = 15;   //cm
int minDistance = 5;    //cm
int waitingTime = 1300;  //ms


void setup(){
  pinMode(trigPin1, OUTPUT); 
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT); 
  pinMode(echoPin2, INPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  Serial.begin(9600);
  myServo1.attach(12);
}

void loop(){
  int ledValue = analogRead(LR);
  Serial.println(ledValue);
  if (ledValue >= 550) {
    securityState = 1;
  } else {
    securityState = 0;
  }
  if (securityState) {
    Serial.print("Hay ");
    Serial.print(contador);
    Serial.print(" personas");
    Serial.println("");
    delay(20);
    countPerson();
    delay(20);
    outPerson();
    delay(20);
    intPerson();
    delay(20);
  } else {
    Serial.println("///////ALERTA///////");
    delay(2000);
    digitalWrite(LED_RED,LOW);
    digitalWrite(LED_GREEN,LOW);
    myServo1.write(closeAngle);
  }
}

int calculateDistanceInt(){ 
  digitalWrite(trigPin1, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  durationInt = pulseIn(echoPin1, HIGH); 
  distanceInt= durationInt*0.034/2;
  return distanceInt;
}

int calculateDistanceOut(){ 
  digitalWrite(trigPin2, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  durationOut = pulseIn(echoPin2, HIGH); 
  distanceOut = durationOut*0.034/2;
  return distanceOut;
}

void intPerson(){
  if (calculateDistanceInt() <= maxDistance && !aforoState){
    Serial.println("Entrando...");
    delay(20);
    myServo1.write(openAngle);
    delay(waitingTime);
    if (calculateDistanceInt()<= minDistance){
      delay(waitingTime/2);
      if (calculateDistanceOut()<= minDistance){
        Serial.println("Pasó 1 persona");
        contador += 1;
        delay(20);        
      } else {
        myServo1.write(closeAngle);
        Serial.println("No entró...");
      } 
    } else {
      myServo1.write(closeAngle);
      Serial.println("No entró...");
    }
  }
}

void outPerson(){
  if (calculateDistanceOut() <= maxDistance){
    Serial.println("Saliendo...");
    delay(20);
    myServo1.write(openAngle);
    delay(waitingTime);
    if (calculateDistanceOut()<= minDistance){
      delay(waitingTime/2);
      if (calculateDistanceInt()<= minDistance){
        Serial.println("Salió 1 persona");
        contador -= 1;
        delay(20);        
      } else {
        myServo1.write(closeAngle);
        Serial.println("No salió...");
      } 
    } else {
      myServo1.write(closeAngle);
      Serial.println("No salió...");
    }
  }
}

void countPerson (){
  if (contador == maxCount){
    delay(20);
    myServo1.write(closeAngle);
    Serial.println("Aforo a full capacidad");
    delay(20);
    digitalWrite(LED_RED,HIGH);
    delay(20);
    digitalWrite(LED_GREEN,LOW);
    delay(20);
    aforoState = 1;
  } else{
    digitalWrite(LED_GREEN,HIGH);
    delay(20);
    digitalWrite(LED_RED,LOW);
    delay(20);
    aforoState = 0;
  }
}