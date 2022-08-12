# Hip Motion Capture- Software

Visualisation software using [Three.js](https://threejs.org/), which is a WebGL wrapper, and the experimental Web Serial API. Accepts a data stream consisting of gyroscope, accelerometer, magnetometer and quaternion for each sensor.

___
<h3 align="center"> ->> <a href="https://menglinmaker-hip-motion-capture.netlify.app/">Live Demo!</a> <<- </h3>

___

<div align='center'>
<img width="300" src="https://user-images.githubusercontent.com/39476147/184284635-813f5fff-4b3c-4afb-ae10-3b8ae9ba4124.gif"/>
</div>

## Instructions
**Live Visualisation Streaming**
1. Select baud rate.
2. Click connect and choose COM port.
**Recording Serial Data**
3. Choose buffer size for saving CSV (Optional).
4. Click save and enter file name to save (Optional).
Note: Choose a reasonable value for CSV buffer size: under 10^6.


## Block Diagram
<div align='center'>
<img width="600" src="https://user-images.githubusercontent.com/39476147/184133450-62b48f3b-8428-49a7-9e68-98947d0beceb.png"/>
</div>
