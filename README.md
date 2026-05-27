# 🚁 LiDAR-Based Pilot Assist System — FPV Drone

> Real-time obstacle detection system using LiDAR and ultrasonic sensor fusion on a 5" FPV drone. Achieves **90% obstacle detection rate** with **80–100ms response latency**. Published in conference proceedings.

---

## 📹 Flight Demo

https://github.com/Dhrxv27/Lidar-pilot-assist-for-FPV-drones/raw/main/demo_college.mp4

---

## 🎤 Project Presentation

https://github.com/Dhrxv27/Lidar-pilot-assist-for-FPV-drones/raw/main/project_explanation.mp4

*Presented at department seminar — visual walkthrough of system architecture, sensor fusion logic, and results.*

---

## 🔍 Overview

Traditional FPV drones rely entirely on pilot visual feedback for obstacle avoidance, creating significant risk in GPS-denied or low-visibility environments. This project implements an onboard pilot-assist system that provides real-time proximity alerts using a sensor fusion approach — combining LiDAR and ultrasonic sensing with graduated threshold-based decision logic on a lightweight embedded platform.

---

## ⚙️ Hardware Stack

| Component | Specification |
|---|---|
| Drone Frame | 5" FPV Quadrotor |
| Primary Sensor | TF Mini-S LiDAR |
| Secondary Sensor | HC-SR04 Ultrasonic |
| Microcontroller | Arduino Nano (ATmega328P) |
| Flight Controller | Betaflight / INAV |

---

## 💻 Software Stack

- Arduino C++ — sensor fusion and graduated alert logic
- Rolling average filter for noise reduction
- Dual-threshold system: WARNING (50cm) and CRITICAL (20cm)
- Proportional buzzer response — faster alerts as obstacle proximity increases
- Betaflight / INAV — flight controller configuration

---

## 📊 Results

| Metric | Value |
|---|---|
| Obstacle Detection Rate | 90% |
| Response Latency | 80–100 ms |
| Operating Environment | GPS-denied indoor/outdoor |
| Alert Levels | WARNING + CRITICAL |

---

## 🗂️ Repository Structure

```
├── obstacle_detection.ino           # Sensor fusion code with graduated alerts
├── demo_college.mp4                 # Live flight demo
├── project_explanation.mp4          # Department seminar presentation
├── Lidar_Report.docx                # Full project report
└── LiDAR_FPVD_PilotAssist_ATIGB2026F.pdf  # Conference paper (ATiGB 2026)
```

---

## 📄 Publication

This work was presented and published at the **ATiGB 2026 Conference** (domestic proceedings).

> *"LiDAR-Based Object Detection and Pilot Assist System for FPV Drones in GPS Denied Environments"*  
> Dhruv Bakshi, Bhavesh P, Mangala Gowri — ATiGB 2026

---

## 👤 Author

**Dhruv Bakshi**  
B.E. ECE — Sir M. Visvesvaraya Institute of Technology, Bangalore  
📧 dhruvb773@gmail.com  
🔗 [GitHub Profile](https://github.com/Dhrxv27)
