# Hip motion capture
Basic hip motion visualiser based on the [IMU-Webserial-Visualiser](https://github.com/MengLinMaker/IMU-Webserial-Visualiser). A total of three quaternions are used to represent orientations for the hip and two thighs. Capable of record accelerometer, gyroscope, magnetometer and quaternion data simultaneously at a rate of 120hz.

<h3 align="center"> ->> <a href="https://menglinmaker-hip-motion-capture.netlify.app/">Live Demo!</a> <<- </h3>

<div align='center'>
<img width="100%" src="https://user-images.githubusercontent.com/39476147/184134151-e77d7593-4099-48b6-bd41-c98e1127ee23.png"/>
</div>



## Requirements for usage
This demo requires a physical construction of the hip and thigh motion capture device. Placement of sensors are shown below:

<div align='center'>
<img width="100%" src="https://user-images.githubusercontent.com/39476147/184135467-71227c2f-213e-4460-a38c-ffa0869da64e.png"/>
</div>

Please contruct a similar or equivalent device to fully use this web visualiser.



## Instructions
**Live Visualisation Streaming**
1. Select baud rate.
2. Click connect and choose COM port.
**Recording Serial Data**
3. Choose buffer size for saving CSV (Optional).
4. Click save and enter file name to save (Optional).
Note: Choose a reasonable value for CSV buffer size: under 10^6.





# Development Process
Overall there are 3 major subsections that are needed:
* Hardware: Physical device for strapping around waist and thigh, housing microcontroller and battery, plus interfacing with sensors.
* Firmware: Data collection and fusionto obtain quaternion orientations. The final data is then streamed to another ESP32 or strait to PC.
* Software: A website visualiser with data recording capabilities.

Made using [Three.js](https://threejs.org/), which is a WebGL wrapper, and the experimental Web Serial API. An ESP32 microctontroller interfaces with [FXOS8700 + FXAS21002](https://www.adafruit.com/product/3463), and two [BMX160](https://core-electronics.com.au/bmx160-9-axis-sensor-module-v1-0.html) IMUs and calculates the orientation using a [Madgwick Filter](https://ahrs.readthedocs.io/en/latest/filters/madgwick.html).
Finally the data is parsed into an array and streamed to the visualisation website.



## Hardware
Develop 



## Software
<div align='center'>
<img width="100%" src="https://user-images.githubusercontent.com/39476147/184133450-62b48f3b-8428-49a7-9e68-98947d0beceb.png"/>
</div>





# Credits
This code was modified from Mike Molinari's serialTerminal.com: https://github.com/mmiscool/serialTerminal.com
Reskinned UI and refactored the original code. Added ability to save CSV file and determine last full line, stored in "currentData".
Access the original webserial terminal here: https://www.serialterminal.com
