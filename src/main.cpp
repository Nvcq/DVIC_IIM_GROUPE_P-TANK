#include <Arduino.h>
#include <PikBtLib.h>

/* Constantes pour les broches */
const int TRIGGER_PIN = 33;  // Broche TRIGGER
const int ECHO_PIN = 32;     // Broche ECHO

const int LED_GREEN = 21;    // Broche Led Verte
const int LED_YELLOW = 22;   // Broche Led Jaune
const int LED_RED = 23;      // Broche Led Rouge

const int leftMotor1 = 12;
const int leftMotor2 = 14;
const int rightMotor1 = 27;
const int rightMotor2 = 26;

const int rightAccel = 13;
const int leftAccel = 25;

int speed = 150;

/* Constantes pour le timeout */
const unsigned long MEASURE_TIMEOUT = 25000UL; // 25ms = ~8m à 340m/s

/* Vitesse du son dans l'air en mm/us */
const float SOUND_SPEED = 340.0 / 1000;

PikBt Bt = PikBt();
void setup() {
  Serial.begin(9600);
  Bt.Init("Nvcq");

  /* Initialise les broches */
  pinMode(leftMotor1, OUTPUT);
	pinMode(leftMotor2, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
	pinMode(rightMotor2, OUTPUT);
  pinMode(rightAccel, OUTPUT);
  pinMode(leftAccel, OUTPUT);

  pinMode(TRIGGER_PIN, OUTPUT);
  digitalWrite(TRIGGER_PIN, LOW); // La broche TRIGGER doit être à LOW au repos
  pinMode(ECHO_PIN, INPUT);

  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);
}

bool automatic = false;

void loop() {

  /* 1. Lance une mesure de distance en envoyant une impulsion HIGH de 10µs sur la broche TRIGGER */
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  
  /* 2. Mesure le temps entre l'envoi de l'impulsion ultrasonique et son écho (si il existe) */
  long measure = pulseIn(ECHO_PIN, HIGH, MEASURE_TIMEOUT);
  
  /* 3. Calcul la distance à partir du temps mesuré */
  float distance_mm = measure / 2.0 * SOUND_SPEED;

  // Serial.print("Distance: ");
  // Serial.print(distance_mm);
  // Serial.print("mm (");
  // Serial.print(distance_mm / 10.0, 2);
  // Serial.print("cm, ");
  // Serial.print(distance_mm / 1000.0, 2);
  // Serial.println("m)");



  /* 4. Allumage des LED en fonction de la distance */
  if(distance_mm < 600) {
    // Serial.println("BIP BIP BIP 10CM");
    digitalWrite(LED_GREEN,HIGH);
    delay(10);
  } else if(distance_mm > 300) {
    digitalWrite(LED_GREEN,LOW);
    delay(10);
  }

  if(distance_mm < 400) {
    // Serial.println("BIP BIP BIP 5CM");
    digitalWrite(LED_YELLOW,HIGH);
    delay(10);
  } else if(distance_mm > 200) {
    digitalWrite(LED_YELLOW,LOW);
    delay(10);
  }

  if(distance_mm < 200) {
    // Serial.println("BIP BIP BIP 2CM");
    digitalWrite(LED_RED,HIGH);
    delay(10);
  } else if(distance_mm > 100) {
    digitalWrite(LED_RED,LOW);
    delay(10);
  }


  if(automatic) {

    digitalWrite(leftMotor1 ,HIGH);     // HIGH MOTEUR 1
    digitalWrite(leftMotor2 ,LOW);    // LOW MOTEUR 1

    digitalWrite(rightMotor1 ,HIGH);   // HIGH MOTEUR 2
    digitalWrite(rightMotor2 ,LOW);    // LOW MOTEUR 2

    analogWrite(rightAccel, 200);
    analogWrite(leftAccel, 200);

    if(distance_mm < 100) {

      digitalWrite(leftMotor1 ,HIGH);     // HIGH MOTEUR 1
      digitalWrite(leftMotor2 ,LOW);    // LOW MOTEUR 1

      digitalWrite(rightMotor2 ,HIGH);   // HIGH MOTEUR 2
      digitalWrite(rightMotor1 ,LOW);    // LOW MOTEUR 2

      analogWrite(rightAccel, 150);
      analogWrite(leftAccel, 150);

      delay(1000);

      digitalWrite(leftMotor1 ,HIGH);     // HIGH MOTEUR 1
      digitalWrite(leftMotor2 ,LOW);    // LOW MOTEUR 1

      digitalWrite(rightMotor1 ,HIGH);   // HIGH MOTEUR 2
      digitalWrite(rightMotor2 ,LOW);    // LOW MOTEUR 2

      analogWrite(rightAccel, 200);
      analogWrite(leftAccel, 200);

    } 
    
  } else {
    if(Bt.Available()){

      char input = Bt.ReadChar();

      if(input=='f') {

        Bt.SendMsg("forward");

        digitalWrite(leftMotor1 ,HIGH);     // HIGH MOTEUR 1
        digitalWrite(leftMotor2 ,LOW);    // LOW MOTEUR 1

        digitalWrite(rightMotor1 ,HIGH);   // HIGH MOTEUR 2
        digitalWrite(rightMotor2 ,LOW);    // LOW MOTEUR 2

        analogWrite(rightAccel, speed);
        analogWrite(leftAccel, speed);

      } else if(input=='b') {

        Bt.SendMsg("back off");

        digitalWrite(leftMotor2 ,HIGH);     // HIGH MOTEUR 1
        digitalWrite(leftMotor1 ,LOW);    // LOW MOTEUR 1

        digitalWrite(rightMotor2 ,HIGH);   // HIGH MOTEUR 2
        digitalWrite(rightMotor1 ,LOW);    // LOW MOTEUR 2

        analogWrite(rightAccel, speed);
        analogWrite(leftAccel, speed);
      } else if(input=='0') {

        Bt.SendMsg("stop");

        analogWrite(rightAccel, 0);
        analogWrite(leftAccel, 0);
      } else if(input=='l') {

        Bt.SendMsg("left");

        digitalWrite(leftMotor2 ,HIGH);     // HIGH MOTEUR 1
        digitalWrite(leftMotor1 ,LOW);    // LOW MOTEUR 1

        digitalWrite(rightMotor1 ,HIGH);   // HIGH MOTEUR 2
        digitalWrite(rightMotor2 ,LOW);    // LOW MOTEUR 2

        analogWrite(rightAccel, speed);
        analogWrite(leftAccel, speed);
      } else if(input=='r') {

        Bt.SendMsg("right");

        digitalWrite(leftMotor1 ,HIGH);     // HIGH MOTEUR 1
        digitalWrite(leftMotor2 ,LOW);    // LOW MOTEUR 1

        digitalWrite(rightMotor2 ,HIGH);   // HIGH MOTEUR 2
        digitalWrite(rightMotor1 ,LOW);    // LOW MOTEUR 2

        analogWrite(rightAccel, speed);
        analogWrite(leftAccel, speed);
      } else if(input=='2') {

        Bt.SendMsg("accelerate");

        speed += 25;

        analogWrite(rightAccel, speed);
        analogWrite(leftAccel, speed);
      } else if(input=='1') {

        Bt.SendMsg("slow down");

        speed -= 25;

        analogWrite(rightAccel, speed);
        analogWrite(leftAccel, speed);
      }
      
      if(input=='a') {
        if(!automatic) {
          automatic = true;
        } else if(automatic) {
          automatic = false;
        }
      }

    }
    delay(100);
  }

}