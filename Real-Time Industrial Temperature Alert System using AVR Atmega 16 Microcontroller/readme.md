# 🌡️ Industrial Temperature Monitoring and Alert System using ATmega16

This embedded systems project involves designing a real-time temperature monitoring and alert system using the **AVR ATmega16** microcontroller and **LM35 temperature sensor**. It simulates a practical industrial scenario where overheating can lead to equipment failure or hazards — hence timely alerts are critical.

---

## 🔧 Features

- ✅ Real-time temperature sensing using **LM35 sensor**
- ✅ Efficient data acquisition using **ADC with interrupts**
- ✅ Displays current temperature on a **16x2 LCD**
- ✅ Triggers **buzzer alert** when temperature exceeds a threshold (e.g., 40°C)
- ✅ Developed and tested on both **Proteus simulation** and **real AVR hardware**

---

## 🛠️ Technologies Used

- **Microcontroller:** ATmega16 (AVR, 8 MHz)
- **Programming Language:** Embedded C (AVR-GCC / Atmel Studio)
- **Simulation:** Proteus Design Suite
- **Interfaces Used:**  
  - ADC (Analog to Digital Converter)  
  - 16x2 LCD (parallel interface)  
  - Digital Output (Buzzer)  
  - External Interrupts

---

## ⚙️ Working Principle

1. **LM35** outputs analog voltage proportional to temperature.  
2. **ADC** of ATmega16 reads this analog value and converts it to digital.  
3. The digital value is converted to temperature (in °C) and displayed on LCD.  
4. If temperature > **40°C**, the **buzzer turns ON** continuously as an alert.  
5. If temperature ≤ 40°C, the system operates normally without alerts.

---

## 🖥️ LCD Output Format

Temp: 32.4 C
Status: NORMAL


If temperature crosses threshold:

Temp: 42.6 C
Status: ALERT!!!


---

## 🚨 Buzzer Alert Logic

- **Threshold Temp:** 40°C (can be modified in code)
- If temperature > 40 → Buzzer ON
- Else → Buzzer OFF

---



## 📂 Project Structure

├── main.c # Source code
├── README.md # This documentation
├── proteus_project.pdsprj # Proteus simulation file
├── images/
│ └── proteus_screenshot.png


---

## 📚 Learning Outcomes

- Interfacing analog sensors with microcontrollers
- Interrupt-based ADC programming in AVR
- Real-time LCD interfacing and display logic
- Safety and alert system design for industrial applications
- Simulation + Hardware integration workflow

---

## 💡 Future Enhancements

- Add UART for serial monitoring via PC
- Replace buzzer with GSM alert (SMS)
- Store temperature logs in EEPROM
- Add fan control using relay/MOSFET for automatic cooling

---

## 🙋‍♂️ Author

**Prabhat Kumar**  
Electronics & Communication Engineering  
Embedded Systems Enthusiast  
📧 choudharyprabhat25@gmail.com  


---

## 📎 License

This project is open-source and free to use for educational and academic purposes.
