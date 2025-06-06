# Smart-Water-System
IoT-based smart water management for buildings 🚰

---

# Smart Water Management System 💧

An automated water level monitoring and pump control system using **Arduino Uno**, **ultrasonic sensor**, and **RTC module**, designed to reduce water wastage, prevent pump damage, and promote energy-efficient tank management in residential settings.

---

## 🔧 Key Features
- 🚰 Automated pump control via level thresholds  
- ⏰ RTC-based daily water usage lock system  
- 📟 Real-time LCD display with water level & status  
- 🔴🟡 LED indicators for tank status alerts  
- ⚙️ Reliable offline operation, energy-efficient and low maintenance

---

## 🛠️ Components Used
- Arduino Uno  
- Ultrasonic Sensor (HC-SR04)  
- RTC Module (DS3231)  
- 1-Channel Relay Module  
- Mini DC Water Pump  
- 16x2 LCD Display with I²C  
- LEDs (Red & Yellow), Resistors  
- Breadboard, Jumper Wires  
- 5V USB Power Supply

---

## ⚙️ System Workflow

- Ultrasonic sensor continuously monitors tank level  
- When water is **below the lower threshold**, the pump turns ON and the Red LED lights up  
- When the tank reaches the **upper threshold**, the pump turns OFF and locks for the day; Yellow LED lights up  
- RTC resets the system at midnight  
- LCD displays current water level and pump status in real time

---

## 💡 Applications
- Automated tank management in homes & apartments  
- School/hostel water monitoring  
- Rural & urban water conservation setups  
- Indoor gardens or irrigation systems

---

## 🚀 Future Improvements
- Add water flow sensors for precision usage tracking  
- Mobile app or web dashboard integration  
- ThingSpeak/IoT-based monitoring & control

---

## 👥 Team Members

- **Lavanya A**  
- **Aishwarya S**  
- **Kavinila M**  
*B.E. Electronics and Communication Engineering, SRIT (2025)*

---

## 👩‍💻 Author Note

*System design, embedded development, and hardware implementation led by Lavanya A*  
- Sensor integration, display control, and pump logic  
- Real-time scheduling with RTC module  
- Circuit testing and debugging

🔗 [LinkedIn – Lavanya A](https://www.linkedin.com/in/lavanya-arulkumar/)

---

> ⚠️ This project was developed as part of our undergraduate design project at SRIT (2025).
