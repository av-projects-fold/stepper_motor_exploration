# Stepper Motor Experiment Repository ⚙️

This open-source contribution project aims to develop a structured experiment setup for understanding stepper motors. Future students can use this repository to explore the behavior, limitations, and complexities of stepper motors through practical demonstrations.

---

## 📁 Project Structure

This repository contains multiple experiment demos, each showcasing different aspects of stepper motor control:

| Folder Name                           | Description                                                                                     |
|---------------------------------------|-------------------------------------------------------------------------------------------------|
| `Demo_A_0.1_manual_stepMode_&_RPM`    | Allows **manual control** of RPM and step modes to observe the motor’s behavior in real-time.   |
| `Demo_B_0.1_stepMode_Iteration`       | Iterates through step modes automatically after completing a full revolution at a set RPM.      |
| `Demo_C_0.1_incremental_RPM`          | Enables **manual step mode selection** while incrementally adjusting RPM after a user-defined cycle time. |
| `Demo_D_Incremental_stepDelay`        | Allows fine control of motor speed by letting users set the **step delay** directly.            |
| `Demo_E_smoothing_the_motor`          | Switches to different step modes at user-defined points as RPM changes, improving motor control. |

---

## 🚀 Purpose of the Project

- 📚 **Learning Tool**: Designed for students to understand stepper motors through hands-on experiments.
- 🔍 **Experiment Goals**:
   1. Analyze stepper motor behaviors at different step modes (Full, Half, etc.).
   2. Explore the effect of RPM and step delay adjustments.
   3. Measure and compare vibrations using piezo sensors and oscilloscopes.

---

## 🛠️ Hardware Setup & Requirements

1. **Hardware**:
   - Stepper motor (compatible with Arduino Micro).
   - Arduino Micro board.
   - Power supply and jumper wires.
   - Optional: Piezo sensors, oscilloscope, or audio logging tools for vibration analysis.

2. **Software**:
   - Arduino IDE (or any other compatible IDE).

---

## 📊 Expected Outputs

### **Demo A: Manual Step Mode and RPM**
- User sets the RPM and step mode manually.
- The motor runs at the specified settings, and the user can observe changes.

### **Demo B: Step Mode Iteration**
- The motor runs at a fixed RPM but iterates through all step modes after completing one revolution.
- Differences in motor sound and performance are noticeable at each step mode.

### **Demo C: Incremental RPM**
- RPM increments by a user-defined value after a specified cycle time.
- Step mode remains manually selectable.

### **Vibration Analysis (Future Addition)**:
- Vibrations can be measured using piezo sensors and analyzed via:
  - Oscilloscope
  - Audio recording software
  - Dedicated data-logging tools

---

## ✅ To-Do List

- [x] **Demo_A**: Manual control of RPM and step mode.
- [x] **Demo_B**: Iterates through step modes automatically after a full revolution.
- [x] **Demo_C**: Incrementally adjusts RPM after a user-defined cycle time while maintaining manual step mode selection.
- [ ] **Demo_D**: Adds incremental step delay functionality for finer control over motor speed.
- [ ] **Demo_E**: Implements smoother motor transitions by switching step modes during RPM changes.
- [ ] **Add vibration measurement setup instructions** (`hardware_setup.md`).
- [ ] **Introduce stepper motor libraries for Arduino** for enhanced motor control functionality.
- [ ] **Provide example data files** and visuals for results.
- [ ] **Document piezo sensor integration** for vibration analysis (oscilloscope and audio recording setup).
- [ ] **Add real-time motor control** via serial inputs.
- [ ] **Test and validate all demos** with different hardware configurations.

---

## 📌 Notes

- Currently, no external libraries are required.  
- Future files will introduce **dedicated stepper motor libraries** for improved functionality.  

---

## 🧩 Contributing

We welcome contributions from the community! To contribute:
1. Fork the repository.
2. Create a new branch for your feature or bug fix.
3. Submit a pull request with a detailed description of changes.

---

## 🔗 Additional Resources

- [Arduino Documentation](https://www.arduino.cc/)
- [Stepper Motor Control Basics](https://example.com/stepper-motor-basics)
- [How to Set Up a Piezo Sensor with Arduino](https://example.com/piezo-setup)

---

## 👥 Contributors

- **Your Name** – Lead Developer  
- Open-source community contributions are welcome!  

---

## 📝 License

This project is licensed under the MIT License. Feel free to use and build upon it.

---

🎉 **Happy Experimenting!** 🎉
