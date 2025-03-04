/*
    Multichannel_gas_sensor_V2.0.ino
    Description: A terminal for Seeed Grove Multichannel gas sensor V2.0.
    2019 Copyright (c) Seeed Technology Inc.  All right reserved.
    Author: Hongtai Liu(lht856@foxmail.com)
    2019-9-29

    The MIT License (MIT)
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:
    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.1  USA
*/

#include <Multichannel_Gas_GMXXX.h>
#include <Arduino.h>

#include "sensirion_common.h"
#include "sgp30.h"

// if you use the software I2C to drive the sensor, you can uncommnet the define SOFTWAREWIRE which in Multichannel_Gas_GMXXX.h.
#ifdef SOFTWAREWIRE
#include <SoftwareWire.h>
SoftwareWire myWire(3, 2);
GAS_GMXXX<SoftwareWire> gas;
#else
#include <Wire.h>
GAS_GMXXX<TwoWire> gas;
#endif

static uint8_t recv_cmd[8] = {};

void setup() {
  s16 err;
  u16 scaled_ethanol_signal, scaled_h2_signal;
  Serial.begin(9600);
  Serial.println("Setup starting...");
  // If you have changed the I2C address of gas sensor, you must to be specify the address of I2C.
  //The default addrss is 0x08;
  gas.begin(Wire, 0x08); // use the hardware I2C
  //gas.begin(MyWire, 0x08); // use the software I2C
  Serial.println("Setup 1...");
  // gas.setAddress(0x64); //change thee I2C address
#if defined(ESP8266)
  pinMode(15, OUTPUT);
  Serial.println("Setup 2...");
  digitalWrite(15, 1);
  Serial.println("Setup 3...");
  Serial.println("Set wio link power!");
  delay(500);
#endif
  /*Init module,Reset all baseline,The initialization takes up to around 15 seconds, during which
    all APIs measuring IAQ(Indoor air quality ) output will not change.Default value is 400(ppm) for co2,0(ppb) for tvoc*/
  Serial.println(sgp_probe());
  while (sgp_probe() != STATUS_OK) {
    Serial.println("SGP failed");
    while (1);
  }
  /*Read H2 and Ethanol signal in the way of blocking*/
  err = sgp_measure_signals_blocking_read(&scaled_ethanol_signal,
                                          &scaled_h2_signal);
  if (err == STATUS_OK) {
    Serial.println("get ram signal!");
  } else {
    Serial.println("error reading signals");
  }
  err = sgp_iaq_init();
  //
  Serial.println("Setup last...");
}

void loop() {
  Serial.println("Loop has begun...");
  uint8_t len = 0;
  uint8_t addr = 0;
  uint8_t i;
  uint32_t val = 0;
  s16 err = 0;
  u16 tvoc_ppb, co2_eq_ppm;

  val = gas.measure_NO2(); Serial.print("NO2: "); Serial.print(val); Serial.print("ppm"); Serial.print("  eq  ");
  Serial.print(gas.calcVol(val)); Serial.println("V");
  val = gas.measure_C2H5OH(); Serial.print("C2H5OH: "); Serial.print(val); Serial.print("ppm"); Serial.print("  eq  ");
  Serial.print(gas.calcVol(val)); Serial.println("V");
  val = gas.measure_VOC(); Serial.print("VOC: "); Serial.print(val); Serial.print("ppm"); Serial.print("  eq  ");
  Serial.print(gas.calcVol(val)); Serial.println("V");
  val = gas.measure_CO(); Serial.print("CO: "); Serial.print(val); Serial.print("ppm"); Serial.print("  eq  ");
  Serial.print(gas.calcVol(val)); Serial.println("V");
  err = sgp_measure_iaq_blocking_read(&tvoc_ppb, &co2_eq_ppm);
  if (err == STATUS_OK) {
    Serial.print("tVOC: ");
    Serial.print(tvoc_ppb);
    Serial.println("ppb");

    Serial.print("CO2eq: ");
    Serial.print(co2_eq_ppm);
    Serial.println("ppm");
  } else {
    Serial.println("error reading IAQ values\n");
  }
  Serial.println();

  delay(2000);
}
