#pragma once

/*
*/

template<class PinLoad, class PinData, class PinClock>
class IC74HC595 {
private:
  PinLoad&  PL;
  PinData&  DS;
  PinClock& CP; 

  public:
  // Constructor
  IC74HC595(PinLoad& load, PinData& data, PinClock& clock)
     :   PL(load), DS(data), CP(clock)
  {
  }

  void beginWrite()
  {
    PL.write(LOW);
  }

  void write(uint8_t value)
  {
    for (auto i = 0; i < 8; i++) {
      CP.write(LOW);
      DS.write(value);
      CP.write(HIGH);
    }
  }

  void endWrite()
  {
    PL.write(HIGH);
  }

};
