# Hip motion capture
Basic hip motion visualiser based on the [IMU-Webserial-Visualiser](https://github.com/MengLinMaker/IMU-Webserial-Visualiser). A total of three quaternions are used to represent orientations for the hip and two thighs. Able to also record accelerometer, gyroscope and magnetometer data simultaenously.

Made using [Three.js](https://threejs.org/), which is a WebGL wrapper, and the experimental Web Serial API. An ESP32 microctontroller interfaces with [FXOS8700 + FXAS21002](https://www.adafruit.com/product/3463), and two [BMX160](https://core-electronics.com.au/bmx160-9-axis-sensor-module-v1-0.html) IMUs and calculates the orientation using a [Madgwick Filter](https://ahrs.readthedocs.io/en/latest/filters/madgwick.html).
Finally the data is parsed into an array and streamed to the visualisation website.

<h3 align="center"><a href="https://menglinmaker-imu-webserial-visualiser.netlify.app/">Live Demo!</a></h3>

### Instructions:
**Live Visualisation Streaming**
1. Select baud rate.
2. Click connect and choose COM port.
**Recording Serial Data**
3. Choose buffer size for saving CSV (Optional).
4. Click save and enter file name to save (Optional).
Note: Choose a reasonable value for CSV buffer size: under 10^6.

# Credits
This code was modified from Mike Molinari's serialTerminal.com: https://github.com/mmiscool/serialTerminal.com
Reskinned UI and refactored the original code. Added ability to save CSV file and determine last full line, stored in "currentData".
Access the original webserial terminal here: https://www.serialterminal.com
