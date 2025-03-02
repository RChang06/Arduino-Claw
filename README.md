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
- Upload the code thorugh the arduino IDE onto the arduino board https://www.google.com/search?q=how+to+upload+code+to+arduino&rlz=1C1CHBF_enCA1126CA1126&oq=how+to+upload+co&gs_lcrp=EgZjaHJvbWUqDQgAEAAYkQIYgAQYigUyDQgAEAAYkQIYgAQYigUyBwgBEAAYgAQyBggCEEUYOTIHCAMQABiABDIHCAQQABiABDIHCAUQABiABDIHCAYQABiABDIHCAcQABiABDIHCAgQABiABDIHCAkQABiABNIBCDIxOTlqMGo3qAIAsAIA&sourceid=chrome&ie=UTF-8#fpstate=ive&vld=cid:c0b71538,vid:oBZw45NWW-I,st:0
- 


