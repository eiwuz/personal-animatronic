# Proximity-Sensing Animatronic

## Description
An interactive animatronic that responds to nearby objects by moving at varying speeds and "greeting" them with Morse code audio feedback. Built with Arduino to demonstrate sensor integration, motor control, and real-time decision-making in embedded systems.

## How It Works
The system continuously measures distance to nearby objects using an ultrasonic sensor. Based on that distance, the motor speed changes:
- **Far away (>50cm):** Motor spins forward at full speed (200/255)
- **Medium distance (30-50cm):** Motor spins forward slowly (120/255)
- **Close (<30cm):** Motor stops and plays "HI" in Morse code through a speaker

Distance data is also logged to serial monitor for debugging and monitoring.

## Hardware
- **Microcontroller:** Arduino (Uno or similar)
- **Motor:** TT DC motor with PWM speed control
- **Motor Driver:** L298N or similar (IN1, IN2 for direction; ENA for speed)
- **Sensor:** HC-SR04 ultrasonic distance sensor
- **Audio:** Small speaker (8Ω recommended)
- **Housing:** 3D-printed enclosure to hold motor and sensor assembly

## Software
- **Language:** C++ (Arduino IDE)
- **Key Libraries:** Arduino built-in (tone, digitalWrite, analogWrite, pulseIn)
- **Core Features:**
  - `motorForward()` / `motorReverse()` / `motorStop()` — motor direction and speed control via PWM
  - `microsecondsToInches()` / `microsecondsToCentimeters()` — ultrasonic distance calculation
  - `playHi()` — Morse code audio generation (H = ...., I = ..)
  - Distance-based motor logic with thresholds

## Pinout
| Component | Pin | Type |
|-----------|-----|------|
| Motor Enable (PWM) | 5 | Output |
| Motor IN1 (Forward) | 6 | Output |
| Motor IN2 (Reverse) | 10 | Output |
| Ultrasonic Trigger | 7 | Output |
| Ultrasonic Echo | 8 | Input |
| Speaker | 9 | Output |

## Demo
https://youtube.com/shorts/JLoOLTgrmnQ

Note: The video shows the proximity-based motor control. The Morse code audio feature (plays "HI" when object is very close) is functional in the code but not clearly audible in the demo video due to speaker limitations.

## What I Learned
- Ultrasonic sensor calibration and time-based distance calculation
- PWM motor control and direction switching using L298N driver
- Sensor-based decision logic (if-else distance thresholds)
- Audio generation using tone() function for Morse code
- Serial debugging for real-time sensor monitoring
- Timing precision for Morse code playback (dots, dashes, pauses)
- Integration of multiple I/O systems on a single microcontroller
