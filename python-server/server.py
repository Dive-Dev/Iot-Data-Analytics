from flask import Flask, request, jsonify
import json

app = Flask(__name__)

# Endpoint to receive data
@app.route('/data', methods=['POST'])
def receive_data():
    try:
        # Get the JSON data from the request
        data = request.get_json()
        
        # Extract temperature and humidity from the data
        temperature = data['temperature']
        humidity = data['humidity']
        
        # Print the received data
        print(f"Temperature: {temperature}°C, Humidity: {humidity}%")
        
        # Save the data to a file or database for analytics
        with open("sensor_data.json", "a") as file:
            file.write(json.dumps(data) + "\n")
        
        return jsonify({"status": "success"}), 200
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)}), 400

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)  # Run the server on port 5000
