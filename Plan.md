# Health and Safety Considerations

## General Safety
1. Safety Exits
2. Knowing fire extinguisher locations
3. First Aid Kit Location

## Components
1. Batteries
2. Motor

## Prototype Fabrication
1. 3D Printing Fumes (VOCs)
2. MDF Particles
3. Aluminium Cutting (Particles, Hacksaw)

## Mitigation Action
| Considerations             | Action |
| :---------------- |  :----: |
|  3D Printing Fumes       |   3D print in well ventilated room  |
|  MDF Paricles      |   Use propper PPE (mask)  |  
|  Aluminium Cutting      |   Use propper PPE and secure rod to worksurface |  

# Risk Management
1. Scope creep - losing sight of the original plan as the weeks progress and overcomplicating the design

2. Time crunch - due to a limited amount of time, the design execution is subpar and many original ideas are scrapped

3. Electronics Failure Raspberry Pi Pico getting shorted - due to poor wiring techniques or poor electrical parts, the motors may be unable to work or the Raspberry Pi Pico is shorted and unable to function

4. 3D Printing Failure/Wasting print volume - due to failures during 3D printed, large amounts of filament may be wasted which would make it difficult for an updated design to follow the 3D printing amount regulations

5. Mechanical failure - once part has been 3D printed, it is determined that the part doesn't function as well or the part breaks which means it needs to be printed again

6. Inaccurate dimensioning - due to poor dimensioning, parts of the robot cannot be integrated properly or do not meet the requirements to complete the competition objectives

7. Congested WiFi - since multiple groups will be using the same WiFi and will be controlling their robot through WiFi protocols, issues related to WiFi congestion are possible

8. Major design remodelling after testing - after testing has been done, our design ideas do not work and it is required we remodell our design to salvage the project

9. Battery Voltage Fluctuation - due to electrical components having high voltage demands, the batteries drain quickly and require often charging, which impede our testing


### Risk Matrix
![Screenshot](RiskMatrix.png)


| Risk              | Response Plan | Name |
| :---------------- |  :----: | :----: | 
|  Scope creep       |   Keep a weekly schedule to keep us on track with our original plan  | Both |
|  Time crunch       |   Allocate an amount of time for each objective to be completed so we don't waste time and can work efficiently  | Both |
|  Electronics Failure Raspberry Pi Pico getting shorted       | Wire electrical components prior to connecting them to power, ensuring they have been wired correctly, which lowers risk of electrical failures | Mustafa |
|  3D Printing Failure/Wasting print volume      | Ensure prints are oriented in a way that minimizes supports (which will minimize filament used). Also, budget out the amount of filament used for each component that needs to be printed for each iteration of that component| Callum |
|  Mechanical failure       | When 3D modelling, ensure wall thickness is suitable for the component to be sturdy. Also, if the part breaks, redesign failure point to mitigate future breaks| Callum |
|  Inaccurate dimensioning       |   Measure the board dimensions accurately, ensuring that an accurate representation of the board is provided. Double check the dimensions in CAD with the dimensions in the sketch to ensure accurate fittings| Both |
|  Congested WiFi       |   If WiFi is congested, ensure there are other objectives to work on so time isn't wasted | Mustafa |
|  Major design remodelling after testing      | Test each component individually. This will ensure that each component is working as intended before being integrated into the design| Callum|
|  Battery Voltage Fluctuation       | Use a voltmeter to determine the voltage a battery provides. This will ensure an accurate reading of the battery's voltage is known and when it is acceptable to switch the batteries. This is important information to know as it helps make sure the electrical components are working at their peak capabilities| Mustafa|


