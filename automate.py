import serial
import pandas as pd
import time

# Set up the serial connection
try:
    ser = serial.Serial('COM4', 9600)  # Replace 'COM4' with your port
    print("Serial connection established.")
except serial.SerialException as e:
    print(f"Error opening serial port: {e}")
    exit()

# Initialize lists to store data and timestamps
data = {f'Pin A{i} Voltage': [] for i in range(6)}
data.update({f'Pin A{i} Resistance': [] for i in range(6)})
timestamps = []

start_time = time.time()

while time.time() - start_time < 60:  # Collect data for 1 minute
    if ser.in_waiting > 0:
        line = ser.readline().decode('utf-8').rstrip()
        current_time = time.strftime('%Y-%m-%d %H:%M:%S')
        print(f"Received at {current_time}: {line}")  # Debugging print with timestamp
        # Parse the received line and store the data
        if "Pin" in line and ": " in line:
            try:
                pin, values = line.split(": ")
                voltage, resistance = values.split(", ")
                data[f'{pin} Voltage'].append(float(voltage.replace("V", "")))
                data[f'{pin} Resistance'].append(float(resistance.replace("Sensor res:", "").replace(" ohms", "")))
                if len(timestamps) < len(data[f'{pin} Voltage']):
                    timestamps.append(current_time)
            except ValueError as e:
                print(f"Error parsing line '{line}': {e}")

# Ensure all lists are the same length by padding with None
max_length = max(len(lst) for lst in data.values())
for key in data:
    while len(data[key]) < max_length:
        data[key].append(None)
while len(timestamps) < max_length:
    timestamps.append(None)

# Create a DataFrame and save to Excel
df = pd.DataFrame(data)
df['Timestamp'] = timestamps
df.to_excel('C:/Users/IoT Lab/Documents/sensor_data.xlsx', index=False)
print("Data saved to C:/Users/IoT Lab/Documents/sensor_data.xlsx")