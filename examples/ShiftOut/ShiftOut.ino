#include <ShiftOut.h>
#include <hardware/IC74HC595.h>

#define LATCHPIN A11
#define DATAPIN A15
#define CLOCKPIN A13
#define CHIPCOUNT 4

CREATE_NATIVE_74HC595(so, LATCHPIN, DATAPIN, CLOCKPIN, CHIPCOUNT);

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Booting");
}

void loop() {
  delay(500);
  so.setAll(true).commit();

  delay(500);
  so.setAll(false).commit();
}