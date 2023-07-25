#include <Servo.h>. 

const int trigPin1  = 8 ;
const int echoPin1  = 9 ;
const int trigPin2  = 10 ;
const int echoPin2  = 11 ;
const int maxCount  = 5;
const int LED_RED   = 7;
const int LED_GREEN = 6;
long durationInt ;
long durationOut ;
int distanceInt ;
int distanceOut ;
int contador = 0;
bool aforoState = 0;
Servo myServo; 


void setup(){
  pinMode(trigPin1, OUTPUT); 
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT); 
  pinMode(echoPin2, INPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  Serial.begin(9600);
  myServo.attach(12);
}

void loop(){
  Serial.print("Hay ");
  Serial.print(contador);
  Serial.print(" personas u.u");
  Serial.println("");

  delay(20);
  countPerson();
  delay(20);
  intPerson();
  delay(20);
  outPerson();
  delay(20);
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
  if (calculateDistanceInt() <= 150){
    Serial.println("Hay alguien blo");
    delay(1300);
    if (calculateDistanceInt()<= 50 && !aforoState){
      Serial.println("Pasó 1 persona");
      delay(200);
      contador += 1;
      delay(20);
    }
  }
}

void outPerson(){
  if (calculateDistanceOut() <= 150){
    Serial.println("Va a salir alguien blo");
    delay(1300);
    if (calculateDistanceOut() <= 50){
      Serial.println("Salió 1 persona");
      delay(200);
      contador -= 1;
      delay(20);
    }
  }
}

void countPerson (){
  if (contador == maxCount){
    delay(20);
    myServo.write(40);
    Serial.println("Aforo a full capacidad");
    delay(20);
    digitalWrite(LED_RED,HIGH);
    delay(20);
    digitalWrite(LED_GREEN,LOW);
    delay(20);
    aforoState = 1;
  } else{
    myServo.write(40);
    delay(20);
    digitalWrite(LED_GREEN,HIGH);
    delay(20);
    digitalWrite(LED_RED,LOW);
    delay(20);
    aforoState = 0;
  }
}