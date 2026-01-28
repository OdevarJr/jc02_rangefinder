#ifndef jc02_rangefinder_h
#define jc02_rangefinder_h

#include <Arduino.h>

class Rangefinder {
  public:
    Rangefinder(Stream &serial);

    void start();
	void stop();
	void reset();
	void singleMeasure();
    bool read();

    // Parsed values
    float elevation;
    float distance;
    float sineHeight;
    float horizRange;
    float twoPointHeight;
    float azimuth;
    float horizAngle;
    float span;
    float velocity;
    uint8_t measureUnit;

  private:
    Stream &serialPort;

    bool _verifyChecksum(byte *packet);
    int16_t _parseShort(byte high, byte low);
};

#endif