#include <ShiftInOut.h>
#include <LightManager.h>

CREATE_NATIVE_74HC595(lichten, A11, A15, A13, 2);
LightManager<uint8_t, 2> lights;

uint8_t aan[] = {0xFF, 0xFF};
uint8_t uit[] = {0x00, 0x00};

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Booting");
}

void loop() {
  delay(500);
  lights.set(1, false);
  lichten.write(lights.buffer(), 2);

  delay(500);
  lights.set(1, true);
  lichten.write(lights.buffer(), 2);
}
