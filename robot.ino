/*
Ce code a été écrit en 2023 par Julien Talent et les membres de son groupe en 1ère STI2D 3.
Ce code est celui qui aura fait fonctionner le robot du lycée Adam de Craponne à Salon de Provence.
Je souhaite remercier tout mes professeurs et mes camarades de classe pour leurs aide et leurs soutiens.
    Merci !
https://github.com/jujububule/robot
*/

#define dirMotoD 7
#define vitMotoD 6

#define dirMotoG 4
#define vitMotoG 5


#define servoPin 9
#include <Servo.h>
Servo servo;


#define ultraTrig 12
#define ultraEcho 11

#define tempQuartTour 500
#define vitesseMoto 100

void setup()
{
  Serial.begin(9600);
  Serial.println("Startup !");
  
  //pin moteur droit
  pinMode(dirMotoD, OUTPUT);
  pinMode(vitMotoD, OUTPUT);
  
  //pin moteur gauche
  pinMode(dirMotoG, OUTPUT);
  pinMode(vitMotoG, OUTPUT);
  
  //pin servo moteur
  servo.attach(servoPin);

  //pin capteur ultrason
  pinMode(ultraTrig, OUTPUT);
  pinMode(ultraEcho, INPUT);

  Serial.println("Started !");
}

void loop()
{
  servo.write(90); delay(2000);
  avancer(vitesseMoto);
  while(distance()>12 or distance() == 0);
  stop();
  servo.write(0); delay(2000);
  if(distance()>20 or distance() == 0)
  {
    droite(vitesseMoto); delay(tempQuartTour);
    stop();
  }
  else
  {
    servo.write(180); delay(2000);
    if(distance()>20 or distance() == 0)
     {
     gauche(vitesseMoto); delay(tempQuartTour);
     stop();
   }
   else
   {
    Serial.println("Fait Demi-tour !");
    gauche(vitesseMoto); delay(tempQuartTour*2);
    stop(); 
   }
  }
}

void reculer(int vitesse)
{
  Serial.println("Recule !");
// Pour faire tourner les moteurs dans le bon sens 
  digitalWrite(dirMotoD,HIGH);
  digitalWrite(dirMotoG,HIGH);
// Pour donner un acoup et lancer les moteurs
  analogWrite(vitMotoD, 255);
  analogWrite(vitMotoG, 255);
  delay(5);
// Pour faire tourner les moteurs a la vitesse voulue
  analogWrite(vitMotoD, vitesse);
  analogWrite(vitMotoG, vitesse);
}

void avancer(int vitesse)
{
  Serial.println("Avance !");
// Pour faire tourner les moteurs dans le bon sens 
  digitalWrite(dirMotoD,LOW);
  digitalWrite(dirMotoG,LOW);
// Pour donner un acoup et lancer les moteurs
  analogWrite(vitMotoD, 255);
  analogWrite(vitMotoG, 255);
  delay(5);
// Pour faire tourner les moteurs a la vitesse voulue
  analogWrite(vitMotoD, vitesse);
  analogWrite(vitMotoG, vitesse);
}

void droite(int vitesse)
{
  Serial.println("Tourne a Droite !");
// Pour faire tourner les moteurs dans le bon sens 
  digitalWrite(dirMotoD,HIGH);
  digitalWrite(dirMotoG,LOW);
// Pour donner un acoup et lancer les moteurs
  analogWrite(vitMotoD, 255);
  analogWrite(vitMotoG, 255);
  delay(5);
// Pour faire tourner les moteurs a la vitesse voulue
  analogWrite(vitMotoD, vitesse);
  analogWrite(vitMotoG, vitesse);
}

void gauche(int vitesse)
{
  Serial.println("Tourne a Gauche !");
// Pour faire tourner les moteurs dans le bon sens 
  digitalWrite(dirMotoD,LOW);
  digitalWrite(dirMotoG,HIGH);
// Pour donner un acoup et lancer les moteurs
  analogWrite(vitMotoD, 255);
  analogWrite(vitMotoG, 255);
  delay(5);
// Pour faire tourner les moteurs a la vitesse voulue
  analogWrite(vitMotoD, vitesse);
  analogWrite(vitMotoG, vitesse);
}

void stop()
{
  Serial.println("S'arête !");
// Arête la rotation des moteurs
  analogWrite(vitMotoD, 0);
  analogWrite(vitMotoG, 0);
}

float distance() {
  Serial.println("Mesure la Distance");

  float varDistance;
  digitalWrite(ultraTrig, LOW);
  delayMicroseconds(5);

  digitalWrite(ultraTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultraTrig, LOW);

  float duration = pulseIn(ultraEcho, HIGH, 3000);
  varDistance = duration * 0.034 / 2;
  
  Serial.println(varDistance);
  return(varDistance);
}
