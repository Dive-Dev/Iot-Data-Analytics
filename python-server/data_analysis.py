import pandas as pd
import matplotlib.pyplot as plt
import json

# Load the sensor data
data = []
with open("sensor_data.json", "r") as file:
    for line in file:
        data.append(json.loads(line))

# Convert data to a DataFrame
df = pd.DataFrame(data)

# Convert temperature and humidity to numeric values
df['temperature'] = pd.to_numeric(df['temperature'])
df['humidity'] = pd.to_numeric(df['humidity'])

# Plot the temperature and humidity
plt.figure(figsize=(10, 5))

# Plot temperature
plt.subplot(1, 2, 1)
plt.plot(df['temperature'], label='Temperature (°C)', color='r')
plt.title('Temperature over Time')
plt.xlabel('Time')
plt.ylabel('Temperature (°C)')

# Plot humidity
plt.subplot(1, 2, 2)
plt.plot(df['humidity'], label='Humidity (%)', color='b')
plt.title('Humidity over Time')
plt.xlabel('Time')
plt.ylabel('Humidity (%)')

plt.tight_layout()
plt.show()

# You can also compute statistics like average temperature, humidity, etc.
avg_temperature = df['temperature'].mean()
avg_humidity = df['humidity'].mean()

print(f"Average Temperature: {avg_temperature}°C")
print(f"Average Humidity: {avg_humidity}%")
