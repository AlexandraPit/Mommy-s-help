#include <Servo.h>
#include <dht11.h>

dht11 DHT11;
Servo myservo;
int pos = 0;
int stepSize = 1;
int numMovements = 2;

const int servoPin = A0;
const int soundSensorPin = A1;
const int waterSensorPin = A2;
const int temperatureSensorPin = 4;
const int waterSensorLed = 3;
const int temperatureSensorLed = 5;

//  noTone(buzzerPin);

void setup() {
  myservo.attach(servoPin);
  Serial.begin(9600);
  pinMode(waterSensorLed, OUTPUT);
  pinMode(temperatureSensorLed, OUTPUT);
}

void loop() {


  /// ----------------------   INPUT: SOUND SENSOR; OUTPUT: SERVO   ----------------------

  int soundValue = analogRead(soundSensorPin);
  Serial.print("Sound: ");
  Serial.println(soundValue);

  if (soundValue > 200) {
    myservo.write(0);
    delay(500);

    for (int i = 0; i < numMovements; ++i) {
      for (pos = 0; pos <= 190; pos += stepSize) {
        myservo.write(pos);
        delay(15);
      }

      for (pos = 190; pos >= 0; pos -= stepSize) {
        myservo.write(pos);
        delay(15);
      }
    }
  }



  /// ----------------------  INPUT: WATER SENSOR; OUTPUT: LED   ----------------------

  int waterValue = digitalRead(waterSensorPin);

  if (waterValue == HIGH) {
    digitalWrite(waterSensorLed, HIGH);
    delay(100);
    digitalWrite(waterSensorLed, LOW);
    delay(100);
  }

  Serial.println(waterValue == HIGH ? "Water detected!" : "No water");
  delay(100);
  Serial.println();



  /// ----------------------   INPUT: TEMPERATURE AND HUMIDITY SENSOR;  OUTPUT: LED    ----------------------

  int chk = DHT11.read(temperatureSensorPin);

  Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity, 2);

  Serial.print("Temperature  (C): ");
  Serial.println((float)DHT11.temperature, 2);

  if ((float)DHT11.temperature >= 30 || (float)DHT11.temperature <=20) {

    digitalWrite(temperatureSensorLed, HIGH);
    delay(300);
    digitalWrite(temperatureSensorLed, LOW);
    delay(300);

  }
  delay(2000);
}