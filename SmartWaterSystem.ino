#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>

// === Pins ===
#define TRIG_PIN 2
#define ECHO_PIN 3

#define RED_LED_PIN 4
#define YELLOW_LED_PIN 5
#define GREEN_LED_PIN 6

#define RELAY_PIN 7

// === Constants ===
const int tankEmptyDistance = 3;   // Distance when tank is empty (adjust based on your tank)
const int tankFullDistance = 5;     // Distance when tank is full (adjust based on your tank)

// Pump control flags
bool pumpLocked = false;

// === Objects ===
LiquidCrystal_I2C lcd(0x27, 16, 2); // Check I2C address (usually 0x27 or 0x3F)
RTC_DS3231 rtc;

// === Variables ===
long duration;
int distanceCm;

void setup() {
  Serial.begin(9600);

  // Pin Modes
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // Relay module active LOW: HIGH means OFF initially

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Tank Monitor");

  // Initialize RTC
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, setting time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Set RTC time to compile time
  }

  delay(2000);
  lcd.clear();
}

void loop() {
  DateTime now = rtc.now();

  // Daily pump unlock at midnight
  if (now.hour() == 0 && now.minute() == 0 && now.second() == 0) {
    pumpLocked = false;
  }

  distanceCm = getDistance();
  Serial.print("Distance: ");
  Serial.print(distanceCm);
  Serial.println(" cm");

  lcd.setCursor(0, 0);
  lcd.print("Water Lvl: ");
  lcd.print(distanceCm);
  lcd.print(" cm  ");

  if (!pumpLocked) {
    if (distanceCm > tankEmptyDistance) {
      // Water very low
      digitalWrite(RED_LED_PIN, HIGH);
      digitalWrite(GREEN_LED_PIN, LOW);
      digitalWrite(YELLOW_LED_PIN, LOW);

      digitalWrite(RELAY_PIN, LOW); // Turn ON pump (Relay active LOW)

      lcd.setCursor(0, 1);
      lcd.print("Pump: ON          ");
    }
    else if (distanceCm <= tankFullDistance) {
      // Water full
      digitalWrite(RED_LED_PIN, LOW);
      digitalWrite(GREEN_LED_PIN, LOW);
      digitalWrite(YELLOW_LED_PIN, HIGH);

      digitalWrite(RELAY_PIN, HIGH); // Turn OFF pump
      pumpLocked = true;             // Lock pump for the day

      lcd.setCursor(0, 1);
      lcd.print("Tank FULL LOCKED  ");
    }
    else {
      // Water normal level
      digitalWrite(RED_LED_PIN, LOW);
      digitalWrite(GREEN_LED_PIN, HIGH);
      digitalWrite(YELLOW_LED_PIN, LOW);

      digitalWrite(RELAY_PIN, HIGH); // Turn OFF pump

      lcd.setCursor(0, 1);
      lcd.print("Pump: OFF         ");
    }
  }
  else {
    // Pump locked
    digitalWrite(RELAY_PIN, HIGH); // Keep pump OFF
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, HIGH);

    lcd.setCursor(0, 1);
    lcd.print("Pump Locked       ");
  }

  delay(1000);
}

// === Function to measure distance using Ultrasonic ===
int getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  int distanceCm = duration * 0.034 / 2;
  return distanceCm;
}