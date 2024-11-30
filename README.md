# Robotic Mechanical Arm 

## Description

This robotic arm, built entirely from 3D-printed components and electronics, 
has a claw mechanism and precise movement allowing to pick up and sort objects based on their color autonomously with the combination of sensors.

Full 3D Model of Project: https://a360.co/4f849vz

### Key Features:
- 4 Degree of Freedom Motion (DOF): Base, Shoulder, Forearm, and Wrist
- Each joint supports 180 degree motion, while the base is capable of 360 degree motion.
- Gripper claw (end effector) to pick up and place objects into bins based on color.
- Distance and color sensors for autonomous motion and object detection.
- Fully 3D-printed custom parts.

                                        1st Prototype of Robotic Arm
![IMG_0994](https://github.com/user-attachments/assets/404b799d-c3dc-40da-95ea-17052f256961)

## Hardware Overview
The mechanical arm is made up of the following components:
- **Controller**: Arduino Mega 2560 (May switch to Teensy 4.0)
- **Motor Driver**: A4998 Motor Driver
- **Motors**: NEMA17 Stepper Motor
- **Servo Driver**: PCA9685 Servo Driver
- **Servo**: MGR996 Servo
- **Color Sensor**: TCS3200 Color Sensor
- **Distance Sensor**: HC-SCR04 Ultrasonic Sensor
- **Power Supply**: NiMH 12V for Motor and 9V Rechargable Battery

                                            Components Picture
![IMG_1288](https://github.com/user-attachments/assets/daf180d0-0452-40f9-9cf1-1691b80e3157)

## Software Overview
The software of coding the robotic arm is in VS Code with PlatformIO System in C++.
- **Stepper Motor Control**: <Stepper.h> Arudino Library
- **Servo Control**: <Adafruit_PWMServoDriver.h> Library
- **Sensors Implementation**: <HCSR04.h> and <tcs3200.h> Library

The robotic arm has an IK (Inverse Kinematic) Algorithm for precise movement and positioning of end effector.
The robot performs tasks autonomously based on the color and distance sensor.

                                      General Software Mechanism of Robot
<img width="408" alt="Screenshot 2024-11-29 at 10 41 42 PM" src="https://github.com/user-attachments/assets/405f7bf5-468f-4596-bc33-5a4c1b4e05a8">



