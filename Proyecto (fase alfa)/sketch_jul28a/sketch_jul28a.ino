#include <Servo.h>.
#include <math.h>

// COMPONENTS
const int trigPin1  = 8 ;
const int echoPin1  = 9 ;
const int trigPin2  = 10 ;
const int echoPin2  = 11 ;
const int LED_RED   = 7;  //close
const int LED_GREEN = 6;  //open
const int LED_WHITE = 5;  //dangerZone
const int LDR= 0;        //generalStatus
Servo myServo1; 

//CONSTANTS
const int maxCount = 5; //capacity
const float angleRad = 120*PI/180; //radians (just change the value behind PI, put it in sexagesimals - don't be a MONGOL)
const float doorHeight = 15; //cm
const float doorWidth = 10; //cm
const int securityRange = 1; //cm

//VARIABLES
const float baseDistance = doorHeight*tan(angleRad); //cm
const float floorDistance = sqrt(sq(doorHeight)+sq(baseDistance)); //cm
const int closeAngle = 90*PI/180 - atan(2.2/(doorWidth/2)); // closing angle
const int openAngle = 2*closeAngle; // openning angle
float distanceInt;
float distanceOut;
float durationInt ;
float durationOut ;
bool intState = 0;
bool outState = 0;
bool aforoState = 0;
bool securityState = 0;
int contador = 0; 


void setup(){
  pinMode(trigPin1, OUTPUT); 
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT); 
  pinMode(echoPin2, INPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT); 
  pinMode(LED_WHITE, OUTPUT);
  Serial.begin(9600);
  myServo1.attach(12);
//  myServo2.attach(13);
}

void loop(){
  int lightRValue = analogRead(LDR);
  Serial.println(lightRValue);
  if (lightRValue >= 550) {
    securityState = 1;
  } else {
    securityState = 0;
  }
  if (securityState) {
    Serial.print("Hay ");
    Serial.print(contador);
    Serial.print(" persona(as)");
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
    delay(1000);
    digitalWrite(LED_RED,LOW);
    digitalWrite(LED_GREEN,LOW);
    digitalWrite(LED_WHITE,LOW);
    myServo1.write(closeAngle);
    }
}

float calculateDistanceInt(){ 
  digitalWrite(trigPin1, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  durationInt = pulseIn(echoPin1, HIGH); 
  distanceInt= durationInt*0.034/2;
  return distanceInt;
}

float calculateDistanceOut(){ 
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
  if (calculateDistanceInt() <= floorDistance && !aforoState){
    Serial.println("Entrando...");
    float relativeDistance = 0;
    float generalDistance = relativeDistance*sin(angleRad);
    float securityDistance = doorWidth + securityRange + 1.5;
    float avSpeedInt = 0;
    while (generalDistance < securityDistance){
      float distance1 = calculateDistanceInt();
      delay(300);
      float distance2 = calculateDistanceInt();
      if (distance1 < distance2){
        avSpeedInt = (distance1 + distance2)/0.3;
        intState = 1;
        relativeDistance = distance2;
      } else{
        intState = 0;
        generalDistance = securityDistance;
      }
    }
    if (intState){
      float securitySpace = doorWidth + securityRange + 1.5;
      float spaceConfirm = calculateDistanceOut()*sin(angleRad);
      while (spaceConfirm < securitySpace){
        digitalWrite(LED_WHITE, HIGH);
        delay(20);
        digitalWrite(LED_WHITE, LOW);
        delay(20);
        digitalWrite(LED_WHITE, HIGH);
        float spaceConfirm1 = calculateDistanceOut()*sin(angleRad);
        delay(20);
        digitalWrite(LED_WHITE, LOW);
        spaceConfirm = spaceConfirm1;
      }
      digitalWrite(LED_WHITE, LOW);
      myServo1.write(0);
      delay((2*securityDistance/avSpeedInt)-500);
      myServo1.write(closeAngle);
      delay(350);
      float confirmDistance = calculateDistanceOut();
      if (confirmDistance < securitySpace){
        contador += 1;
        Serial.println("Sí pasó...");
      } else {
        Serial.println("No pasó...");
      }
    } 
  }
}

void outPerson(){
  if (calculateDistanceInt() <= floorDistance){
    Serial.println("Saliendo...");
    float relativeDistance = 0;
    float generalDistance = relativeDistance*sin(angleRad);
    float securityDistance = doorWidth + securityRange;
    float avSpeedOut = 0;
    while (generalDistance < securityDistance){
      float distance1 = calculateDistanceOut();
      delay(300);
      float distance2 = calculateDistanceOut();
      if (distance1 < distance2){
        avSpeedOut = (distance1 + distance2)/0.3;
        outState = 1;
        relativeDistance = distance2;
      } else{
        outState = 0;
        generalDistance = securityDistance;
      }
    }
    if (outState){
      float securitySpace = doorWidth + securityRange;
      float spaceConfirm = calculateDistanceInt()*sin(angleRad);
      while (spaceConfirm < securitySpace){
        digitalWrite(LED_WHITE, HIGH);
        delay(20);
        digitalWrite(LED_WHITE, LOW);
        delay(20);
        digitalWrite(LED_WHITE, HIGH);
        float spaceConfirm2 = calculateDistanceInt()*sin(angleRad);
        delay(20);
        digitalWrite(LED_WHITE, LOW);
        spaceConfirm = spaceConfirm2;
      }
      digitalWrite(LED_WHITE, LOW);
      myServo1.write(openAngle);
      delay((2*securityDistance/avSpeedOut)-500);
      myServo1.write(closeAngle);
      delay(350);
      float confirmDistance = calculateDistanceInt();
      if (confirmDistance < securitySpace){
        contador -= 1;
        Serial.println("Sí salió...");
      } else {
        Serial.println("No salió...");
      }
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