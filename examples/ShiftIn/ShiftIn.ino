#include <ShiftIn.h>
#include <hardware/IC74HC165.h>

#define LATCHPIN A12
#define DATAPIN A14
#define CLOCKPIN A13
#define CHIPCOUNT 4

CREATE_NATIVE_74HC165(si, LATCHPIN, DATAPIN, CLOCKPIN, CHIPCOUNT);

long lastMillis = 0;
long loops = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Booting");
}

void loop() {
  long currentMillis = millis();
  loops++;

  auto result = si.read();
  for (uint8_t i = 0; i < CHIPCOUNT; i++) {
    Serial.print(result[i], BIN);
    Serial.print(" ");
  }
  Serial.println();

  if (currentMillis - lastMillis > 1000) {
    Serial.print("Loops last second:");
    Serial.println(loops);

    lastMillis = currentMillis;
    loops = 0;
  }
}