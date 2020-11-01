#include <NativeDigitalIO.h>
#include <hardware/IC74HC166.h>
#include <ShiftInOut.h>

IC74HC166<NativeDigitalIO, 2> aa(1,2,3);
pisoInterface<IC74HC166<NativeDigitalIO, 2>> knoppen(aa);

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Booting");
}

void loop() {
  auto buffer = knoppen.read(2);

  Serial.print  ("0x");
  Serial.print  (buffer[0], HEX);
  Serial.print  (", 0x");
  Serial.println(buffer[1], HEX);
}
