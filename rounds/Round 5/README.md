# Workshop 10.1 and 10.2: Autonomous Mode Implimentation & Prototype Testing

## Design Round 5 Scrum Planning

### What are the specific goals for this round? Aside from meeting this round’s design review deliverables, what are your own goals?
Our primary goal is testing the completed CAD for the gripper/arm mechanism and start to impliment the autonomous mode for the robot. We will need to start testing the line following sensor to determine its range of operating values and sensitivity. Another goal is to integrate the arm mechanism with controller to determine our button mapping with the servomotors. We will also need to test the arm mechanism extensively to determine if it is capable to manipulate Ken and the dinosaurs. 

### What are the backlog items from last round?
As of right now, we need to 3D print the arm mechanism and start integrating the line following sensor into our design. 

### What are the tasks needed to achieve each goal, including the backlog items?
1. Write code to start testing line following sensor - Mustafa
2. Finish designing and 3D print arm mechanism - Callum
3. Finalize button mapping and controller integration for servos - Callum 

## Workshop 10.1 Initial Thoughts on the robot 
From our testing, we determined our design was a good foundation to iterate upon. Despite our concerns with the tank treads making the robot's movement unstable and uneven, this was not an issue as the TPU used to make the tank treads provided an acceptable amount of friction. An unintended side effect of using the tank treads was that our robot was able to move in-and-out of the doll pit with ease. Due to this, we further developed our arm mechanism to be shorter because the distance required to reach the doll decreased by a fair amount when the robot entered the pit. The shorter arm made the robot less likely to tip over when objects were picked up and the torque produced by the objects will be less. In the next iteration, we will 3D print the linkage instead of laser cutting it with MDF. 3D printing will ensure that the linkage has proper clearance, ensuring the arm mechanism operates smoothly. Also, we will need to 3D print the module for the line following sensor to connect it at an appropriate height to detect the lines. 

| Part | Volume | Percent |
|------|--------|---------|
| Left Tread | 1.68 in<sup>3</sup>  | 11.2 % |
| Right Tread | 1.68 in<sup>3</sup> | 11.2 % |
| Wheels | 2.25 in<sup>3</sup>| 15 %|
| Mounts | 1.13 in<sup>3</sup>| 7.5 % |
| Total | 5.61 in<sup>3</sup>| 44.9 %|

modified from this design https://www.thingiverse.com/thing:430305