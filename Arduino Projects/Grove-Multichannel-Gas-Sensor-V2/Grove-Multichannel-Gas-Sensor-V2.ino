#include <Multichannel_Gas_GMXXX.h>
#include <Wire.h>
GAS_GMXXX<TwoWire> gas;

void setup() {
  Serial.begin(115200);
  Serial.println("Setup starting...");
  gas.begin(Wire, 0x08); // use the hardware I2C
}

void loop() {
  int val;

  // GM102B NO2 sensor
  val = gas.getGM102B();
  Serial.print("Raw NO2: ");
  Serial.println(val);
  if (val > 999) val = 999;
  Serial.print("NO2: ");   
  Serial.println(gas.calcVol(val));

  // GM302B C2H5CH sensor
  val = gas.getGM302B();
  Serial.print("Raw C2H5CH: ");
  Serial.println(val);
  if (val > 999) val = 999;
  Serial.print("C2H5CH: ");  
  Serial.println(gas.calcVol(val)); 

  // GM502B VOC sensor
  val = gas.getGM502B();
  Serial.print("Raw VOC: ");
  Serial.println(val);
  if (val > 999) val = 999;
  Serial.print("VOC: ");  
  Serial.println(gas.calcVol(val)); 

  // GM702B CO sensor
  val = gas.getGM702B();
  Serial.print("Raw CO: ");
  Serial.println(val);
  if (val > 999) val = 999;
  Serial.print("CO: ");  
  Serial.println(gas.calcVol(val)); 

  delay(2000);
}