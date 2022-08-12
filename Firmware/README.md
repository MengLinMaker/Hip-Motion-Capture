# Hip Motion Capture - Firmware
Data from all three IMUs are streamed to the ESP32 microcontroller. Then the orientation is calculated using a [Madgwick Filter](https://ahrs.readthedocs.io/en/latest/filters/madgwick.html). Finally the data is parsed into an array and streamed to the visualisation website.

Since data streaming is required for fast data collection and debugging. Wireless streaming is ideal since using wires could be hazardous during a fall, disconnect and suffer signal integrity issues. [The final solution is to use ESP-NOW for data streaming.](https://github.com/MengLinMaker/ESP32-data-stream-comparisons)

<div align='center'>
<img width="600" src="https://user-images.githubusercontent.com/39476147/184151203-12f458df-35d7-4bbf-b74b-92e109fd126b.png"/>
</div>
