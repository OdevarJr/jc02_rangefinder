#include "jc02_rangefinder.h"

Rangefinder::Rangefinder(Stream &serial) : serialPort(serial) {}

void Rangefinder::start() {
  byte cmd[8] = {0xAE, 0xA7, 0x04, 0x00, 0x0E, 0x12, 0xBC, 0xBE};
  serialPort.write(cmd, 8);
}

void Rangefinder::stop() {
  byte cmd[8] = {0xAE, 0xA7, 0x04, 0x00, 0x0F, 0x13, 0xBC, 0xBE};
  serialPort.write(cmd, 8);
}

void Rangefinder::reset() {
  byte cmd[9] = {0xAE, 0XA7, 0X05, 0X00, 0X0B, 0X00, 0X10, 0XBC, 0XBE};
  serialPort.write(cmd, 9);
}

void Rangefinder::singleMeasure() {
  byte cmd[8] = {0xAE, 0xA7, 0x04, 0x00, 0x05, 0x09, 0xBC, 0xBE};
  serialPort.write(cmd, 8);
}



bool Rangefinder::read() {
  if (serialPort.available() < 27) return false;

  byte packet[27];
  serialPort.readBytes(packet, 27);

  if (packet[0] != 0xAE || packet[1] != 0xA7 || packet[25] != 0xBC || packet[26] != 0xBE) return false;
  if (packet[4] != 0x85) return false;
  if (!_verifyChecksum(packet)) return false;

  byte *data = &packet[5];
  elevation      = _parseShort(data[0], data[1]) * 0.1;
  distance   	 = _parseShort(data[2], data[3]) * 0.1;
  sineHeight     = _parseShort(data[4], data[5]) * 0.1;
  horizRange     = _parseShort(data[6], data[7]) * 0.1;
  twoPointHeight = _parseShort(data[8], data[9]) * 0.1;
  azimuth        = _parseShort(data[10], data[11]) * 0.1;
  horizAngle     = _parseShort(data[12], data[13]) * 0.1;
  span           = _parseShort(data[14], data[15]) * 0.1;
  velocity       = _parseShort(data[16], data[17]) * 0.1;
  measureUnit    = data[18];

  return true;
}

bool Rangefinder::_verifyChecksum(byte *packet) {
  byte dataLength = packet[2];
  byte addr       = packet[3];
  byte cmd        = packet[4];

  uint16_t sum = dataLength + addr + cmd;
  for (int i = 5; i < 5 + (dataLength - 3); i++) {
    sum += packet[i];
  }

  byte checksum = packet[5 + (dataLength - 3)];
  return ((sum & 0xFF) == checksum);
}

int16_t Rangefinder::_parseShort(byte high, byte low) {
  return (int16_t)((high << 8) | low);
}