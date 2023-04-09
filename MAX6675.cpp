#include "MAX6675.h"

MAX6675::MAX6675(int8_t clk, int8_t cs, int8_t miso, int8_t mosi) {
  _clk = clk, _cs = cs, _miso = miso, _mosi = mosi;

  pinMode(cs, OUTPUT);
  digitalWrite(cs, HIGH);
  SPI.begin(clk, miso, mosi, cs);

  _lastCallTime = 0;
}

float MAX6675::readC(void) {
  uint16_t result;

  if (millis() - _lastCallTime >= MAX6675_READ_PERIOD) {
    readSPI();
    if (_result & MAX6675_TC_OPEN_BIT) return MAX6675_TC_OPEN;
    _currentTemp = (_result >> 3) * MAX6675_CONV_RATIO;
  }
  return _currentTemp + MAX6675_THERMAL_OFFSET;
}

float MAX6675::readF(void) {
  return readC() * 9.0 / 5.0 + 32;
}

void MAX6675::readSPI(void) {
  SPI.beginTransaction(MAX6675_SPI_SETTINGS);
  digitalWrite(_cs, LOW);
  _result = SPI.transfer16(0x00);
  digitalWrite(_cs, HIGH);
  SPI.endTransaction();
  _lastCallTime = millis();
}