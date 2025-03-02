Arduino Claw Control with Ultrasonic Sensor

This mini-project is an Arduino-based system that control servo-operated claw using Arduino Claw Control with Ultrasonic Sensor. The design of this claw was designed for carrying objects the size of a can or smaller. However, the code written is interchangable with other Claw control systems as long as the sensor is kept perpindecular to the ground floor at all times. 

Features
- Ultrasonic Distance: Utilizes an HC_SRO4 Ultrasonic Sensor to measure the distance of objects
- Customizable Triggers: Adjustablle triggers for height and timing delays for release actions
- Servo-Controlled Claw: The expansion and contraction relies on relies on the torque provided by the servo motor

Hardware/material Requirement:
- Arduino kit (Needs to include, servo motor, HC-SR04 Ultrasonic Sensor, jumper wires
- Power supply (prefferably a mini battery to install on the claw)
- Any suitable material can work for the framework of claw (aluminium sheets is recommeded
- 

How it works

1. The ultrasonic sensor continuously measures the distance of the object in front of it
2. If the object is detected within trigger parameters set on the sensor, the claw closes
3. The claw will naturally release when it reaches another trigger height

The system uses a state machine to manage its behaviour split into four states (open, closing, close, opening)

How to run: 
- Upload the code thorugh the arduino IDE using a .ion file onto the arduino board. [(Quick Tutorial)](https://www.youtube.com/watch?v=oBZw45NWW-I)
- Connect the Hardware: Wire teh companents as descirbed in the Pin Connections series (this can be adjusted in the code)
- 


