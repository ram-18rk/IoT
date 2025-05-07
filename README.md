# 🛡️ IoT Radar-Based Object Detection & Tracking System

A smart radar system built using **ESP32**,  **ultrasonic sensor**, and **servo motor** to detect and track objects in real-time. Data is visualized through a sleek web interface, creating a live radar effect just like in sci-fi movies — but powered by microcontrollers.

> 🎯 Ideal for security systems, smart robotics, and autonomous mapping.

---

## 🔍 Overview

This project uses a **rotating ultrasonic sensor** mounted on a servo motor to scan the environment. It detects objects within range and sends real-time distance and angle data from the ESP32 to the ESP32 via wireless communication. JavaScript for live object detection sketch in processing 4.

---

## ⚙️ Tech Stack

- **Microcontrollers:** ESP32 (scanner), ESP32 (receiver)
- **Sensors:** HC-SR04 ultrasonic sensor
- **Actuation:** Servo motor (165° sweep),Servo motor mounted with camera/wepon(optional)
- **Communication:** Wi-Fi / ESP-NOW / MQTT
- **Frontend:** JavaScript 
- **Security:** Optional TLS encryption for MQTT/Web

---

## 🧠 Features

✅ Real-time object detection & angle calculation  
✅ Servo-powered 165° sweep  
✅ Wireless data transmission between two ESP32  
✅ Interactive web-based radar interface   
✅ Easily customizable for robotics or security zones  

---

## 🧰 Bill of Materials

| Component         | Quantity | Notes                           |
|------------------|----------|---------------------------------|
| ESP32            | 1        | Transmits sensor data           |
| ESP32          | 1        | Receives data        |
| HC-SR04 Sensor   | 1        | Measures distance               |
| Servo Motor (SG90)| 2      | Rotates the ultrasonic sensor   |
| Breadboard       | 1        | Prototyping                     |
| Jumper Wires     | n/a      | For connections                 |

---

## 🛠️ Setup Instructions

### 1️⃣ Hardware Assembly
- Connect **HC-SR04** and **Servo** to **ESP32**
- Power the **ESP32** via USB or external source
- Reference the circuit diagram: `hardware/circuit_diagram.png`

### 2️⃣ Upload Code
- Flash `esp32_transmitter.ino` to the ESP32
- Flash `esp32_receiver.ino` to the ESP32
- Adjust SSID, password, and IPs as needed in the code

### 3️⃣ Run the Radar
- Open `radar_web_interface.html` in processing 4

---



---


---

## 📂 Project Structure

