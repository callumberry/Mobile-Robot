# Workshop 6.1 Electical Schematic and Power Budgeting

## Design Round 3 Scrum Planning

### What are the specific goals for this round? Aside from meeting this round’s design review deliverables, what are your own goals?
Our primary goal is completing the CAD for the chassis design for laser cutting as well as starting with arm/gripper design. As well as determining the material types that will be used for the arm/gripper. Another goal is fine tuning our PID control for the DC motor with the wheels now attached. Another goal is too get DC motor control working with the remote control, as well as finalizing the button mapping for the robot.

### What are the backlog items from last round?
As of right now, we need to start integrating the controller with the DC motors, finsh up CAD modelling the design and create a more accurate 2D diagram of the board.

### What are the tasks needed to achieve each goal, including the backlog items?
1. Integrate DC motors with controller - Mustafa
2. Create accurate 2D model of the compeition board - Callum
3. Fine Tune PID loop for DC motor - Mustafa
4. Complete Chassis 3D model and begin arm/gripper - Callum
5. Material choice for arm/gripper - Callum and Mustafa
6. Finalize button mapping - Callum and Mustafa

## Electrical Schematic
Electrical Schematic made using Cirkit Designer
![Screenshot](Images/Electrical_Schematic.png)
![Screenshot](Images/photo_elec_subsystem.jpg)

## Power Budgeting *
| Component | Voltage (V) | Current Draw (A) | Power (W) | Source |
|-----------|---------|--------------|-----------|--------|
| DC Motor w/Encoder | 6 | 0.13 (3.2) | 0.78(19.2) | https://www.dfrobot.com/product-1617.html
| DC Motor w/Encoder | 6 | 0.13 (3.2) | 0.78(19.2) | https://www.dfrobot.com/product-1617.html
| TB6612FNG | 3.3 | 0.0011 (0.0018) | 3.63 (5.94) | https://www.sparkfun.com/datasheets/Robotics/TB6612FNG.pdf
| Hitec HS-422 | 6 | 0.008 (0.15) | 0.048 (0.9)| https://cdn.robotshop.com/media/h/hit/rb-hit-27/pdf/hs422-31422s.pdf
| Hitec HS-422 | 6 | 0.008 (0.15) | 0.048 (0.9)| https://cdn.robotshop.com/media/h/hit/rb-hit-27/pdf/hs422-31422s.pdf
| Hitec HS-422 | 6 | 0.008 (0.15) | 0.048 (0.9)| https://cdn.robotshop.com/media/h/hit/rb-hit-27/pdf/hs422-31422s.pdf
| Line Follower | 3.3 | 0.075 | 0.2475 | https://cdn.robotshop.com/media/g/gtd/rb-gtd-02/pdf/linefollowerdatasheet.pdf
| Pi Pico | 5 | 0.05 (0.15) | 0.25 (0.75) | https://datasheets.raspberrypi.com/picow/pico-w-datasheet.pdf?_gl=1\*11bp2lj*_ga\*NzU5OTYyNDQzLjE3MDg5NjQ1NjM.\*_ga_22FD70LWDS*MTcwODk2NDU3MC4xLjAuMTcwODk2NDU3MC4wLjAuMA.. https://lastminuteengineers.com/getting-started-with-raspberry-pi-pico-w/#:~:text=On%20the%20board%2C%20there%20is,Pico%20W%20consumes%20about%2050mA.
| Total || 0.4101 (7.0768) | 5.8315 (48.0375) |

| Battery | Voltage (V) | Current (A) | Power (W)
|------|--------|---------|-----|
| Finish |  |  | |


Therefore the battery will last __ to __ hours.

## 3D printing tally
![Screenshot](3D/wheelPrint.png)
![Screenshot](3D/treads.png)

| Part | Volume | Percent |
|------|--------|---------|
| Left Tread | 1.68 in<sup>3</sup>  | 11.2 % |
| Right Tread | 1.68 in<sup>3</sup> | 11.2 % |
| Wheels | 2.25 in<sup>3</sup>| 15 %|
| Total | 5.61 in<sup>3</sup>| 37.4 %|

modified from this design https://www.thingiverse.com/thing:430305

# Workshop 6.2 Mechanical Module Assembly

# Mechanical Module *
![Screenshot](Images/mechanical.jpg)
The mechanical module is the 

# Workshop 7.1 Module Integration

## Integrated Module *
![Screenshot](Images/integration.jpg)
finish
talk about

## Team Health Assessment and Peer Feedback *
finish
summarize discussions

