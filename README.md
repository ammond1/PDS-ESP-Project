# Electronics and IoT Assignment Documentation

## Name: Ammond Wong 

**Link to Demo Video:** [Watch here](https://youtu.be/Jrg3KLvsXh4)

---

## Introduction

This project demonstrates how to build and code a sound-detecting device that sends a message whenever the sound levels are too high. Some use cases include notifying people to lower their voices in classrooms or libraries.

## How It Works (Brief Explanation)

- The sound sensor records the base noise level upon power-up.
- Each subsequent sound reading is compared to this base noise level and sent to a Firebase Realtime Database.
- A Telegram bot reads from this database and sends a message (`"NOISY SIA"`) whenever the noise level exceeds a set threshold (200 in this project).

## Code Overview

This project consists of two main code files:

1. **Arduino `.ino` File (ESP32 + Sensor Control):**
   - Initializes with a base noise level.
   - Averages out readings to smooth out fluctuations.
   - Pushes noise data to Firebase.
   
2. **Python `bot.py` File (Telegram Bot):**
   - Listens for the `/start` command to monitor noise levels from Firebase.
   - Sends a message (`"NOISY SIA"`) when the threshold is exceeded.
   - Stops monitoring with the `/stop` command.

## Requirements

- **Hardware:**
  - ESP32-C3-DevkitC-02 board
  - KY-037 Sound Sensor
  - Male-to-male jumper wires
  - Breadboard

- **Software:**
  - Arduino IDE
  - Python + IDE (e.g., VS Code)
  - Telegram account
  - Firebase account

## Setup Guide

### Step 1: Hardware Setup

- Connect KY-037 **`+`** to **ESP `5V`**
- Connect KY-037 **`G`** to **ESP `GND`**
- Connect KY-037 **`AO`** to **ESP `Pin 0`** (or any ADC pin)

### Step 2: Firebase Realtime Database Setup

1. Go to [Firebase Console](https://firebase.google.com) and create a new project.
2. Set up a Realtime Database with a **`noise_level`** data path.
3. Set database rules to `read` and `write: true`.
4. Note down your **Firebase URL** and access **Database Secret**.
5. Download Firebase Admin SDK in **Node.js** format.

### Step 3: ESP32 Software Setup

1. Install [Arduino IDE](https://www.arduino.cc/en/software).
2. Clone the project repository:
   ```bash
   git clone https://github.com/ammond1/PDS-ESP-Project.git
   ```
3. Open `esp_project_sound_sensor.ino` in Arduino IDE.
4. Paste your Firebase credentials in `FIREBASE_HOST` and `FIREBASE_AUTH`.
5. Set your WiFi SSID and password.
6. Upload the code to your ESP32.

### Step 4: Telegram Bot Setup

1. Open Telegram and search for **BotFather**.
2. Create a new bot and copy the provided **HTTP API key**.
3. In your project folder, create a `.env` file:
   ```bash
   BOT_TOKEN=your_telegram_bot_api_key
   ```
4. Install required Python libraries:
   ```bash
   python -m venv venv
   source venv/bin/activate  # (On Windows, use `venv\Scripts\activate`)
   pip install python-dotenv os telebot firebase_admin time
   ```
5. Update `bot.py` with your Firebase credentials.

### Step 5: Running the Project

1. Power on the ESP32.
2. Run the Telegram bot:
   ```bash
   python bot.py
   ```
3. Start monitoring by sending `/start` in the Telegram chat.
4. Stop monitoring with `/stop`.
5. Reset ESP32 if the bot triggers excessively.

## Configuration Options

### Adjusting Sound Sensor Sensitivity

- Use a screwdriver to turn the **KY-037 potentiometer**:
  - Clockwise → **Increase sensitivity**
  - Counter-clockwise → **Decrease sensitivity**
- The **LED below the potentiometer** lights up when noise exceeds the threshold.

### Adjusting Noise Threshold in `bot.py`

- Modify **line 42** in `bot.py` to change the threshold level.

---

### 🔗 Repository: [GitHub](https://github.com/ammond1/PDS-ESP-Project.git)

