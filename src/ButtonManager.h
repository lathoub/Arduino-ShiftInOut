#pragma once

#define BITSINABYTE 8
#define TYPESIZE (sizeof(type) * BITSINABYTE)

template <class type, uint8_t size>
class ButtonManager
{
  class ButtonsState
  {
    private:
      const unsigned long debounceTime = 5;  // button debouncer, how many ms to debounce, 5+ ms is usually plenty
      unsigned long  buttonsTime [TYPESIZE * size];

    public:
      uint8_t        buttonsState[TYPESIZE * size]; // 2 = on or off
      uint8_t        count;

    private:
      void add(uint8_t index)
      {
        if (millis() - buttonsTime[count] >= debounceTime)
        {
            buttonsTime[count]  = millis();
            buttonsState[count] = index;
            count++;
        }
      }

      friend class ButtonManager; 
  };

  private:
    type _buffer[size];
    
    ButtonsState _buttonsState[2];

  public:
    void init(type value)
    {
        memset(_buffer, value, size * sizeof(type));
    }

    bool hasChanged(type* bitsIn)
    {
        // Optimization: do a quick check is *something* changed
        if (0 != memcmp(_buffer, bitsIn, size * sizeof(type)))
        {
            // no need to re-init _buttonState
            _buttonsState[0].count = 
            _buttonsState[1].count = 0;

            for (auto i = 0; i < size; i++)
            {
                for (auto j = 0; j < TYPESIZE; j++)
                {
                    const auto ud = bitRead(bitsIn[i], j);
                    if (bitRead(_buffer[i], j) != ud)
                        _buttonsState[ud].add((i * TYPESIZE) + j);
                }
            }
            memcpy(_buffer, bitsIn, size * sizeof(type));

            return true;
        }
        else
        {
            // no changes
            return false;
        }
    }

    ButtonsState* buttonsState(const bool upDown)
    {
        return &_buttonsState[upDown];
    }

};