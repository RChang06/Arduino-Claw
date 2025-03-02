#include <Servo.h>
#include <NewPing.h>


/* PIN ASSIGNMENT */
#define SERVO_PIN 2
#define GROUND_PIN 10
#define ECHO_PIN 11
#define TRIGGER_PIN 12
#define VCC_PIN 13


/* CONSTANTS */
#define SECOND 1000.0 //ms

//Sonar
#define SONAR_MAX_DISTANCE 200 //cm
#define SONAR_MODE 1 //0 for NewPing, 1 for Simple

//Servo
#define SERVO_MIN_ANGLE 180 //deg
#define SERVO_MAX_ANGLE 0 //deg
#define SERVO_SPEED 180.0/SECOND //deg/s

//Breakpoints
#define TALL_OBJECT_TRIGGER_HEIGHT 0 //cm   //DISABLED
#define SMALL_OBJECT_TRIGGER_HEIGHT 20 //cm
#define RELEASE_TRIGGER_HEIGHT 200 //cm

//Timing
#define UPDATE_DELAY 100 //ms
#define TALL_TRIGGER_DELAY 8 * SECOND //s
#define SMALL_TRIGGER_DELAY 2 * SECOND //s
#define RELEASE_TRIGGER_DELAY 5 * SECOND //s


/* PERSISTANT VARS */
//Timers
int update_timer = 0;
int claw_timer = 0;

//State vars
int claw_state = 1; //1 for open, 2 for closing, 3 for closed, 4 for opening
int in_small_object_range = 0; // 0/1 - F/T
int in_tall_object_range = 0; // 0/1 - F/T
int in_release_range = 0; // 0/1 - F/T


/* PROTOTYPES */
int getDistanceCM(int mode);
void stepServoToAngle(int angle);

/* COMPONENT INIT */
NewPing sonar(TRIGGER_PIN, ECHO_PIN, SONAR_MAX_DISTANCE);
Servo servo;


void setup() {
  /* PIN SETUP */
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(GROUND_PIN, OUTPUT); // tell pin 10 it is going to be an output
  pinMode(VCC_PIN, OUTPUT); // tell pin 13 it is going to be an output

  digitalWrite(GROUND_PIN,LOW); // tell pin 10 to output LOW (OV, or ground)
  digitalWrite(VCC_PIN, HIGH); // tell pin 13 to output HIGH (+5V)

  /* SERVO SETUP */
  servo.attach(SERVO_PIN);

  servo.write(SERVO_MIN_ANGLE);

  /* SERIAL SETUP*/
  Serial.begin(9600); // set data transmission rate to communicate withcomputer
  Serial.println("Serial Started");
}

void loop() {
  /* TEMP VARS */
  int current_time = millis();

  /* MAIN LOOP*/

  // Skip if it is not time to update
  if (current_time - update_timer < UPDATE_DELAY){
    return 0;
  }

  // Get current time
  update_timer = current_time;

  // Get sonar data
  int distance = getDistanceCM(SONAR_MODE); 

  // Print sonar ping data
  Serial.print("Ping: ");
  Serial.println(distance);

  Serial.print("State: ");
  Serial.println(claw_state);
  // Go to behavior for each claw state
  switch(claw_state){

    case 1: // Open
      Serial.println(servo.read());
      // Check if we are within the small object trigger range
      if (distance <= SMALL_OBJECT_TRIGGER_HEIGHT){
        Serial.println("In range");

        // Check if we had just entered the small object range
        if (in_small_object_range == 0){
          
          // Start the claw timer to time against the SMALL_TRIGGER_DELAY
          claw_timer = current_time;

          // Set range states to proper values 
          // (Reset tall object range so that it can retrigeer on exiting small object range)
          in_small_object_range = 1;
          in_tall_object_range = 0;

          Serial.println("Entered small object range");
        }

        // Check if we have passed the SMALL_TRIGGER_DELAY
        else if (current_time - claw_timer >= SMALL_TRIGGER_DELAY){

          // Progress to closing the claw
          claw_state = 2;
          Serial.println("Progressing to 'closing'(2)\n");

          // Reset range states
          in_small_object_range = 0;
        }

      }

      // Else check if we are within the large object trigger range
      else if (distance <= TALL_OBJECT_TRIGGER_HEIGHT){ // DISABLED through global var TALL_OBJECT_TRIGGER_HEIGHT
        
        // Check if we had just entered the large object range
        if (in_tall_object_range == 0){

          // Start the claw timer to time against the TALL_TRIGGER_DELAY
          claw_timer = current_time;

          // Set range states to proper values
          in_tall_object_range = 1;

          Serial.println("Entered tall object range");
        }

        // Check if we have passed the TALL_TRIGGER_DELAY
        else if (current_time - claw_timer >= TALL_TRIGGER_DELAY){
          
          // Progress to closing the claw
          claw_state = 2;
          Serial.println("Progressing to 'closing'(2)\n");

          // Reset range states
          in_tall_object_range = 0;
        }
      }

      // Reset range states if outside ranges
      else{
        in_small_object_range = 0;
        in_tall_object_range = 0;
      }
      break;

    case 2: // Closing

      // Begin closing the claw
      stepServoToAngle(SERVO_MAX_ANGLE);

      // Progress to closed if we have reached the max angle
      if (servo.read() <= SERVO_MAX_ANGLE){
        claw_state = 3;
        Serial.println("Progressing to 'closed'(3)\n");
      }
      break;

    case 3: // Closed
      Serial.println(servo.read());
      // Check if we are within the release trigger range
      if (distance <= RELEASE_TRIGGER_HEIGHT){

        Serial.println("In range");
        // Check if we had just entered the release trigger range
        if (in_release_range == 0){

          // Start the claw timer to time against the RELEASE_TRIGGER_DELAY
          claw_timer = current_time;

          // Set range states to proper values
          in_release_range = 1;

          Serial.println("Entered release object range");
        }
        // Check if we have passed the RELEASE_TRIGGER_DELAY
        else if (current_time - claw_timer >= RELEASE_TRIGGER_DELAY){

          // Progress to opening the claw
          claw_state = 4;
          Serial.println("Progressing to 'opening'(4)\n");
          
          // Reset range states
          in_release_range = 0;
        }
      }

      // Reset range state if outside range
      else{
        in_release_range = 0;
      }
      break;

    case 4: // Opening

      // Begin opening the claw
      stepServoToAngle(SERVO_MIN_ANGLE);

      Serial.println(servo.read());
      // Progress to open if we have reached the max angle
      if (servo.read() >= SERVO_MIN_ANGLE){
        claw_state = 1;
        Serial.println("Progressing to 'open'(1)");
      }
      break;

    default: // If we hit this case, something went wrong

      Serial.println("Error: Claw State Not Implemented");
  }
}

int getDistanceCM(int mode){

  // Go to behavior for each ping type
  switch (mode){

    case 0: // NewPing

      // Return distance
      return sonar.ping_cm();


    case 1: // Simple

      // Trigger a sonar ping
      digitalWrite(TRIGGER_PIN, LOW);
      delayMicroseconds(2);
      digitalWrite(TRIGGER_PIN, HIGH);
      delayMicroseconds(20);
      digitalWrite(TRIGGER_PIN, LOW);

      // Get the pulse duration of sonar
      long duration = pulseIn(ECHO_PIN, HIGH);

      // Calculate the distance from ground
      int distance = duration * 0.034 / 2;       

      // Return distance clamped to under the SONAR_MAX_DISTANCE
      if (distance > SONAR_MAX_DISTANCE){
        return SONAR_MAX_DISTANCE;
      }
      else if (distance == 0){
        return 99;
      }
      else{
        return distance;
      }

    default: // If we hit this case, something went wrong
      Serial.println("Sonar Mode Not Set");
  }
}

void stepServoToAngle(int target_angle){
  int next_step;

  // Get current servo angle
  int current_angle = servo.read();
  
  // Calculate next step towards the target_angle based off of SERVO_SPEED
  if (current_angle < target_angle){
    next_step = current_angle + SERVO_SPEED * UPDATE_DELAY;
  }
  else if (current_angle > target_angle){
    next_step = current_angle - SERVO_SPEED * UPDATE_DELAY;
  }

  // Write next step to servo
  servo.write(next_step);
}
