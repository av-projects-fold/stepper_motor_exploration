//Alexander Visscher Created 27/11/2024 
//Project: Stepper motor demonstration on Step modes and Speed
//For: Contribution towards Practable.io
//------------------------------------------------------------

/*
Stepper Motor Resolution Calculations:

- Full Step: 200 steps per revolution (1.8° per step)
- Half Stepping: 400 steps per revolution (0.9° per step)
- Quarter Stepping: 800 steps per revolution (0.45° per step)
- 1/8 Stepping: 1600 steps per revolution (0.225° per step)
- 1/16 Stepping: 3200 steps per revolution (0.1125° per step)

Microstepping Mode Configuration (MS1, MS2, MS3 pins):

- Full Step:    MS1 = Low (0), MS2 = Low (0), MS3 = Low (0)
- Half Step:    MS1 = High (1), MS2 = Low (0), MS3 = Low (0)
- Quarter Step: MS1 = Low (0), MS2 = High (1), MS3 = Low (0)
- 1/8 Step:     MS1 = High (1), MS2 = High (1), MS3 = Low (0)
- 1/16 Step:    MS1 = High (1), MS2 = High (1), MS3 = High (1)
*/

// Define stepper motor connections and steps per revolution:
#define dirPin 9
#define stepPin 8
#define MS1 5
#define MS2 6
#define MS3 7

// Settings
#define stepsPerRevolution 1600 //How many steps in a revolution. Specified by the stepMode and Stepper Motor resolution.
float RPM = 120; //rotations per minute

void setup() {
  Serial.begin(9600);
  // Declare pins as output:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(MS1,OUTPUT);
  pinMode(MS2,OUTPUT);
  pinMode(MS3,OUTPUT);

  // Set the Step mode
  digitalWrite(MS1, HIGH);
  digitalWrite(MS2, HIGH);
  digitalWrite(MS3, LOW);
  // Set the spinning direction clockwise:
  digitalWrite(dirPin, HIGH);

}

void loop() {
  // The stepper motor moves by having signals sent at specified intervals. 
  // The interval (stepDelay) between each signal determined the stepper motors speed
  float stepDelay = 60.0 / (RPM * stepsPerRevolution);  // in seconds
  float pulseDelay = (stepDelay / 2) * 1000 * 1000;    //step delay in microseconds.
  Serial.println("RPM: " + String(RPM) + "  pulseDelay us: " + String(pulseDelay));

  
  // Spin the stepper motor 1 revolution
  for (int i = 0; i < stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(pulseDelay);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(pulseDelay);
  }

}