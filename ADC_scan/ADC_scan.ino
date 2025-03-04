int sensorPin = A0; // Analog input pin that the sensor is attached to
float voltage;
float inputVoltage;

void setup() {
    Serial.begin(115200); // Initialize serial communication at 115200 bits per second
}

void loop() {
    int sensorValue = analogRead(sensorPin); // Read the analog input
    voltage = sensorValue * (3.3 / 1023.0); // Convert the analog reading to voltage (assuming a 3.3V reference)
    inputVoltage = voltage * 2; // Scale back up (assuming a 1:1 voltage divider)

    Serial.print("Measured Voltage: ");
    Serial.print(inputVoltage);
    Serial.println(" V");

    delay(1000); // Wait for a second before taking another reading
}
