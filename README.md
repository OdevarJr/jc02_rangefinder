# JC-02-1 UART RANGEFINDER MODULE LIBRARY
![JC02-1](https://github.com/OdevarJr/jc02_rangefinder/blob/main/pictures/rangefinder.png)

This library is intended to interface an Arduino board with cheap Chinese JC02-1 UART rangefinder series, that have model with allegated range from 600 to 1200 meters.

### Link to buy the module (last access in 2024/01/28):
https://pt.aliexpress.com/item/1005010430761656.html?spm=a2g0o.order_list.order_list_main.39.79f0caa4c7XaPT&gatewayAdapt=glo2bra
### The original vendor Chinese manuals:
https://github.com/OdevarJr/jc02_rangefinder/blob/main/manual/JC02-1%20%E6%B5%8B%E8%B7%9D%E6%A8%A1%E7%BB%84%E4%B8%AD%E6%96%87%E8%AF%B4%E6%98%8E%E4%B9%A6%20%2020251107%2015%20.pdf
### The original vendor English manual:
https://github.com/OdevarJr/jc02_rangefinder/blob/main/manual/JC02-1%20%E8%8B%B1%E6%96%87.pdf

This library relies on Stream. So, this library is supposed to work with any Arduino/ESP board. Serial or SoftwareSerial should be used depending on the board used. 

## Object declaration
`Rangefinder myRangefinder(Stream &serial)`

## Functions:
-	`start()` – With this command, the module will start to do measurements continuously, until receive a STOP command.
- `stop()` – With this command, the module will stop to do countinuous measurements.
- `reset()` – Reset’s the module. There’s no return for this command.
- `singleMeasure()` – With this command, the module will perform only one single measurement and stops. 
- `read` – Used to obtain the current measured values. Use it in your loop function to update the measurements. If you started a continuous measure command (with start), the values will be updated in real time. If you used a single measure command, the values will be the same until you do a new reading.

## Measured values available:
The module’s protocol has a total of 10 parameters that is returned to the user:
-	`elevation`       :  Elevation Angle (float)
-	`distance`        :  Crow flight Distance (float) [^1]
-	`sineHeight`      :  Sine Height (float)
-	`horizRange`      :  Horizontal Range (float)
-	`twoPointHeight`  :  Two-Point High (float)
-	`azimuth`         :  Azimuth (float)
-	`horizAngle`      :  Horizontal Angle (float)
-	`span`            :  Span (float)
-	`velocity`        :  Velocity (float)
-	`measureUnit`     :  Measure unit (uint8_t) - 1=meters, 2=feet, 3=inches 

## Usage example:
```
#include <SoftwareSerial.h>
#include <jc02_rangefinder.h>
SoftwareSerial mySerial(10, 11); // RX, TX
Rangefinder myRangefinder(mySerial);
void setup() {
  Serial.begin(115200);
  mySerial.begin(9600);
  myRangefinder.start();
}
void loop() {
  if (myRangefinder.read()) {
    Serial.print("Distance: "); Serial.print(myRangefinder.distance); Serial.println(" m");
  }
}
```

[^1]: For JC02-1 series modules, only this parameter works, and the measure unit is fixed in 1 (that means meters). All the other parameters will always be zero. **It's not a malfunction, but the module's feature.**
I kept all the fields available in case of future module's upgrades. But for now, only `distance` works (and this is the main reason to use this module, right? 😉).
