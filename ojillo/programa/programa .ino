#include <pcf8574.h>

PCF8574 ex1(0x20);
PCF8574 pepe2(0x21);

int pinA = 10;
int pinB = 11;
int pinC = 12;
int pinD = 13;
int contador = 0;


int and1 = 6;
int and2 = 7;
int and3 = 8;
int and4 = 9;

bool estA; 
bool estB; 
bool estC; 
bool estD; 

int nestA; 
int nestB; 
int nestC; 
int nestD; 

int salida = 3;


void setup() {
  Serial.begin(9600);
  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);
  pinMode(pinC, INPUT);
  pinMode(pinD, INPUT);

  pinMode(ex1, 0, OUTPUT);
  pinMode(ex1, 1, OUTPUT);
  pinMode(ex1, 2, OUTPUT);
  pinMode(ex1, 3, OUTPUT);

  pinMode(ex1, 4, OUTPUT);
  pinMode(ex1, 5, OUTPUT);
  pinMode(ex1, 6, OUTPUT);
  pinMode(ex1, 7, OUTPUT);

  pinMode(pepe2, 0, OUTPUT);
  pinMode(pepe2, 1, OUTPUT);
  pinMode(pepe2, 2, OUTPUT);
  pinMode(pepe2, 3, OUTPUT);

  pinMode(pepe2, 4, OUTPUT);
  pinMode(pepe2, 5, OUTPUT);
  pinMode(pepe2, 6, OUTPUT);
  pinMode(pepe2, 7, OUTPUT);

  pinMode(and1, INPUT);
  pinMode(and2, INPUT);
  pinMode(and3, INPUT);
  pinMode(and4, INPUT);
  
  pinMode(salida, OUTPUT);
  
  digitalWrite(ex1, 0, LOW);
  digitalWrite(ex1, 1, LOW);
  digitalWrite(ex1, 2, LOW);
  digitalWrite(ex1, 3, LOW);

  digitalWrite(ex1, 4, LOW);
  digitalWrite(ex1, 5, LOW);
  digitalWrite(ex1, 6, LOW);
  digitalWrite(ex1, 7, LOW);

  digitalWrite(pepe2, 0, LOW);
  digitalWrite(pepe2, 1, LOW);
  digitalWrite(pepe2, 2, LOW);
  digitalWrite(pepe2, 3, LOW);

  digitalWrite(pepe2, 4, LOW);
  digitalWrite(pepe2, 5, LOW);
  digitalWrite(pepe2, 6, LOW);
  digitalWrite(pepe2, 7, LOW);


  
}

void loop() {
  estA = digitalRead(pinA);
  estB = digitalRead(pinB);
  estC = digitalRead(pinC);
  estD = digitalRead(pinD);
  
  nestD = !estD;
  nestC = !estB;
  nestB = !estC;
  nestA = !estA;


  
  
  bool condicion = estA && estB && estC && estD;

  bool lect_and1 = digitalRead(and1);
  bool lect_and2 = digitalRead(and2);
  bool lect_and3 = digitalRead(and3);
  bool lect_and4 = digitalRead(and4);
  bool cond_ands = lect_and1 && lect_and2 && lect_and3 && lect_and4;
  int led = cond_ands;


  
  if(condicion == 0){
    contador = contador + 1;
    nestD = !estD;
    nestC = !estB;
    nestB = !estC;
    nestA = !estA;

    delay(400);
    if(contador == 1){
    digitalWrite(ex1, 0, nestD);
    digitalWrite(ex1, 1, nestC);
    digitalWrite(ex1, 2, nestB);
    digitalWrite(ex1, 3, nestA);
    }
    if(contador == 2){
    digitalWrite(ex1, 4, nestD);
    digitalWrite(ex1, 5, nestC);
    digitalWrite(ex1, 6, nestB);
    digitalWrite(ex1, 7, nestA);
    }

    if(contador == 3){
    digitalWrite(pepe2, 0, nestD);
    digitalWrite(pepe2, 1, nestC);
    digitalWrite(pepe2, 2, nestB);
    digitalWrite(pepe2, 3, nestA);
    }

    if(contador == 4){
    digitalWrite(pepe2, 4, nestD);
    digitalWrite(pepe2, 5, nestC);
    digitalWrite(pepe2, 6, nestB);
    digitalWrite(pepe2, 7, nestA);
    }
  }
  

  Serial.print(cond_ands);
  Serial.println(led);
  digitalWrite(salida, led);
}
