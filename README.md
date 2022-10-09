# mpu

A robot car system using Raspberry Pi 2 as main processing unit, Raspberry Pi pico as Slave motion controller, MPU6050 for motion tracking and PCA9685 for PWM motor control.

![alt text](https://github.com/Fabrice-Beya/robot-car/blob/0dfa4a569ecc2751b2ae9f7f828b8e67c82686ea/System%20Overview.png)

The main controller task exposes an cli interface which allows the user to control the robot by sending direction, speed and runetime(how long to move) parameters. These commands are send to the rp2040 over spi interface. The rp2040 in turn sends the neccary commands to the motors via PWM controller.
