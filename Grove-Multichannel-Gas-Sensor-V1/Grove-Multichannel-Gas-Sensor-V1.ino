// Read Data from Grove - Multichannel Gas Sensor
#include <Wire.h>
#include "MutichannelGasSensor.h"
#include <Multichannel_Gas_GMXXX.h>
GAS_GMXXX<TwoWire> volt;

void setup()
{
    Serial.begin(115200);  // start serial for output
    Serial.println("power on!");
    gas.begin(0x04);//the default I2C address of the slave is 0x04
    gas.powerOn();
    Serial.print("Firmware Version = ");
    Serial.println(gas.getVersion());
}
float v_o;
void loop()
{
    
    float c;
    Serial.println("----New Data----");
    c = gas.measure_NH3();
    Serial.print("The concentration of NH3 is ");
    if(c>=0) Serial.print(c);
    else Serial.print("invalid");
    Serial.println(" ppm");
    Serial.print("Voltage: ");
    Serial.println(volt.calcVol(c));
    

    c = gas.measure_CO();
    Serial.print("The concentration of CO is ");
    if(c>=0) Serial.print(c);
    else Serial.print("invalid");
    Serial.println(" ppm");
    Serial.print("Voltage: ");
    Serial.println(volt.calcVol(c));

    c = gas.measure_NO2();
    Serial.print("The concentration of NO2 is ");
    if(c>=0) Serial.print(c);
    else Serial.print("invalid");
    Serial.println(" ppm");
    Serial.println("Voltage: ");
    Serial.println(volt.calcVol(c));

    c = gas.measure_C3H8();
    Serial.print("The concentration of C3H8 is ");
    if(c>=0) Serial.print(c);
    else Serial.print("invalid");
    Serial.println(" ppm");
    Serial.println("Voltage: ");
    Serial.println(volt.calcVol(c));

    c = gas.measure_C4H10();
    Serial.print("The concentration of C4H10 is ");
    if(c>=0) Serial.print(c);
    else Serial.print("invalid");
    Serial.println(" ppm");
    Serial.println("Voltage: ");
    Serial.println(volt.calcVol(c));

    c = gas.measure_CH4();
    Serial.print("The concentration of CH4 is ");
    if(c>=0) Serial.print(c);
    else Serial.print("invalid");
    Serial.println(" ppm");
    Serial.println("Voltage: ");
    Serial.println(volt.calcVol(c));

    c = gas.measure_H2();
    Serial.print("The concentration of H2 is ");
    if(c>=0) Serial.print(c);
    else Serial.print("invalid");
    Serial.println(" ppm");
    Serial.println("Voltage: ");
    Serial.println(volt.calcVol(c));

    c = gas.measure_C2H5OH();
    Serial.print("The concentration of C2H5OH is ");
    if(c>=0) Serial.print(c);
    else Serial.print("invalid");
    Serial.println(" ppm");
    Serial.println("Voltage: ");
    Serial.println(volt.calcVol(c));

    Serial.println("----Resistance------");
    Serial.print("The R0 and Rs of CH3 is ");
    Serial.println(gas.getR0(0));
    Serial.println(gas.getRs(0));
    Serial.print("volatge for CH3 is");
    v_o = v_out(gas.getR0(0), gas.getRs(0));
    Serial.println(v_o);
    
    Serial.print("The R0 and Rs of CO is ");
    Serial.println(gas.getR0(1));
    Serial.println(gas.getRs(1));
    Serial.print("volatge for CO is");
    v_o = v_out(gas.getR0(1), gas.getRs(1));
    Serial.println(v_o);

    Serial.print("volatge is");
    Serial.print("The R0 and Rs of NO2 is ");
    Serial.println(gas.getR0(2));
    Serial.println(gas.getRs(2));
    Serial.print("volatge for NO2 is");
    v_o = v_out(gas.getR0(2), gas.getRs(2));
    Serial.println(v_o);


    delay(1000);
}


float v_out(float r_0, float r_s){
  float v_o;
  v_o = 3.3 * (r_s / (r_s + r_0)); //check the voltage - is it 3.3v or 5v?
  return v_o;
}
