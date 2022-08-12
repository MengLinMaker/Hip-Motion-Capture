# Hip motion capture - Hardware
The hardware consists of the battery charger, microcontroller case and sensor straps. An [ESP32 microcontroller](https://www.tinypico.com/) interfaces with [FXOS8700 + FXAS21002](https://www.adafruit.com/product/3463), and two [BMX160](https://core-electronics.com.au/bmx160-9-axis-sensor-module-v1-0.html).

<div align='center'>
<img width="450" src="https://user-images.githubusercontent.com/39476147/184135467-71227c2f-213e-4460-a38c-ffa0869da64e.png"/>
</div>

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
