int analogPins[] = {A0, A1, A2, A3, A4, A5}; // Array of analog pins
float voltage; // Variable to store voltage values
float resistance; // Variable to store resistance values
const float Vin = 5.0; // Reference voltage

void setup() {
  Serial.begin(9600); // Setup serial communication
}

void loop() {
  Serial.println("-------------");
  for (int i = 0; i < 6; i++) {
    int val = analogRead(analogPins[i]); // Read the input pin
    voltage = (val / 1023.0) * Vin; // Convert to voltage
    if (i < 3) {
      resistance = calcR(voltage, 2000); // Calculate resistance for 2k ohm(JP1) resistor
    } else {
      resistance = calcR(voltage,10000); // Calculate resistance for 10k ohm(JP2) resistor
    }
    String format = "Pin A" + String(i) + ": " + String(voltage) + "V, " +"Sensor res:"+ String(resistance) + " ohms";
    Serial.println(format);
  }
  delay(1000); // Wait for a second before the next reading
}

float calculateResistance2k(float Vout) {
  const float R1 = 2000; // 2k ohm resistor
  return R1 * ((Vin / Vout) - 1);
}

float calculateResistance10k(float Vout) {
  const float R1 = 10000; // 10k ohm resistor
  return R1 * ((Vin / Vout) - 1);
}

float calcR(float Vout, float resistance){
  return resistance * ((Vin / Vout) - 1);
}
