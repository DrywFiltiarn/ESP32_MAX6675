#ifndef _MAX6675_H_
#define _MAX6675_H_
#include <Arduino.h>
#include <SPI.h>
#include "stdint.h"

#define MAX6675_SPI_SETTINGS    (SPISettings(1000000, MSBFIRST, SPI_MODE1))
#define MAX6675_TC_OPEN_BIT     0x04
#define MAX6675_TC_OPEN         -1.0
#define MAX6675_READ_PERIOD     250
#define MAX6675_CONV_RATIO      0.25
#define MAX6675_THERMAL_OFFSET  -16. // Offset temperature to compensate for cold-junction errors due to
                                    // non-themrocouple screw terminals that induce a thermocouple effect

class MAX6675 {
  public:
    MAX6675(int8_t clk, int8_t cs, int8_t miso, int8_t mosi);

    float readC(void);
    float readF(void);
    uint16_t _result;

  private:
    int8_t _clk, _cs, _miso, _mosi;
    uint32_t _lastCallTime;
    float _currentTemp;
    void readSPI(void);
};

#endif