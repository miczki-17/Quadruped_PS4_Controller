# 🕷️ ESP32 Quadruped Robotics Platform

[![C++](https://img.shields.io/badge/Language-C++-blue.svg)](https://isocpp.org/)
[![Platform](https://img.shields.io/badge/Platform-ESP32-green.svg)](https://www.espressif.com/en/products/socs/esp32)
[![RTOS](https://img.shields.io/badge/RTOS-FreeRTOS-orange.svg)](https://www.freertos.org/)
[![CAD](https://img.shields.io/badge/CAD-Fusion%20360-red.svg)](https://www.autodesk.com/products/fusion-360/)

Zaawansowany, czteronożny robot kroczący zaprojektowany od zera (CAD 3D) i oprogramowany w języku C++. Projekt demonstruje praktyczne zastosowanie kinematyki odwrotnej (IK), systemów czasu rzeczywistego (FreeRTOS) oraz aktywnej stabilizacji z wykorzystaniem fuzji danych z czujników (IMU).

🎥 <img src="Media/Images/mages/my_quadruped.gif" width="500" alt="Chód robota">

---

## 🚀 Główne cechy i rozwiązania inżynierskie

To nie jest standardowy projekt typu "wgraj gotowca". Cały system ruchu i logiki został zaprojektowany z myślą o płynności, wydajności i stabilności:

### 📐 Autorska Kinematyka Odwrotna (Inverse Kinematics 3-DOF)
* Zaimplementowano w pełni autorski model matematyczny (klasa `IK`) obliczający pozycje kątowe stawów na podstawie pożądanych współrzędnych XYZ stopy (3 stopnie swobody na nogę).
* System pozwala na niezależną translację całego korpusu (X, Y, Z) oraz rotację **Roll, Pitch, Yaw** bez utraty przyczepności stóp.

### 🧠 Architektura Wielowątkowa (FreeRTOS Dual-Core)
Aby uniknąć opóźnień (jittera) na serwomechanizmach i zapewnić płynną komunikację Bluetooth, system wykorzystuje oba rdzenie mikrokontrolera ESP32:
* **Core 1 (Główna pętla):** Obsługuje obliczenia trygonometryczne IK, odczyt IMU oraz sterowanie sprzętowymi timerami PWM dla 12 serw.
* **Core 0 (Service Task):** Przypisany do obsługi stosu Bluetooth (Bluepad32), parsowania danych z kontrolera PS4 oraz generowania wektorów chodu w klasie `Gait2`.

### 🏃 Dynamiczny Silnik Chodu (Gait Engine)
Klasa `Gait2` odpowiada za generowanie trajektorii ruchu:
* **Filtry LPF (Low-Pass Filter):** Wejścia z kontrolera są filtrowane, co zapobiega gwałtownym szarpnięciom konstrukcji podczas startu i hamowania.
* **Zmienna częstotliwość i wysokość kroku:** Parametry chodu adaptują się dynamicznie na podstawie zadanej prędkości liniowej (w przedziale 1.5Hz – 3.0Hz).
* **Trajektoria sinusoidalna:** Faza przenoszenia nogi (swing) wykorzystuje funkcję trygonometryczną do płynnego podnoszenia i opuszczania stopy.

### ⚖️ Aktywna Stabilizacja Korpusu (IMU Auto-leveling)
* Wykorzystanie czujnika **MPU6050** do kompensacji pochylenia terenu.
* Zaimplementowano programowe filtry dolnoprzepustowe (Low-Pass Filter) na odczytach kątów z żyroskopu/akcelerometru.
* **Delayed Offset Calibration:** Robot wykonuje samokalibrację "zera" dopiero po fizycznym wstaniu i odczekaniu 1.5 sekundy na stabilizację serw.

---

## 🛠️ Stack Technologiczny

**Hardware:**
* Mikrokontroler: **ESP32** (Wi-Fi/Bluetooth SoC)
* Czujnik: **MPU6050** (Akcelerometr + Żyroskop po I2C)
* Serwomechanizmy: 12x (obsługa za pomocą sprzętowych przerwań - *ESP32_ISR_Servo*)
* Kontroler: **PlayStation 4 DualShock** (Bluetooth HID)

**Software & Narzędzia:**
* Język: **C/C++** * Środowisko: Oparte o rdzeń Arduino z integracją **FreeRTOS**
* Biblioteki: `Bluepad32` (stos BT), `MPU6050_light`, autorskie biblioteki matematyczne.
* Modelowanie 3D: **Autodesk Fusion 360** (Customowe części)
* Produkcja: Druk 3D (FDM)

---

## 🎮 Instrukcja Uruchomienia

1. **Zasilanie:** Włącz główne zasilanie robota (uwaga na piki prądowe przy starcie 12 serw). Robot automatycznie przejdzie w stan nasłuchiwania.
2. **Parowanie Bluetooth:** Na kontrolerze PS4 naciśnij i przytrzymaj jednocześnie przyciski **PS + SHARE** aż dioda zacznie szybko migać na biało.
3. **Inicjalizacja:** ESP32 przechwyci adres MAC kontrolera, połączy się i zainicjuje sekwencję wstawania (Stand-up sequence).
4. **Kalibracja:** Nie ruszaj robota przez 1.5 sekundy! Trwa inicjalizacja poziomu referencyjnego (Zero-level) dla czujnika MPU. Dioda kontrolera zmieni kolor na zielony.
5. **Sterowanie:** Robot jest gotowy do akcji! Lewa gałka: ruch poziomy. Prawa gałka: obroty i pochylenia.

---

## 📂 Struktura Projektu

Projekt podzielony jest modułowo dla łatwego utrzymania i rozwoju:
* `/libs/IK` - Klasy i struktury definiujące nogi, punkty w przestrzeni 3D oraz logikę rozwiązywania kinematyki odwrotnej.
* `/libs/Gait` - Generator trajektorii (algorytmy chodu).
* `/headers` - Pliki konfiguracyjne pinów, stałych robota i stref martwych kontrolera.
* `main.ino` - Główny szkielet programu i inicjalizacja zadań (Tasks).

---
*Autor: [Mikołaj Papierski / mikolaj.papierski20@gmail.com]*
