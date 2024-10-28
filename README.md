
# Gripper Control System with MQTT and GUI

This project provides an MQTT-controlled mechanical gripper system using an ESP32 microcontroller and a Python GUI. The ESP32 reads position data from analog sensors on the gripper jaws and communicates with an MQTT broker, while a Python GUI enables control of the gripper’s opening and closing functions. 

## Table of Contents
1. [Project Overview](#project-overview)
2. [Hardware Requirements](#hardware-requirements)
3. [Software Requirements](#software-requirements)
4. [Installation and Setup](#installation-and-setup)
5. [Usage](#usage)
6. [File Structure](#file-structure)
7. [Contributing](#contributing)
8. [License](#license)

## Project Overview

The **Gripper Control System** includes:
- **ESP32 Microcontroller**: Controls the gripper motor and reads analog sensors for position feedback.
- **Python GUI**: Provides buttons to open and close the gripper, displays real-time gripper position, and indicates the MQTT connection status using a visual "LED" indicator.

The ESP32 is programmed to subscribe to MQTT control messages (`gripper/control` topic) and publish position data on `gripper/position` topic.

## Hardware Requirements

1. ESP32 microcontroller
2. Stepper motor and driver (to control the gripper)
3. Analog sensors for position feedback (mounted on the left and right gripper jaws)
4. A computer with Python and MQTT broker software (like Mosquitto) installed

## Software Requirements

1. **Arduino IDE** with ESP32 board support
2. **Python 3.7+**
3. Python libraries:
   - `paho-mqtt`
   - `tkinter` (usually included with Python)

## Installation and Setup

### 1. Setting Up the ESP32

- Install the [Arduino IDE](https://www.arduino.cc/en/software) if you haven't already.
- Install the ESP32 board in Arduino by going to `File > Preferences`, adding this URL to "Additional Boards Manager URLs":
  ```
  https://dl.espressif.com/dl/package_esp32_index.json
  ```
  Then, go to `Tools > Board > Board Manager`, search for "ESP32", and install it.
- Open the Arduino sketch `gripper_control.ino` from this repository.
- Update the WiFi credentials (`YOUR_SSID` and `YOUR_PASSWORD`) and the `YOUR_MQTT_BROKER_IP` with your MQTT broker's IP address.
- Connect the ESP32 to your computer, select the correct port, and upload the sketch.

### 2. Setting Up the MQTT Broker (e.g., Mosquitto)

If you don’t have an MQTT broker installed locally:
- Install Mosquitto (or another MQTT broker).
- Start the MQTT broker on `localhost`, or make note of its IP if running on a different machine.

### 3. Setting Up the Python GUI

- Ensure Python 3.7+ is installed.
- Install `paho-mqtt` if it’s not already installed:
  ```bash
  pip3 install paho-mqtt
  ```
- Open the Python file `gripper_control_gui.py` and update `broker` with your MQTT broker's IP if it’s not running locally.
- Run the script using:
  ```bash
  python3 gripper_control_gui.py
  ```

## Usage

1. **Run the ESP32 sketch** on your ESP32 microcontroller to start the gripper control.
2. **Start your MQTT broker** (e.g., Mosquitto).
3. **Run the Python GUI script** to open the control window.
   - Use the **Open Gripper** and **Close Gripper** buttons to control the gripper.
   - The **Current Gripper Position** will display real-time position data based on sensor input.
   - Connection status and broker IP are displayed, with a visual indicator showing green when connected and red if disconnected.

## File Structure

- **`gripper_control.ino`**: The Arduino sketch for the ESP32 microcontroller to control the gripper motor and read sensor data.
- **`gripper_control_gui.py`**: The Python GUI script that allows you to control the gripper and monitor its position via MQTT.

### `gripper_control.ino` (Arduino ESP32 File)
This file:
  - Connects the ESP32 to WiFi and an MQTT broker.
  - Subscribes to `gripper/control` for gripper commands (`0` to open, `1` to close).
  - Publishes gripper position to `gripper/position` based on analog sensor readings.

### `gripper_control_gui.py` (Python GUI File)
This file:
  - Connects to the MQTT broker and provides a GUI interface to control the gripper.
  - Displays the current position of the gripper as reported by the ESP32.
  - Shows connection status with an IP display and a green/red visual indicator.

## Contributing

Contributions are welcome! Please open an issue or submit a pull request for any enhancements or bug fixes.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
