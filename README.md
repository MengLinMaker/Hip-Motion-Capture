<h1 align="center"> Hip Motion Capture - <a href="https://menglinmaker-hip-motion-capture.netlify.app/">Demo</a></h1>

<div align="center">
  <img width="500" src="https://user-images.githubusercontent.com/39476147/224037990-f7bcf3e8-f0fb-47a4-9b23-752a9bbdc7d5.gif" 
  href="https://menglinmaker-hip-motion-capture.netlify.app/"/>
</div>

<div>&nbsp</div>

<div flex align="center">
<img alt="GitHub" src="https://img.shields.io/github/license/menglinmaker/Hip-Motion-Capture?style=flat-square">
<img src="https://img.shields.io/github/languages/code-size/menglinmaker/Hip-Motion-Capture?style=flat-square">
<img src="https://img.shields.io/website?down_color=red&down_message=offline&up_color=success&up_message=online&url=https://menglinmaker-hip-motion-capture.netlify.app/&style=flat-square">
</div>

Basic hip motion visualiser based on the [IMU-Webserial-Visualiser](https://github.com/MengLinMaker/IMU-Webserial-Visualiser). A total of three quaternions are used to represent orientations for the hip and two thighs. Capable of record accelerometer, gyroscope, magnetometer and quaternion data simultaneously at a rate of 120hz.

Made using [Three.js](https://threejs.org/), which is a WebGL wrapper, and the experimental Web Serial API. An ESP32 microctontroller interfaces with [FXOS8700 + FXAS21002](https://www.adafruit.com/product/3463), and two [BMX160](https://core-electronics.com.au/bmx160-9-axis-sensor-module-v1-0.html) IMUs and calculates the orientation using a [Madgwick Filter](https://ahrs.readthedocs.io/en/latest/filters/madgwick.html).
Finally the data is parsed into an array and streamed to the visualisation website.





<div>&nbsp</div><div>&nbsp</div><div>&nbsp</div><div>&nbsp</div><div>&nbsp</div>

## Requirements for usage

This demo requires a physical construction of the hip and thigh motion capture device. Placement of sensors are shown below:

<div align='center'>
<img width="450" src="https://user-images.githubusercontent.com/39476147/184135467-71227c2f-213e-4460-a38c-ffa0869da64e.png"/>
</div>

Please contruct a similar or equivalent device to fully use this web visualiser.


<div>&nbsp</div>

## Instructions
**Live Visualisation Streaming**
1. Select baud rate.
2. Click connect and choose COM port.
**Recording Serial Data**
3. Choose buffer size for saving CSV (Optional).
4. Click save and enter file name to save (Optional).
Note: Choose a reasonable value for CSV buffer size: under 10^6.

<div align='center'>
<img width="500" src="https://user-images.githubusercontent.com/39476147/184134151-e77d7593-4099-48b6-bd41-c98e1127ee23.png"/>
</div>


<div>&nbsp</div><div>&nbsp</div><div>&nbsp</div><div>&nbsp</div><div>&nbsp</div>

# Development Process
The aim of this mini project is to create a physical device and visualise live motion data. Due to the complexity of the project, it is best approached by breaking the project into subsystems

Overall there are 3 major subsystems:
* Hardware: Physical device for strapping around waist and thigh, housing microcontroller and battery, plus interfacing with sensors.
* Firmware: Data collection and fusionto obtain quaternion orientations. The final data is then streamed to another ESP32 or strait to PC.
* Software: A website visualiser with data recording capabilities.

Since some parts between subsystems depend on each other, it is best to approach the project in different stages:
1. Create simple data stream from one sensor to website.
2. Develop a simple 3D visualisation to debug the orientation algorithm. Create a 3D printed housing for microcontroller and battery.
3. Integrate multiple sensors in hardware, firmware and software visualisation.

<div>&nbsp</div>

## Hardware
Since harware development is more risky, this is prioritised.
<div align='center'>
<img width="600" src="https://user-images.githubusercontent.com/39476147/184150800-2b112a2e-f998-42f0-9713-0ee4bd7d7471.png"/>
</div>

A battery is needed for the device for wireless transmission of data. Prototyping various charger designs determine the best dimensions for the battery case. This knowledge can also be applied to the device design.

<div align='center' flex>
<img height="300" src="https://user-images.githubusercontent.com/39476147/184155974-c0cc122f-f393-4bc8-9143-edd899971f17.png"/>
<img height="300" src="https://user-images.githubusercontent.com/39476147/184157783-c2fe14be-e108-4b88-8e18-4fa32a7d4ea8.png"/>
</div>

A I2C sensor hub relays all the sensor data to the microcontroller. I2C reduces the number of wires needed and transfers data fast enough to reach over 100Hz samples from all three sensors. Flexible silicone prevents wire breakage.

<div align='center' flex>
<img height="300" src="https://user-images.githubusercontent.com/39476147/184158486-2c9df1b0-fb5c-4d18-9753-74e7c9f3f80a.png"/>
</div>

Finally, the sensors need to be attached to the thigh and waist. Straps can secure the sensors, albeit with slipping issues. Pins can also be used to secure the placement of straps.

<div align='center' flex>
<img height="300" src="https://user-images.githubusercontent.com/39476147/184160311-6496dedc-44b9-4772-84bf-5a8a77aab78d.png"/>
</div>

<div>&nbsp</div>

## Firmware
Data streaming is required for fast data collection and debugging. Wireless streaming is ideal since using wires could be hazardous during a fall, disconnect and suffer signal integrity issues. Madgwick filter is used to determine the orientation.

<div align='center'>
<img width="600" src="https://user-images.githubusercontent.com/39476147/184151203-12f458df-35d7-4bbf-b74b-92e109fd126b.png"/>
</div>

<div>&nbsp</div>

## Software
The website intefaces with serial USB using the webserial API. Three.js enables 3D visualisation. Overall, the software can be descibed in this block diagram.

<div align='center'>
<img width="600" src="https://user-images.githubusercontent.com/39476147/184133450-62b48f3b-8428-49a7-9e68-98947d0beceb.png"/>
</div>



<div>&nbsp</div><div>&nbsp</div><div>&nbsp</div><div>&nbsp</div><div>&nbsp</div>

# Credits
This code was modified from Mike Molinari's serialTerminal.com: https://github.com/mmiscool/serialTerminal.com
Reskinned UI and refactored the original code. Added ability to save CSV file and determine last full line, stored in "currentData".
Access the original webserial terminal here: https://www.serialterminal.com
