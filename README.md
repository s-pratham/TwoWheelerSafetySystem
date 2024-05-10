# Two-Wheeler Safety System


The Two-Wheeler Safety System is an Arduino-based project designed to enhance rider safety through real-time object detection and alerting. This system utilizes ultrasonic sensors, an Arduino microcontroller, and an LCD display to provide riders with crucial information about surrounding obstacles.

## Features

- **Real-Time Object Detection**: Ultrasonic sensors detect objects in the rider's vicinity.
- **Proactive Alerting Mechanism**: Alerts riders of potential hazards based on object proximity.
- **Dynamic and Adaptive**: Easily scale the system by adding more ultrasonic sensors with simple pin configurations.
- **Interactive LCD Display**: Provides clear and intuitive feedback to the rider about detected objects.
- **Enhanced Safety Standards**: Contributes to advancing safety measures for two-wheeler vehicles.

## Components Used

- Arduino board (e.g., Arduino Uno)
- Ultrasonic sensors for object detection (e.g., HC-SR04)
- Buzzer for audible alerts
- LED indicators for visual feedback
- LCD display for real-time status information (via I2C module)
- Breadboard and jumper wires
- Power supply unit

## Getting Started

1. **Setup**: Connect ultrasonic sensors, buzzer, LCD display, and LEDs to the Arduino board as per the provided pin configurations.
2. **Upload**: Upload the Arduino sketch (`TwoWheelerSafetySystem.ino`) to the Arduino board using the Arduino IDE.
3. **Run**: Power on the system and observe real-time object detection and alerting on the interactive LCD display.
