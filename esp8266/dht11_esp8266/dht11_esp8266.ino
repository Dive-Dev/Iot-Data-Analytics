#include <ESP8266WiFi.h>
#include <DHT.h>
#include <ESP8266HTTPClient.h>

#define DHTPIN 4        // Pin where the DHT11 data pin is connected (GPIO4/D2)
#define DHTTYPE DHT11   // Define the sensor type (DHT11)

DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor

// Wi-Fi credentials
const char* ssid = "Divesh-2.4G";     // Your Wi-Fi SSID
const char* password = "8884986140";  // Your Wi-Fi password

// Server URL to send the data to
const char* serverUrl = "http://192.168.1.7:5000/data";  // Server URL

void setup() {
  Serial.begin(115200);  // Start the serial communication for debugging
  dht.begin();           // Initialize the DHT sensor
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);  // Start connecting to the Wi-Fi network

  // Wait for Wi-Fi connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);  // Wait for 1 second before checking again
    Serial.println("Connecting to WiFi...");  // Print the connection status
  }
  Serial.println("Connected to WiFi");  // Print a message once connected to Wi-Fi
}

void loop() {
  delay(2000);  // Wait for 2 seconds between measurements

  // Reading temperature and humidity from the DHT11 sensor
  float humidity = dht.readHumidity();  // Get the humidity value
  float temperature = dht.readTemperature();  // Get the temperature value

  // Check if reading failed (NaN = Not a Number)
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");  // Print error if sensor reading fails
    return;  // Exit the loop if reading failed
  }
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%  Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");

  // Create HTTP client to send data to the server
  WiFiClient client;  // Create a WiFiClient object
  HTTPClient http;    // Create an HTTPClient object
  http.begin(client, serverUrl);  // Use the WiFiClient object with the server URL
  http.addHeader("Content-Type", "application/json");  // Set the header for JSON data

  // Prepare JSON data to send to the server
  String jsonData = "{\"temperature\": " + String(temperature) + ", \"humidity\": " + String(humidity) + "}";

  // Send the POST request with the JSON data
  int httpResponseCode = http.POST(jsonData);

  // Check the response code from the server
  if (httpResponseCode > 0) {
    Serial.println("Data sent successfully");  // Print success message if data is sent
  } else {
    Serial.print("Error sending data. HTTP response code: ");
    Serial.println(httpResponseCode);  // Print error message if data transfer fails
  }

  // End the HTTP connection after the request is sent
  http.end();
}
