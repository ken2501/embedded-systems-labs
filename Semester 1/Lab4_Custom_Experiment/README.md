# Microcontroller-Based Threat Monitoring and Alert System

## Overview
Embedded monitoring and alert system developed using Arduino Nano.

The system simulates a configurable threat detection environment where analogue sensor input controls threat levels while visual and audio indicators provide system feedback.

The project demonstrates:
- embedded input processing
- state-based control logic
- RGB LED control
- actuator triggering
- emergency override systems
- real-time monitoring behaviour

---

# Features

- Potentiometer-based threat simulation
- RGB LED threat visualization
- Four-level discrete alert indicators
- Pushbutton response level control
- Emergency stop override
- Buzzer activation during high-threat states
- Real-time system monitoring

---

# Hardware Used

- Arduino Nano
- Breadboard
- RGB LED
- Standard LEDs
- Potentiometer
- Pushbuttons
- Passive buzzer
- Resistors
- Jumper wires

---

# System Logic

The potentiometer simulates changing sensor values.

Threat levels are classified into multiple states:
- Safe
- Low threat
- Medium threat
- High threat

The RGB LED visualizes current system status while discrete LEDs represent response escalation levels.

A dedicated emergency stop button immediately resets the system into a safe state and disables active alerts.

---

# Software Concepts Demonstrated

- Embedded state machines
- Real-time input handling
- PWM RGB control
- Non-blocking timing
- Conditional logic
- Multi-device coordination
- Safety override systems

---

# Results

The system successfully demonstrated:
- stable real-time operation
- responsive threat-level transitions
- reliable emergency override behaviour
- synchronized visual and audio alerts

---

# Files

- `threat_monitor.ino`
- `setup.png`

---

# Future Improvements

Possible future extensions:
- real sensor integration
- wireless telemetry
- SD card logging
- autonomous response logic
- LCD/OLED interface
- remote monitoring dashboard