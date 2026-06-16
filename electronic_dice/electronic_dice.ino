#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

// I2C LCD using hd44780 library
hd44780_I2Cexp lcd;

// LCD dimensions
const int LCD_COLS = 16;
const int LCD_ROWS = 2;

// 7-Segment Display Pins
int seg_a = 11;
int seg_b = 10;
int seg_c = 9;
int seg_d = 8;
int seg_e = 7;
int seg_f = 6;
int seg_g = 5;

// Touch Sensor Pin
int sensor = 3;

int i = 0;
int prevRoll = 0;
unsigned long resultDisplayTime = 0;
int rollCount = 0;

void setup() {
  // Configure segment pins as outputs
  pinMode(seg_a, OUTPUT);
  pinMode(seg_b, OUTPUT);
  pinMode(seg_c, OUTPUT);
  pinMode(seg_d, OUTPUT);
  pinMode(seg_e, OUTPUT);
  pinMode(seg_f, OUTPUT);
  pinMode(seg_g, OUTPUT);
  pinMode(sensor, INPUT);

  // Initialize Serial
  Serial.begin(9600);
  Serial.println("Dice Roller Initialized");
  Serial.println("------------------------");

  // Initialize LCD
  int status = lcd.begin(LCD_COLS, LCD_ROWS);
  if (status) {
    // If init failed, halt and flash error code
    hd44780::fatalError(status);
  }
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Dice Roller");
  lcd.setCursor(0, 1);
  lcd.print("Touch to Roll!");

  // Seed random number generator
  randomSeed(analogRead(A0));

  // Idle animation until sensor is touched
  while (digitalRead(sensor) == LOW) {
    pattern();
  }
}

void loop() {
  if (digitalRead(sensor) == HIGH) {
    i = random(1, 7);
    rollCount++;

    // Suspense animation
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Rolling...");
    for (int pat = 0; pat <= 2; pat++) {
      pattern();
    }

    // Display result on 7-segment
    sevenSeg();

    // Display result on LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Roll #");
    lcd.print(rollCount);
    lcd.print(": ");
    lcd.print(i);
    lcd.setCursor(0, 1);
    if (prevRoll == 0) {
      lcd.print("Prev: --");
    } else {
      lcd.print("Prev: ");
      lcd.print(prevRoll);
    }

    prevRoll = i;

    // Log to Serial Monitor
    Serial.print("Roll #");
    Serial.print(rollCount);
    Serial.print(": ");
    Serial.println(i);

    resultDisplayTime = millis();
  }

  // Return to idle after 10 seconds
  if (resultDisplayTime != 0 && millis() - resultDisplayTime > 10000) {
    resultDisplayTime = 0;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Dice Roller");
    lcd.setCursor(0, 1);
    lcd.print("Touch to Roll!");
    while (digitalRead(sensor) == LOW) {
      pattern();
    }
  }
}

void clearDisplay() {
  digitalWrite(seg_a, LOW);
  digitalWrite(seg_b, LOW);
  digitalWrite(seg_c, LOW);
  digitalWrite(seg_d, LOW);
  digitalWrite(seg_e, LOW);
  digitalWrite(seg_f, LOW);
  digitalWrite(seg_g, LOW);
}

void sevenSeg() {
  clearDisplay();

  if (i == 1) {
    digitalWrite(seg_b, HIGH);
    digitalWrite(seg_c, HIGH);
  } else if (i == 2) {
    digitalWrite(seg_a, HIGH);
    digitalWrite(seg_b, HIGH);
    digitalWrite(seg_d, HIGH);
    digitalWrite(seg_e, HIGH);
    digitalWrite(seg_g, HIGH);
  } else if (i == 3) {
    digitalWrite(seg_a, HIGH);
    digitalWrite(seg_b, HIGH);
    digitalWrite(seg_c, HIGH);
    digitalWrite(seg_d, HIGH);
    digitalWrite(seg_g, HIGH);
  } else if (i == 4) {
    digitalWrite(seg_b, HIGH);
    digitalWrite(seg_c, HIGH);
    digitalWrite(seg_f, HIGH);
    digitalWrite(seg_g, HIGH);
  } else if (i == 5) {
    digitalWrite(seg_a, HIGH);
    digitalWrite(seg_c, HIGH);
    digitalWrite(seg_d, HIGH);
    digitalWrite(seg_f, HIGH);
    digitalWrite(seg_g, HIGH);
  } else if (i == 6) {
    digitalWrite(seg_a, HIGH);
    digitalWrite(seg_c, HIGH);
    digitalWrite(seg_d, HIGH);
    digitalWrite(seg_e, HIGH);
    digitalWrite(seg_f, HIGH);
    digitalWrite(seg_g, HIGH);
  }

  delay(2000);
}

void pattern() {
  clearDisplay();

  digitalWrite(seg_a, HIGH); delay(100); digitalWrite(seg_a, LOW);
  digitalWrite(seg_b, HIGH); delay(100); digitalWrite(seg_b, LOW);
  digitalWrite(seg_c, HIGH); delay(100); digitalWrite(seg_c, LOW);
  digitalWrite(seg_d, HIGH); delay(100); digitalWrite(seg_d, LOW);
  digitalWrite(seg_e, HIGH); delay(100); digitalWrite(seg_e, LOW);
  digitalWrite(seg_f, HIGH); delay(100); digitalWrite(seg_f, LOW);
}
