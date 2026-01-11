# HomeGuardX 🏠🔐  
### Smart Home Automation & Security Ecosystem (ESP32)

HomeGuardX is an ESP32-based IoT smart home automation and security system developed and simulated using **Wokwi**. The project integrates multiple sensors and actuators to demonstrate how modern smart home systems perform automation, security monitoring, and intelligent access control using embedded logic.

---

## 🚀 Features

- 🌡️ Automatic temperature-based appliance control
- 💡 Smart lighting using ambient light sensing
- 🚨 Motion-based intrusion detection
- 🚪 Automated door control using servo motor
- 🔐 Normal Mode & Security Mode switching
- 🧠 Centralized automation logic
- ⏱️ Non-blocking execution using `millis()`
- 🧪 Fully simulated on **Wokwi**

---

## 🧩 Core IoT Modules

### 1️⃣ Intelligent Environment Monitoring
- Thermistor/analog temperature sensor
- Fan simulated using LED
- Buzzer alert on high temperature
- Automatic shutdown when temperature normalizes

### 2️⃣ Smart Lighting Automation
- LDR-based ambient light detection
- Lights turn ON in darkness
- Lights turn OFF in daylight

### 3️⃣ Intrusion Detection & Security Alerts
- IR motion sensor
- LED flashing and buzzer alert on detection
- Stronger alerts in Security Mode

### 4️⃣ Smart Door Automation
- Push button as doorbell
- Servo motor rotates 90° to open door
- LED welcome indicator
- Auto-close after delay

### 5️⃣ System Mode Controller
- Toggle button to switch modes
- 🟢 Green LED → Normal Mode
- 🔴 Red LED → Security Mode

### 6️⃣ Integrated Home Automation Engine
- Reads all sensor inputs
- Controls actuators concurrently
- Uses non-blocking logic
- Acts as a smart home control hub

---

## 🛠️ Tech Stack

### Microcontroller
- ESP32 Dev Module

### Simulation Platform
- Wokwi (Online ESP32 Simulator)

### Sensors
- Temperature Sensor (Thermistor / Analog sensor)
- LDR (Light Dependent Resistor)
- IR Motion Sensor

### Actuators
- Servo Motor
- LEDs
- Buzzer

### Development Tools
- Arduino IDE
- Serial Monitor
- Wokwi Simulator

---

## 📚 Libraries Used

- `Arduino.h`  
- `ESP32Servo.h`  
- `analogRead()` (ESP32 ADC)
- `millis()


> ⚠️ No external IoT cloud libraries are required for basic functionality.  
> The project focuses on **embedded automation logic**.

---
