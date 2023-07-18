#include <Servo.h>

int PIR1_PIN = 10;
int PIR2_PIN = 11;
int PIR3_PIN = 12;
int PIR4_PIN = 13;
int LED_1    = 5 ;
int LED_2    = 6 ;
int LED_3    = 7 ;
int LED_4    = 8 ;
int LED_5    = 9 ;
int contador = 0 ;
int aforo    = 10;
Servo miServo;

const int TB_SECONDS = 1;  // Tiempo en segundos para que PIR3 se prenda después de PIR1

bool pir1State = false;
bool pir2State = false;
bool pir3State = false;
bool pir4State = false;

unsigned long pir1StartTime = 0;
unsigned long pir4StartTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(PIR1_PIN, INPUT);
  pinMode(PIR4_PIN, INPUT);
  pinMode(PIR2_PIN, INPUT);
//  pinMode(PIR3_PIN, INPUT);
  pinMode(PIR2_PIN, OUTPUT);
  pinMode(PIR3_PIN, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  pinMode(LED_5, OUTPUT);
  miServo.attach(4);
  // Inicialmente, los PIR2, PIR3 están apagados
  digitalWrite(PIR2_PIN, LOW);
  digitalWrite(PIR3_PIN, LOW);

}

void loop() {

  //CONDICIONES INICIALES


  //Condiciones Iniciales 1
  if (digitalRead(PIR1_PIN) == HIGH && !pir1State) {
    pir1State == true;
    Serial.println("zi");

    pir1StartTime = millis();
  }

  if (pir1State && millis() - pir1StartTime >= TB_SECONDS * 1000) {
    // Encender PIR3
    digitalWrite(PIR3_PIN, HIGH);
    if (digitalRead(PIR3_PIN) == HIGH){
      Serial.println("nou");

      delay(1000);
      contador = contador + 1 ;

    }
    delay(1500);
    digitalWrite(PIR3_PIN,LOW);
    pir1State == false;
  }

  if (digitalRead(PIR4_PIN) == HIGH && !pir4State) {
    pir4State == true;
    digitalWrite(PIR1_PIN, LOW);
    digitalWrite(PIR3_PIN, LOW);
    pir4StartTime = millis();
  }

  if (pir4State && millis() - pir4StartTime >= TB_SECONDS * 1000) {
    // Encender PIR3
    digitalWrite(PIR2_PIN, HIGH);
    if (digitalRead(PIR2_PIN) == HIGH){
      digitalWrite(LED_2,HIGH);
      delay(1000);
      contador = contador - 1 ;
      digitalWrite(LED_2,LOW) ;     
    }
    delay(1500);
    digitalWrite(PIR2_PIN, LOW);
    pir4State == false;
  }
  //Salida al port
  closeDoorLed(aforo);
  delay(3000);
  //Mensajito insano
  Serial.print("Hay ");
  Serial.print(contador);
  Serial.print(" personas.");
  Serial.println("");
    
}

void closeDoorLed(int aforo){
  if (contador == aforo){
    miServo.write(90);
    digitalWrite(LED_3, LOW);
    digitalWrite(LED_4, HIGH);
    delay(8000);
    digitalWrite(LED_5, HIGH);


  }
  else{
    digitalWrite(LED_3,HIGH);
  }
}