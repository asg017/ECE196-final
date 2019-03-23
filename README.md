# ECE 196 Final Project - N.S.A.

A glove that controls a robotic arm.

This repository contains code that was used in creating our final project for eCE 196.

Our project was creating a glove that contained sensors that controlled the PiB Robitic Arm. Most of the code hosted here is for the sensors that interacted with the Arduino (EMG, gyroscope/acceleromter, flex sesnors, etc.).

Our full documentation for this project can be find in our final report.

There's also miscellaneous files for other things (EAGLE, etc.).

## Contents

### `/proof_of_concepts`

This folder contains a directory for each sensor, that contains a small Arduino script that acts as a "proof of concept". It's meant for students who have never worked with the sensors in question, and just want to get a simple "hello world" set up to make sure their sensor+code is working properly.

### `/final`

The final code that we used to get the glove to work, as a MVP.

### `/dev`

Some depedencies you'll need for the gyroscope/accelerometer libraries.
