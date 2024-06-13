# Lightbulb Control Project

This project allows you to control a lightbulb using an ESP32 microcontroller and a Firebase Realtime Database. The web application provides a user interface to control the lightbulb and switch between manual and toggle modes.

## Directory Structure

- `esp32/`: Contains the ESP32 sketch.
- `public/`: Contains the web application files (HTML, CSS, JS).
- `firebase/`: Contains Firebase configuration and rules.
- `.firebase/`: Firebase deployment directory.
- `.firebaserc`: Firebase configuration file.
- `.gitignore`: Git ignore file.
- `firebase.json`: Firebase configuration file.
- `README.md`: Project overview and setup instructions.

## Prerequisites

- ESP32 microcontroller
- Sound sensor module
- Relay module
- Firebase account
- Arduino IDE or PlatformIO

## Libraries Required for Arduino Sketch

Ensure you have the following libraries installed in your Arduino IDE:
- `WiFi.h`
- `FirebaseESP32.h`

You can install the `FirebaseESP32` library via the Arduino Library Manager.

## Setup Instructions

### 1. Clone the Repository

```sh
git clone <your-github-repo-url>
cd lightbulb-project
