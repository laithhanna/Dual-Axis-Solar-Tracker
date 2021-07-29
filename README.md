# Dual Axis Solar Tracker

Hello everyone, this was my Sophomore design project for the "Design and Analysis of Electromechanical Systems" class. In this project I was responsible for the design
and implementation of the computer/software subsystem for the solar tracker. This file will contain information about the Arduino UNO board and description
of the project, wiring diagrams and flowcharts to visualize the algorithms used for the dual axis solar tracking and the real time power calculations.

The software was developed using the Arduino Integrated Development Environment (Arduino IDE) using the C programming language and an Arduino Uno board, which is
an open-source microcontroller board based on the Microchip ATmega328P microcontroller and developed by Arduino.cc. Moreover, The Arduino Uno has
2 microcontroller units (MCU’s): ATmega328P and ATmega16U2. Both of which are created by Atmel, which was acquired by Microchip Technology in 2016.
The ATmega328P is the main microcontroller on the UNO board. It is an 8-bit microcontroller based on AVR Reduced Instruction Set Computer (RISC) architecture.
On the other hand, the ATmega16U2 chip acts as a bridge between the computer's USB port and the main processor's serial port.
In other words, The ATmega16U2 is programmed to act like a USB-serial adapter in order to make serial communication possible between the main MCU and the computer.

This was a brief summary on the hardware and the software used in this project. Now, let’s start addressing the project itself.

Parts needed: SG90 servos (2), LCD-016M002B (1), Arduino Uno (1), Photo Resistors (4), Solar Panel P105 (1), Push Buttons (6).

All the pins and connections are addressed in the code, so here I will put the wiring diagram:

![WD](https://user-images.githubusercontent.com/84100829/127562585-f3785a89-4c7d-4576-b4ee-b49e5449a315.PNG)

The algorithm of the movement of the solar panel will be shown in the flowchart below, but before that, let us discuss it briefly: The algorithm starts with the solar panel in its initial position, then each LDR sensor will sense different light intensities and their values will be returned for comparison and for further calculations. For instance, considering azimuth direction (east to west), the average values from the two right LDRs (upper right and lower right) will be calculated and compared to the average values from the left LDR’s (upper left and lower left). If the right set of LDRs receive more light, the solar tracker moves in that direction through the left-right servomotor and will continue to rotate until the absolute value of the difference is less or equal to 10 or in other words -10< difference <10. This range is used to stabilize the system and once the solar panel is perpendicular to the sun, no further control is made. On the other hand, if the left set of LDRs receives more light, the solar tracker will move in that direction and the mechanism is the same as stated above. The same technique is used for the elevation direction (North and South). Moreover, average radiation value between the four LDR sensors that was calculated will be used as an indication to when the night has come. For instance, if this value is less than a specific little value, that turned out to be 8, it indicates that the night has come. In this case, the solar panel must return to the sun’s rising position. The flowchart below illustrates the algorithm.

![Chart](https://user-images.githubusercontent.com/84100829/127563712-8faf1059-4339-465b-8d39-46e2e84d24df.PNG)

Finally, Moving to real time power calculations. Since the solar panel is expected to output a max value of 6 volts it will be connected to a voltage divider, which its output is connected to the analog pin A5 on the Arduino Uno, since the Arduino operates on a max voltage value of 5V.  Next, adc voltage is calculated by multiplying the step size by the reference voltage which is 5V for the Arduino. Now, further calculations show that the panel voltage is equal to the adc voltage times 2. note that all those calculations are shown in the flow chart. Finally, since the voltage divider resistor values are known ( R1 = R2 = 1000 ohms), we can calculate the panel voltage output and the panel power output, and these values in addition to the solar panel current will be displayed on the lcd module. The flow chart below illustrates this algorithm:

![Power](https://user-images.githubusercontent.com/84100829/127564092-7c7a8c34-29b3-43c2-83f4-93a78a7e424a.PNG)

