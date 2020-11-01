#include <NativeDigitalIO.h>
#include <hardware/IC74HC595.h>
#include <ShiftInOut.h>

IC74HC595<NativeDigitalIO, 2> aa(1,2,3);
sipoInterface<IC74HC595<NativeDigitalIO, 2>> lights(aa);

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Booting");
}

void loop() {

}
