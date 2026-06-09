# IOT-Weather-Monitoring-System
ESP Weather Station using MQTT, Node-RED Dashboard and Telegram Alerts.

IoT Weather Monitoring System

Overview

The IoT Weather Monitoring System is a real-time weather monitoring solution that collects environmental data from sensors connected to an ESP32 microcontroller and displays the information on a dashboard.

The system monitors weather parameters such as temperature, humidity, and atmospheric pressure. Data is transmitted using MQTT and visualized through a dashboard, enabling users to monitor environmental conditions remotely.

Features

- Real-time temperature monitoring
- Real-time humidity monitoring
- Atmospheric pressure monitoring
- MQTT-based communication
- Interactive dashboard with gauges
- Live sensor data visualization
- Remote monitoring capability
- Scalable architecture for additional sensors

Technologies Used

Hardware

- ESP32 Development Board
- Weather Sensors (Temperature, Humidity, Pressure)

Software

- Arduino IDE
- MQTT Protocol
- Node-RED
- Dashboard UI
- Git
- GitHub

System Architecture

1. Sensors collect environmental data.
2. ESP32 reads sensor values.
3. Data is published to MQTT topics.
4. Node-RED subscribes to MQTT topics.
5. Dashboard displays live sensor readings.

Dashboard Components

- Temperature Gauge
- Humidity Gauge
- Pressure Gauge
- Real-Time Data Monitoring

Project Structure

- Source code for ESP32
- Node-RED flow configuration
- Dashboard configuration
- Project screenshots
- Documentation

Screenshots

## screenshots

### Dashboard
![Dashboard](screenshots/dashboard-gauges-png)



How to Run

1. Clone the repository.
2. Open the ESP32 code in Arduino IDE.
3. Configure Wi-Fi credentials.
4. Configure MQTT broker settings.
5. Upload the code to ESP32.
6. Import the Node-RED flow.
7. Start the MQTT broker.
8. Launch the dashboard.
9. Monitor real-time weather data.

Future Improvements

- Historical data storage
- Data analytics
- Mobile application support
- Weather forecasting integration
- Alert and notification system
- Cloud database integration

Learning Outcomes

This project demonstrates:

- IoT System Design
- ESP32 Programming
- MQTT Communication
- Node-RED Development
- Dashboard Creation
- Real-Time Data Visualization

Author

O. Puja Hemanth

Electrical and Electronics Engineering

Interested in Embedded Systems, IoT, and Artificial Intelligence.
