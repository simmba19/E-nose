import pandas as pd
import matplotlib.pyplot as plt

# Read the data from the Excel file
df = pd.read_excel('C:/Users/IoT Lab/Documents/sensor_data.xlsx')

# Convert the 'Timestamp' column to datetime
df['Timestamp'] = pd.to_datetime(df['Timestamp'])

# Resample the data to 10-second intervals
df.set_index('Timestamp', inplace=True)
df_resampled = df.resample('10S').mean().reset_index()

# Plot the data for each pin
for pin in df_resampled.columns:
    if pin != 'Timestamp':
        plt.figure(figsize=(10, 6))
        plt.plot(df_resampled['Timestamp'], df_resampled[pin], label=pin)
        plt.xlabel('Time')
        plt.ylabel('Voltage (V)')
        plt.title(f'Voltage Readings for {pin}')
        plt.xticks(rotation=45)
        plt.legend()
        plt.grid(True)
        plt.savefig(f'C:/Users/IoT Lab/Documents/{pin}_voltage_plot.png')
        plt.show()