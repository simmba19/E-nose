#include <Multichannel_Gas_GMXXX.h>
#include <Wire.h>
GAS_GMXXX<TwoWire> gas;
const float VRefer = 5.0;       // voltage of adc reference

const int pinAdc = A0;
void setup() {
      Serial.begin(9600);           //  setup serial
        // gas.begin(Wire, 0x08); // use the hardware I2C

    }

    void loop(){
      // v2GasMonitor();
      readO2();
      delay(2000);
    }

void v2GasMonitor(){
   int val;
      // GM102B NO2 sensor
      val = gas.getGM102B();
      if (val > 999) val = 999;
      Serial.print("NO2: ");
      Serial.println(gas.calcVol(val));

      // GM302B C2H5CH sensor
      val = gas.getGM302B();
      if (val > 999) val = 999;
      Serial.print("C2H5CH: ");
      Serial.println(gas.calcVol(val));

      // GM502B VOC sensor
      val = gas.getGM502B();
      if (val > 999) val = 999;
      Serial.print("VOC: ");
      Serial.println(gas.calcVol(val));

      // GM702B CO sensor
      val = gas.getGM702B();
      if (val > 999) val = 999;
      Serial.print("CO: ");
      Serial.println(gas.calcVol(val));

}

void readO2(){
    // put your main code here, to run repeatedly:
    float Vout =0;
    Serial.print("Vout =");

    Vout = readO2Vout();
    Serial.print(Vout);
    Serial.print(" V, Concentration of O2 is ");
    Serial.println(readConcentration());
}

float readO2Vout()
{
    long sum = 0;
    for(int i=0; i<32; i++)
    {
        sum += analogRead(pinAdc);
    }
    
    sum >>= 5;
    
    float MeasuredVout = sum * (VRefer / 1023.0);
    return MeasuredVout;
}

float readConcentration()
{
    // Vout samples are with reference to 3.3V
    float MeasuredVout = readO2Vout();
    
    //float Concentration = FmultiMap(MeasuredVout, VoutArray,O2ConArray, 6);
    //when its output voltage is 2.0V,
    float Concentration = MeasuredVout * 0.21 / 2.0;
    float Concentration_Percentage=Concentration*100;
    return Concentration_Percentage;
}