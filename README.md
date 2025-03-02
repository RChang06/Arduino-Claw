# **Arduino Claw Control with Ultrasonic Sensor**

This mini-project is an Arduino-based system that controls a servo-operated claw using an **Ultrasonic Sensor**. The design of this claw is intended for carrying objects the size of a can or smaller. However, the code written is **interchangeable** with other claw control systems, as long as the sensor is kept **perpendicular** to the ground floor at all times.

---

## **Features**
- **Ultrasonic Distance Sensing**: Utilizes an **HC-SR04 Ultrasonic Sensor** to measure the distance of objects.
- **Customizable Triggers**: Adjustable triggers for height and timing delays for release actions.
- **Servo-Controlled Claw**: The expansion and contraction rely on the torque provided by the servo motor.

---

<div align="center">
  <img src="https://github.com/user-attachments/assets/262a8360-075e-45b3-8513-47833e67e3bc" alt="Image" width="85%">
  <p><em>Isometric Sketch of the Claw</em></p>
</div>

---

## **Hardware/Material Requirements**
- **Arduino Kit** (must include a servo motor, HC-SR04 Ultrasonic Sensor, and jumper wires).
- **Power Supply** (preferably a mini battery to install on the claw).
- **Framework Material**: Any suitable material can work for the framework of the claw (aluminum sheets are recommended).

---

## **How It Works**
1. The ultrasonic sensor continuously measures the distance of the object in front of it.
2. If the object is detected within the **trigger parameters** set on the sensor, the claw closes.
3. The claw will naturally release when it reaches another **trigger height**.

The system uses a **state machine** to manage its behavior, split into four states: **open**, **closing**, **closed**, and **opening**.

---

## **How to Run**
1. **Upload the Code**: Run it through the Arduino IDE using a `.ino` file, and upload it onto the Arduino board. [(Quick Tutorial)](https://www.youtube.com/watch?v=oBZw45NWW-I).
2. **Connect the Hardware**: Wire the components as described in the **Pin Connections** section (this can be adjusted in the code).
3. **Power Source**: Attach the Arduino board to a power device.
4. **Monitor Outputs**: Outputs can be used to troubleshoot less reliable hardware, such as the servo motor.

---

## **License**
This project is licensed under the **MIT License**.
