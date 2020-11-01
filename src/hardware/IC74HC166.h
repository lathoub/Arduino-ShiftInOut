#pragma once

// parallel-in/serial out

/*
// The 74HC166; 74HCT166 is an 8-bit serial or parallel-in/serial-out shift register. The
// device features a serial data input (DS), eight parallel data inputs (D0 to D7) and a serial
// output (Q7). 
// 
// When the parallel enable input (PE) is LOW, the data from D0 to D7 is loaded
// into the shift register on the next LOW-to-HIGH transition of the clock input (CP). When
// PE is HIGH, data enters the register serially at DS with each LOW-to-HIGH transition of
// CP. 
//
// When the clock enable input (CE) is LOW data is shifted on the LOW-to-HIGH
// transitions of CP. A HIGH on CE disables the CP input. 
// (Note: often pulled to Ground, so it is always LOW)
// 
// Inputs include clamp diodes which enable the use of current limiting resistors to interface 
// inputs to voltages in excess of VCC. 
*/

template<class DigitalPin, uint8_t size>
class IC74HC166 {
private:
  DigitalPin _clock; // CP
  DigitalPin _latch; // PE
  DigitalPin _data;  // DS
 // DigitalPin _data;  // CE
    
  uint8_t _buffer[size];

  uint8_t shiftIn()
  {
    uint8_t buffer = 0;

    for (uint8_t i = 0; i < 8; i++) { // 8 bits in a byte
      _clock.write(LOW);
      delayMicroseconds(2);
      
      if (_data.read()) 
        buffer = buffer | (1 << i);

      _clock.write(HIGH);
    }

    return buffer;
  }

  public:
  // Constructor
  IC74HC166(uint8_t pinClock, uint8_t pinLatch, uint8_t pinData)
  {
    _clock.pin(pinClock, OUTPUT);
    _latch.pin(pinLatch, OUTPUT);
    _data.pin (pinData,  INPUT);

    _clock.write(LOW);
    _latch.write(LOW);
  }

  // read from <amount> IC's
  uint8_t* read(uint8_t amount)
  {
    _latch.write(HIGH);
    delayMicroseconds(20); // needed??
    _latch.write(LOW);

    for (uint8_t i = 0; i < amount; i++) 
      shiftIn();

    return _buffer;
  }

};
