#include <Servo.h>. 

const int trigPin   = 8 ;
const int echoPin   = 9 ;
const int maxCount  = 30;
const int LED_RED   = 10;
const int LED_GREEN = 11;
long duration ;
int distance ;
int contador = 0;
bool aforoState = 0;
Servo myServo; 


void setup(){
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  Serial.begin(9600);
  myServo.attach(4);
}

void loop(){
  delay(20);
  countPerson();
  delay(20);
  intPerson();
  delay(20);
  outPerson();
  delay(20);
}

int calculateDistance(){ 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); 
  distance= duration*0.034/2;
  return distance;
}

void intPerson(){
  if (calculateDistance() <= 150){
    Serial.println("Hay alguien blo");
    delay(1300);
    if (calculateDistance()<= 50 && !aforoState){
      Serial.println("Pasó 1 persona");
      delay(200);
      contador += 1;
      delay(20);
    }
  }
}

void outPerson(){
  if (calculateDistance() <= 150){
    Serial.println("Va a salir alguien blo");
    delay(1300);
    if (calculateDistance() <= 50){
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
    myServo.write(90);
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