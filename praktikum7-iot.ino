#include <LiquidCrystal_I2C.h>
#include <DHTesp.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
Servo myServo;

const int servoPin = 3;
const int trigPin = 9;
const int echoPin = 10;
const int relayPin = 12;
const int dhtPin = 13;
float suhu = 0;
float kelembaban = 0;
DHTesp dhtSensor;

void setup() {
  dhtSensor.setup(dhtPin, DHTesp::DHT22);
  pinMode(relayPin, OUTPUT);

  myServo.attach(servoPin);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("Pemantauan");
  lcd.setCursor(2, 1);
  lcd.print("Suhu & Kelembaban");
  delay(3000);
  lcd.clear();
}

void loop() {
  TempAndHumidity data = dhtSensor.getTempAndHumidity();
  suhu = data.temperature;
  kelembaban = data.humidity;

  long duration, distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.034) / 2;

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 2);
  lcd.print("Suhu       :");
  lcd.setCursor(13, 2);
  lcd.print(suhu);
  lcd.setCursor(19, 2);
  lcd.print("C");
  lcd.setCursor(0, 3);
  lcd.print("Kelembaban :");
  lcd.setCursor(13, 3);
  lcd.print(kelembaban);
  lcd.setCursor(19, 3);
  lcd.print("%");

  if (suhu < 25) {
    digitalWrite(relayPin, HIGH);
  } else {
    digitalWrite(relayPin, LOW);
  }

  if (distance < 20) {
    myServo.write(180);
  } else {
    myServo.write(0);
  }

}
