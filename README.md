# Ceremet 🏍️🪖
> A modular smart helmet device designed to enhance rider safety and convenience.

Ceremet is a custom hardware and firmware solution built to transform any standard helmet into a smart helmet. Originally created during the **Genesis Hackathon**, this project encompasses a custom-designed PCB, ESP32-based firmware, and a modular architecture.

## 🌟 Features
- **Accident Detection:** Integrated accelerometer for crash and fall detection.
- **Audio Feedback:** I2S Audio Amplification (MAX98357A) for voice alerts and media.
- **Modular Sensors:** IR sensors for helmet wear detection and automated control.
- **Cooling System:** Integrated fan control for rider comfort.
- **Power Management:** Onboard MT3608 boost converter and NDP6020P MOSFETs for efficient power delivery.

## 📂 Repository Structure
This repository is organized into three main domains:

```text
Ceremet/
├── Hardware/                # Electrical Domain (KiCad files, Gerbers, BOM, Schematics)
├── Firmware/                # Software Domain (ESP32 source code for sensors, audio, etc.)
└── Docs/                    # Project Documentation (Datasheets, Hackathon Pitch, etc.)
```

## 🛠️ Hardware Setup
The hardware is designed entirely in **KiCad**. You can view the schematics and layout in the `Hardware/KiCad/` directory.
- To manufacture the board, use the provided Gerber ZIP files located in `Hardware/Gerbers/`.
- The Bill of Materials (BOM) can be found in `Hardware/BOM/`.

## 💻 Firmware
The firmware is written for the ESP32 microcontroller using the Arduino framework. 
Key modules include:
- `accelerometer`: Fall detection and movement tracking.
- `IR_code`: Proximity and wear detection.
- `fan_code`: Temperature/comfort control.

*Note: The firmware is currently undergoing optimization.*

## 📄 License
This project is licensed under the [MIT License](LICENSE).

---
*Built with ❤️ for the Genesis Hackathon.*
