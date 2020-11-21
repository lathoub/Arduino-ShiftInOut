#include <ShiftInOut.h>
#include <ButtonManager.h>

CREATE_NATIVE_74HC165(knoppen, A12, A14, A13, 2);
ButtonManager<uint8_t, 2> comparator;

long lastMillis = 0;
long loops = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Booting");

  comparator.init(0xFF);
}

void loop() {

  long currentMillis = millis();
  loops++;

  if (comparator.hasChanged(knoppen.read(2)))
  {
    auto bs = comparator.buttonsState(0);
    for (int i = 0; i < bs->count; i++)
      Serial.println(bs->buttonsState[i]);

    bs = comparator.buttonsState(1);
    for (int i = 0; i < bs->count; i++)
      Serial.println(bs->buttonsState[i]);
  }

  if (currentMillis - lastMillis > 1000) {
    Serial.print("Loops last second:");
    Serial.println(loops);

    lastMillis = currentMillis;
    loops = 0;
  }
}
