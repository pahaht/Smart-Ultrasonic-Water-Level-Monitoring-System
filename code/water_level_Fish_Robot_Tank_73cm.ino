#include <Wire.h>  // Include the Wire library for I2C communication
#include <LiquidCrystal_I2C.h>  // Include the LiquidCrystal_I2C library for I2C LCD communication

#define trigPin 6
#define echoPin 7

LiquidCrystal_I2C lcd(0x27, 20, 4);  // Set the LCD address to 0x27 for a 16x2 display

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  lcd.init();  // Initialize the LCD
  lcd.backlight();  // Turn on the backlight
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;   // ici
  


  float tankHeight = 73.0;  // Set the height of the tank in cm
  float waterLevel = tankHeight - distance;  // Calculate the water level
  if (waterLevel < 0) {
    waterLevel = 0;  // Prevent negative water level values
  }
 // float waterLevelPercent = (waterLevel / tankHeight) * 100.0;  // Convert water level to percentage

  lcd.clear();  // Clear the LCD
  lcd.setCursor(0, 0);  // Set the cursor to the first column of the first row
  lcd.print("Water Level:");  // Print the header
  lcd.setCursor(0, 1);  // Set the cursor to the first column of the second row
  lcd.print(waterLevel, 2);  // Print the water level in centimeter

  delay(1000);
}
