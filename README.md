[![Build Status](https://grahamplata.visualstudio.com/WeatherBuddy/_apis/build/status/WeatherBuddy-CI?branchName=master)](https://grahamplata.visualstudio.com/WeatherBuddy/_build/latest?definitionId=1&branchName=master)

# WeatherBuddy

A weather interface for the coffee table... Below is the Source for the WeatherBuddy project. Containing sources for board hardware/layout, firmware and User Interface.

## Purpose

The purpose of this project is to learn a bit about internet connected microcontrollers.

## Hardware

- Particle Photon -- Wifi enabled MicroController
- Nextion Enhanced NX4024K032 - Generic 3.2'' HMI Touch Display
- Jumper Cables

## Software Stack

- [C/C++] - Arduino language... basically C/C++
- [Nextion Editor] - Used for building interfaces for Nextion HMIs

### Installation

```sh
# clone the repo
git clone https://github.com/grahamplata/WeatherBuddy.git
```

### Scripts

```sh
# Locally builds for photon
$ ./bin/build
# Places Photon into DFU mode
$ ./bin/dfu-mac
# Flashes the current build to local usb photon
$ ./bin/flash
```
