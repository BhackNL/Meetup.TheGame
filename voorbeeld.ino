#include <I2C.h>
#include <II2C.h>
#include <MPU6050.h>
#include <MultiFuncShield.h>

#define LED_MIN 10
#define LED_MAX 13

#define UP true
#define DOWN false

int ledPin = LED_MIN;
bool direction = UP;
int delayMs = 750;
int score = 0;

void setup() {
  Timer1.initialize();
  MFS.initialize(&Timer1);
  Serial.begin(9600);
  
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);

  Serial.println(score);
}

void gameOver() {
  score = 0;
  delayMs = 750;
  direction = UP;
  ledPin = LED_MIN;

  Serial.println("GAME OVER!");
  
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);

  delay(2000);

  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
}

bool handleUp() {
  if (ledPin == LED_MAX) {
    if (analogRead(3) < 100) {
      score++;
      Serial.println(score);

      if (delayMs > 150)
        delayMs -= 30;
    } else {
      gameOver();
      return true;
    }
      
    direction = DOWN;
    ledPin--;
  } else {
    ledPin++;
  }

  return false;
}

bool handleDown() {
  if (ledPin == LED_MIN) {
    if (analogRead(1) < 100) {
      score++;

      Serial.println(score);

      if (delayMs > 150)
        delayMs -= 30;
    } else {
      gameOver();
      return true;
    }
      
    direction = UP;
    ledPin++;
  } else {
    ledPin--;
  }

  return false;
}

void loop() {
  digitalWrite(ledPin, HIGH);

  if (direction == UP) {
    if (handleUp())
      return;
  } else if (direction == DOWN) {
    if (handleDown())
      return;
  }

  digitalWrite(ledPin, LOW);

  MFS.write(score);
  
  delay(delayMs);
}
