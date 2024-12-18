Here's a possible draft for your **GitHub MD documentation** based on the details you've provided:

---

# Stepper Motor Control with A4988 and Arduino

This project demonstrates how to control a Nema 17 stepper motor using an **A4988 stepper driver** and an **Arduino Pro Micro**. It includes hardware, software implementation, and  steps on setting up the physical prototype.

---


## 1. Resources and Implementation

### Hardware

- **Nema 17 Stepper Motor**:  
  Model: 42x38mm (17HS4401)  
  - **Current Limit**: 1.5A  
  - **Voltage**: 3.8V  
  - **Steps**: 1.8° per step (200 steps/rev for full steps)  
  *(Supplier details pending full datasheet)*  

- **A4988 Stepper Motor Driver**:  
  - **Input Voltage**: 3.3V/5V logic  
  - **Output Capacity**: 35V, 2A max  
  - [A4988 Datasheet](https://www.pololu.com/file/0J450/a4988-datasheet.pdf)  

- **Arduino Pro Micro**:  
  - Microcontroller for controlling stepper motor driver.  
  - [Pro Micro Datasheet](https://cdn.sparkfun.com/assets/f/d/8/0/d/ProMicro16MHzv2.pdf)  

### Software

For demonstration purposes, the software uses hand-coded logic to manage motor steps, delay calculations, and microstepping. Libraries can be explored for future improvements (e.g., acceleration, smoother pulse control).

#### Microstepping Mode Configuration:
```cpp
/*
Microstepping Mode Configuration (MS1, MS2, MS3 pins):

- Full Step:    MS1 = Low (0), MS2 = Low (0), MS3 = Low (0)
- Half Step:    MS1 = High (1), MS2 = Low (0), MS3 = Low (0)
- Quarter Step: MS1 = Low (0), MS2 = High (1), MS3 = Low (0)
- 1/8 Step:     MS1 = High (1), MS2 = High (1), MS3 = Low (0)
- 1/16 Step:    MS1 = High (1), MS2 = High (1), MS3 = High (1)
*/
```

#### Microstepping Parameters:
```cpp
/*
Stepper Motor Resolution Calculations:

- Full Step: 200 steps per revolution (1.8° per step)
- Half Stepping: 400 steps per revolution (0.9° per step)
- Quarter Stepping: 800 steps per revolution (0.45° per step)
- 1/8 Stepping: 1600 steps per revolution (0.225° per step)
- 1/16 Stepping: 3200 steps per revolution (0.1125° per step)
*/
```

#### Motor Speed Calculation:
![stepDelay and pulseDelay Terminology](img/step%20and%20pulse%20graph.png)
```cpp
float stepDelay = 60.0 / (RPM * stepsPerRevolution);  // in seconds
float pulseDelay = (stepDelay / 2) * 1000 * 1000;    //step delay in microseconds.
```
Where:  
- **RPM** = Desired motor speed in revolutions per minute  
- **StepsPerRevolution** = 200 for full steps (adjust for microstepping)  

---

### Reference Links
- [A4988 Stepper Motor Driver with Arduino Tutorial](https://www.makerguides.com/a4988-stepper-motor-driver-arduino-tutorial/)  
- [Pololu A4988 Resources](https://www.pololu.com/product/1182)  
- [Stepper Motor Current Limit Guide](https://www.makerguides.com/a4988-stepper-motor-driver-arduino-tutorial/)  

---

## 2. Setup

### Step 1: Wiring the Hardware

![A4988 Driver](img/A4988%20Driver.png)
![Arduino Pro Micro Pinout](img/Arduino%20Pro%20Micro%20Pinout.png)

Follow the wiring setup below:
![Basic Hardware Circuit](img/Basic%20Hardware%20Circuit.png)

One may come across some confusion with ensuring the right stepper motor coil pairs are connected to the driver. Follow this tutorial to ensure the correct configuration. [Link](https://youtu.be/Bm9b0XT5-rw)


### Step 2: Setting the Current Limit
To set the current limit on A4988:  
1. Power the A4988 via VDD (5V).  
2. Measure **Vref** at the current limit potentiometer.  
3. Use the formula:  
 ```math
   V_{\text{ref}} = \frac{\text{Current Limit}}{8 \times R_{\text{sc}}}
 ```
    Example: For 1A limit with Rsc = 0.068 Ω,

 ```math
    V_{\text{ref}} = 1 \times (8 \times 0.068) = 0.544 \, \text{V}
 ```

Reference table:

| Current (A) | Formula                       | Vref (V)   |
|-------------|--------------------------------|-----------|
| 0.1A        | 0.1*(8*0.068)                 | 0.0544    |
| 0.3A        | 0.3*(8*0.068)                 | 0.1632    |
| 0.5A        | 0.5*(8*0.068)                 | 0.2720    |
| 0.7A        | 0.7*(8*0.068)                 | 0.3808    |
| 0.9A        | 0.9*(8*0.068)                 | 0.4896    |
| 1.0A        | 1.0*(8*0.068)                 | 0.5440    |
| 1.2A        | 1.2*(8*0.068)                 | 0.6528    |
| 1.4A        | 1.4*(8*0.068)                 | 0.7616    |
| 1.5A        | 1.5*(8*0.068)                 | 0.8160    |


### Step 3: Upload Code to Arduino
Upload the following example code to test basic stepper motor movement:

```cpp
const int stepPin = 5;   // STEP pin
const int dirPin = 6;    // DIR pin
const int stepsPerRev = 200;  // Full steps per revolution

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  digitalWrite(dirPin, HIGH);  // Set rotation direction
}

void loop() {
  for (int i = 0; i < stepsPerRev; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);  // Step delay (adjust speed)
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
  }
  delay(1000);  // Wait before reversing direction
  digitalWrite(dirPin, !digitalRead(dirPin));  // Reverse direction
}
```

### Step 4: Adjust Step Delay for Desired RPM
To achieve a specific RPM, adjust `delayMicroseconds()` using the formula:  
```math
\text{stepDelay (µs)} = \frac{6,000,000}{\text{RPM} \times \text{StepsPerRev}} 
```
```math
\text{pulseDelay (µs)} = \frac{stepDelay}{2}
```

---

## 3. Physical Prototype Board

The prototype setup consists of:  
1. **Breadboard** for connections.  
2. **Arduino Pro Micro** as the controller.  
3. **A4988 Driver** for stepper motor control.  
4. **Nema 17 Stepper Motor** powered via a 12V supply.

### Example Prototype Image:
![Prototype Setup](img/Prototype%20board.png)

---

## Future Improvements
- Explore libraries for acceleration and smoother movement (e.g., `AccelStepper` library).  
- Investigate thermal performance under continuous operation.  

---

## Notes
- Ensure proper current limit settings to avoid damaging the motor or driver.  
- Use heatsinks for A4988 to prevent overheating.  

---
