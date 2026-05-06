#include <BleGamepad.h>

BleGamepad bleGamepad("ESP32 FPV Controller", "ESP32", 100);

#define CH1_PIN 32
#define CH2_PIN 33
#define CH3_PIN 25
#define CH4_PIN 26

#define DEADZONE 25

int readPWM(int pin) {
  int val = pulseIn(pin, HIGH, 25000);

  if (val == 0) return 1500;
  if (val < 1000) val = 1000;
  if (val > 2000) val = 2000;

  return val;
}

int mapAxis(int v) {
  if (abs(v - 1500) < DEADZONE) {
    return 16384; // centro
  }
  return map(v, 1000, 2000, 0, 32767);
}

int mapThrottle(int v) {
  return map(v, 1000, 2000, 0, 32767);
}

void setup() {
  pinMode(CH1_PIN, INPUT);
  pinMode(CH2_PIN, INPUT);
  pinMode(CH3_PIN, INPUT);
  pinMode(CH4_PIN, INPUT);

  bleGamepad.begin();
}

void loop() {
  if (bleGamepad.isConnected()) {

    int roll     = mapAxis(readPWM(CH1_PIN));
    int pitch    = mapAxis(readPWM(CH2_PIN));
    int throttle = mapThrottle(readPWM(CH3_PIN));
    int yaw      = mapAxis(readPWM(CH4_PIN));

    bleGamepad.setAxes(
      roll, pitch, throttle, yaw,
      0, 0, 0, 0
    );
  }

  delay(10);
}
