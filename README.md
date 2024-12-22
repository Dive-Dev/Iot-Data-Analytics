# IoT Data Analytics with ESP8266 and DHT11

This project demonstrates how to use an ESP8266 microcontroller to read temperature and humidity data from a DHT11 sensor and send it to a server for data analytics using Python.

---

## **Directory Structure**

```
project-root/
├── esp8266/
│   └── dht11_esp8266/
│       └── dht11_esp8266.ino  # Arduino code for ESP8266
├── python-server/
│   ├── server.py              # Flask server to receive data from ESP8266
│   ├── sensor_data.json       # File to store received data
│   ├── data_analysis.py       # Python script for data analysis and visualization
└── README.md                  # Documentation
```

---

## **Components Required**

- ESP8266 NodeMCU
- DHT11 Temperature and Humidity Sensor
- Jumper Wires
- Breadboard
- USB Cable for ESP8266

---

## **Hardware Setup**

1. Connect the DHT11 sensor:
   - **VCC** to **3.3V** on ESP8266.
   - **GND** to **GND** on ESP8266.
   - **DATA** to **GPIO4 (D2)** on ESP8266.
2. Power the ESP8266 using a USB cable connected to your computer or a power source.

---

## **ESP8266 Code**

### **Steps to Upload Code**

1. Open the `dht11_esp8266.ino` file in the Arduino IDE.
2. Install the required libraries:
   - `ESP8266WiFi`
   - `DHT`
   - `ESP8266HTTPClient`
3. Update the Wi-Fi credentials in the code:
   ```cpp
   const char* ssid = "your_wifi_ssid";
   const char* password = "your_wifi_password";
   ```
4. Update the server URL:
   ```cpp
   const char* serverUrl = "http://<your_server_ip>:5000/data";
   ```
5. Select the correct board and port in the Arduino IDE:
   - **Board**: NodeMCU 1.0 (ESP-12E Module)
   - **Port**: COM port of the ESP8266.
6. Upload the code to the ESP8266.

---

## **Python Flask Server**

### **Steps to Set Up the Server**

1. Navigate to the `python-server/` directory.
2. Install Python dependencies:
   ```bash
   pip install flask
   ```
3. Start the Flask server:
   ```bash
   python server.py
   ```
4. The server will run on `http://<your_server_ip>:5000`.

### **`server.py` Code Overview**

The server receives JSON data from the ESP8266 and stores it in `sensor_data.json` for further analysis.

---

## **Data Analytics with Python**

### **Steps to Analyze Data**

1. Use the `data_analysis.py` script to analyze and visualize the data stored in `sensor_data.json`.
2. Example analysis:

   ```python
   import json
   import matplotlib.pyplot as plt

   # Load data from JSON file
   with open('sensor_data.json', 'r') as file:
       data = json.load(file)

   timestamps = [entry['timestamp'] for entry in data]
   temperatures = [entry['temperature'] for entry in data]
   humidities = [entry['humidity'] for entry in data]

   # Plot temperature and humidity
   plt.plot(timestamps, temperatures, label='Temperature')
   plt.plot(timestamps, humidities, label='Humidity')
   plt.legend()
   plt.show()
   ```

---

## **Testing the Setup**

1. Open the Serial Monitor in the Arduino IDE to view logs.
2. Verify that the ESP8266 connects to Wi-Fi and sends data to the server.
3. Check the server console to confirm receipt of the data.

---

## **Troubleshooting**

- **Wi-Fi Connection Issues**:
  - Verify the SSID and password.
  - Ensure the ESP8266 is within range of the Wi-Fi router.
- **DHT11 Reading Issues**:
  - Check the wiring and connections.
  - Ensure the DHT11 sensor is functional.
- **Server Not Receiving Data**:
  - Verify the server IP address and port.
  - Check the server logs for errors.

---

## **Future Improvements**

- Add database integration for persistent storage.
- Implement real-time data visualization on a web dashboard.
- Use advanced sensors for more accurate readings.

---

## **References**

- [ESP8266WiFi Library Documentation](https://arduino-esp8266.readthedocs.io/en/latest/)
- [DHT Sensor Library](https://github.com/adafruit/DHT-sensor-library)
- [Flask Documentation](https://flask.palletsprojects.com/)

---

## **License**

This project is licensed under the MIT License.
