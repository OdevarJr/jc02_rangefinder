#include <SoftwareSerial.h>
#include <jc02_rangefinder.h>

SoftwareSerial mySerial(10, 11); // RX, TX
Rangefinder rf(mySerial);

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600);

  rf.start();
}

void loop() {
  if (rf.read()) {
    Serial.print("Distance: "); Serial.print(rf.distance); Serial.println(" m");
  }
}