# Arduino-ShiftInOut

The Arduino ShiftInOut is a Serial to Parallel Shifting-Out and Parallel to Serial Shifting-In library.

The hardware bindings for the shifting are provided as C++ template arguments.
Currently supported:
- [74HC165](https://github.com/lathoub/Arduino-ShiftInOut/blob/main/src/hardware/IC74HC165.h)
- [74HC595](https://github.com/lathoub/Arduino-ShiftInOut/blob/main/src/hardware/IC74HC595.h)

The DigitalRead and DigitalWrite functions can be overwritten if faster methods are available (also through C++ temmplate arguments). The [Out-of-the-box implementation](https://github.com/lathoub/Arduino-ShiftInOut/blob/main/src/NativeDigitalIO.h) maps to the default implementation of DigitalRead and Write.

## Usage

### Shift-In

```cpp
#include <ShiftIn.h>
#include <hardware/IC74HC165.h>

#define LATCHPIN A12
#define DATAPIN A14
#define CLOCKPIN A13
#define CHIPCOUNT 4

CREATE_NATIVE_74HC165(si, LATCHPIN, DATAPIN, CLOCKPIN, CHIPCOUNT);

void setup() {
  ...
}

void loop() {
  ...
  auto result = si.read();
  ...
```
  
### Shift-Out

```cpp
#include <ShiftOut.h>
#include <hardware/IC74HC595.h>

#define LATCHPIN A11
#define DATAPIN A15
#define CLOCKPIN A13
#define CHIPCOUNT 4

CREATE_NATIVE_74HC595(so, LATCHPIN, DATAPIN, CLOCKPIN, CHIPCOUNT);

void setup() {
  ...
}

void loop() {
  ..
  so.setAll(true).commit();
  .. 
}
```
