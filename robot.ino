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
  Serial.println("starup");
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
    Serial.println("demi-tour");
    gauche(vitesseMoto); delay(tempQuartTour*2);
    stop(); 
   }
  }
}

void reculer(int vitesse)
{
  digitalWrite(dirMotoD,HIGH);
  digitalWrite(dirMotoG,HIGH);
  analogWrite(vitMotoD, 255);
  analogWrite(vitMotoG, 255);
  delay(5);
  analogWrite(vitMotoD, vitesse);
  analogWrite(vitMotoG, vitesse);
}

void avancer(int vitesse)
{
  digitalWrite(dirMotoD,LOW);
  digitalWrite(dirMotoG,LOW);
  analogWrite(vitMotoD, 255);
  analogWrite(vitMotoG, 255);
  delay(5);
  analogWrite(vitMotoD, vitesse);
  analogWrite(vitMotoG, vitesse);
}

void droite(int vitesse)
{
  Serial.println("droite");
  digitalWrite(dirMotoD,HIGH);
  digitalWrite(dirMotoG,LOW);
  analogWrite(vitMotoD, 255);
  analogWrite(vitMotoG, 255);
  delay(5);
  analogWrite(vitMotoD, vitesse);
  analogWrite(vitMotoG, vitesse);
}

void gauche(int vitesse)
{
  Serial.println("gauche");
  digitalWrite(dirMotoD,LOW);
  digitalWrite(dirMotoG,HIGH);
  analogWrite(vitMotoD, 255);
  analogWrite(vitMotoG, 255);
  delay(5);
  analogWrite(vitMotoD, vitesse);
  analogWrite(vitMotoG, vitesse);
}

void stop()
{
  Serial.println("stop");
  analogWrite(vitMotoD, 0);
  analogWrite(vitMotoG, 0);
}

float distance() {
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
