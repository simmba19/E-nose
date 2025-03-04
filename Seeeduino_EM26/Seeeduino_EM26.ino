int analogPins[] = {A0, A1, A2, A3, A4, A5}; // Array of analog pins
float voltage; // Array to store voltage values

void setup() {
  Serial.begin(9600); // Setup serial communication
}

void loop() {
  Serial.println("-------------");
  for (int i = 0; i < 6; i++) {
    int val = analogRead(analogPins[i]); // Read the input pin
    voltage = (val / 1023.0) * 5.0; // Convert to voltage
    String format="Pin A" + String(i) + ": " + String(voltage) + "V";
    Serial.println(format);
  }
  delay(1000); // Wait for a second before the next reading
}