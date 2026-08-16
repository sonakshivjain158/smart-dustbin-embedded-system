# Smart Dustbin – Industry-Oriented Embedded System
Industry-oriented Embedded Systems project implementing an automatic smart dustbin using Arduino, ultrasonic sensors, servo motor, LEDs and buzzer, with Wokwi virtual simulation.

## 📌 Project Overview
Smart Dustbin is an embedded systems project designed to automate
waste-bin operation using sensors, a microcontroller, and actuators.
The system automatically opens the lid when a person approaches and
continuously monitors the garbage level inside the bin.
The project was first developed and tested virtually using Wokwi.

## 🎯 Objectives
- Automatically detect a person approaching the dustbin
- Open and close the lid automatically
- Monitor garbage fill level
- Display bin status using LEDs
- Generate an alert when the bin is full
- Develop and test the complete embedded system virtually
- Maintain modular firmware and testing stages

## ⚙️ Features
- Automatic lid control
- Ultrasonic proximity detection
- Ultrasonic garbage-level detection
- Fill percentage calculation
- Green/Yellow/Red status indication
- Buzzer alert for full condition
- Modular firmware testing
- Wokwi virtual simulation

## 🧩 Components
| Component | Purpose |
|---|---|
| Arduino Uno | Main microcontroller |
| HC-SR04 × 2 | Proximity and fill-level sensing |
| Servo Motor | Automatic lid control |
| Green LED | Normal status |
| Yellow LED | Near-full status |
| Red LED | Full status |
| Buzzer | Full-bin warning |

## 🔌 Pin Configuration
| Component | Arduino Pin |
|---|---|
| Green LED | D2 |
| Yellow LED | D3 |
| Red LED | D4 |
| Servo | D5 |
| Proximity Echo | D6 |
| Proximity Trigger | D7 |
| Fill Echo | D8 |
| Fill Trigger | D9 |
| Buzzer | D10 |

## 🧠 Working Principle
### 1. Person Detection
The first HC-SR04 measures the distance between the person and
the dustbin.
If the detected distance is below the defined threshold,
the Arduino commands the servo to open the lid.
### 2. Automatic Lid
The servo rotates to the open position when a person is detected.
After the defined time, the servo returns to the closed position.
### 3. Fill-Level Detection
The second HC-SR04 is positioned inside the bin.
The measured distance is converted into an approximate fill
percentage.
### 4. Status Indication
The system uses three LEDs:
- Green → Normal
- Yellow → Near Full
- Red → Full
When the bin reaches the full threshold, the buzzer is activated.

## 🧪 Development & Testing
The system was developed incrementally:
1. Ultrasonic sensor testing
2. Servo motor integration
3. Fill-level detection
4. LED and buzzer integration
5. Complete system integration

## 🖥️ Simulation
The complete system was simulated using Wokwi.
### Wokwi Simulation
Paste your Wokwi project link here.

## 📸 Simulation
 [Wokwi Circuit](images/wokwi-circuit.png)
 [Proximity Detection](images/proximity-test.png)
 [Lid Close](images/lid-close.png)
 [Lid Open](images/lid-open.png)
 [Normal Status](images/led_status_green.png)
 [Near Full Status](images/led_status_yellow.png)
 [Full Status](images/led_status_red.png)

## 📁 Project Structure
https://wokwi.com/projects/472503852428220417
smart-dustbin-embedded-system/
│
├── README.md
│
├── firmware/
│   ├── final/
│   │   └── smart_dustbin_final.ino
│   ├── test_01_ultrasonic/
│   │   └── test_01_ultrasonic.ino
│   ├── test_02_servo/
│   │   └── test_02_servo.ino
│   ├── test_03_fill_level/
│   │   └── test_03_fill_level.ino
│   └── test_04_status_led_buzzer/
│       └── test_04_status_led_buzzer.ino
│
├── simulation/
│   └── wokwi/
│       ├── diagram.json
│       ├── sketch.ino
│       └── wokwi-project.txt
│
└── images/
    ├── wokwi-circuit.png
    ├── proximity-test.png
    ├── lid-close.png
    ├── lid-open.png
    ├── fill_level_1.png
    ├── fill_level_2.png
    ├── fill_level_3.png
    ├── led_status_red.png
    ├── led_status_yellow.png
    ├── led_status_green.png
    ├── final_1.png
    ├── final_2.png
    └── final_3.png
