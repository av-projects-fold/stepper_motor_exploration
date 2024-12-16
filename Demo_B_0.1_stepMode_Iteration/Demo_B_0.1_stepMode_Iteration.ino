//Alexander Visscher Created 27/11/2024 14:32
//Project: Stepper motor demonstration on Step modes and Speed
//For: Contribution towards Practable.io
//------------------------------------------------------------
//whats different to previous verson: implementing easy Step mode selection


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

#define FULL_STEP 0
#define HALF_STEP 1
#define QUARTER_STEP 2
#define EIGHTH_STEP 3
#define SIXTEENTH_STEP 4

// define the stepPerRevolution variable
int stepsPerRevolution;

// Array to store MS1, MS2, MS3 values for each step mode
int stepModes[5][3] = {
  { LOW, LOW, LOW },    // Full Step:    MS1=0, MS2=0, MS3=0
  { HIGH, LOW, LOW },   // Half Step:    MS1=1, MS2=0, MS3=0
  { LOW, HIGH, LOW },   // Quarter Step: MS1=0, MS2=1, MS3=0
  { HIGH, HIGH, LOW },  // 1/8 Step:     MS1=1, MS2=1, MS3=0
  { HIGH, HIGH, HIGH }  // 1/16 Step:    MS1=1, MS2=1, MS3=1
};

// Select Starting Parameters
int stepMode = SIXTEENTH_STEP;
float RPM = 60;
bool constant_stepDelay_n_steps = false; //sets the stepDelay and number of steps to do, constant


void setup() {

  Serial.begin(9600);

  // Declare pins as output:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MS3, OUTPUT);

  setStepMode(FULL_STEP);
}

void loop() {
  // Set the spinning direction clockwise:
  digitalWrite(dirPin, HIGH);

  float stepDelay = 60000000 / (RPM * stepsPerRevolution);  //step delay in millisecond for micro go 6000000 // ...
  float stepDelay = stepDelay / 2.0;

  Serial.println("Step Mode: " + String(stepMode) + " | RPM: " + String(RPM) + " | Steps per Revolution: " + String(stepsPerRevolution) + " | stepDelay: " + String(stepDelay));

  // sets the number of pulses per second constant as Step mode changes.
  // additionally caps the "steps per revolution" at 400 steps
  if (constant_stepDelay_n_steps == true) {
    stepDelay = 5000;          //stepDelay in millisecond for FULL_STEP, 200 stepsPerRevolution at 60 rpm
    pulseDelay = stepDelay/2;
    stepsPerRevolution = 400;  //2x default FULL_STEP rotations (2 rotations)
  }

  // Spin the stepper motor:
  for (int i = 0; i < stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(pulseDelay);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(pulseDelay);
  }


  delay(1000);

  //iterate through step modes and wrap around
  stepMode = (stepMode + 1) % 5;

  //sets the MS1, MS2, MS3 pins appropriately
  //and adjust the stepsPerRevolution if needed
  setStepMode(stepMode);
}

void setStepMode(int mode) {
  // Set the MS1, MS2, MS3 pins based on the mode
  digitalWrite(MS1, stepModes[mode][0]);
  digitalWrite(MS2, stepModes[mode][1]);
  digitalWrite(MS3, stepModes[mode][2]);

  // Set stepsPerRevolution based on the step mode
  switch (mode) {
    case FULL_STEP:
      stepsPerRevolution = 200;  // Full step (1.8 degrees per step)
      break;
    case HALF_STEP:
      stepsPerRevolution = 400;  // Half step (0.9 degrees per step)
      break;
    case QUARTER_STEP:
      stepsPerRevolution = 800;  // Quarter step (0.45 degrees per step)
      break;
    case EIGHTH_STEP:
      stepsPerRevolution = 1600;  // 1/8 step (0.225 degrees per step)
      break;
    case SIXTEENTH_STEP:
      stepsPerRevolution = 3200;  // 1/16 step (0.1125 degrees per step)
      break;
    default:
      stepsPerRevolution = 200;  // Default to full step
  }
}