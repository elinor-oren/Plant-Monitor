
## Overview
This repository contains (an attempt at) documention for a plant monitor, with the main code located in 'soilData'. ('_plantMonitor.ino' just has more comments.) The end result is a data dashboard visualized in Grafana and webpage with live moisture, temperature, and humidity data for your ✨ beloved ✨ houseplant. This project is part of the coursework for the Connected Environments module (CASA0014) at UCL CASA, and a tutorial for this project can be found [here.](https://workshops.cetools.org/codelabs/CASA0014-2-Plant-Monitor/index.html?index=..%2F..casa0014#0)



The sensor uses a DHT 22 to detect temperature and humidity as well as the resistance levels of two nails embedded in the plant to detect soil moisture; moisture readings are _highly variable_ and are _dependet on nail placement._ Make sure that the nails are close enough to get a moisture reading. We use the Adafruit Feather HUZZAH ESP8266 as a base to connect to Wi-Fi and transmit data via MQTT for display. 

## Workflow 
* Step 1A: Sensor Set-up
* Step 1B: Publishing Sensor Data 
* Step 2: Storing + Visualizing Data
>All materials are listed below. *INSERT LINK TO BELOW*

## Step 1A: Sensor Set-up 
Materials: 
* Feather Huzzah ESP8266
* Arduino Uno
* DHT22 temperature and humidity sensor 
* Nails
* Soldering iron + spare wire 
* Resistors (2 x 10k ohm, 1 x 200 ohm, 1 x 100 ohm)

### Hardware Assembly: 
The Feather Huzzah uses the takes readings every minute. There is an NPN transistor to turn off voltage between readings, reducing nail corrosion. The analog pin of the Huzzah reads at a max of 1.0V, so two resistors are used to shift voltage from 3V to 1V.

<img width="782" alt="image" src="https://github.com/elinor-oren/Plant-Monitor/assets/127933946/bb8046cd-5a8b-491f-b0e8-c5368bcf148d"><br>

Here is a close-up of the pinout diagram:

![image](https://github.com/elinor-oren/Plant-Monitor/assets/127933946/042e0a72-8cc0-40d5-9a4d-68a615710f96)
>Image used from CASA tutorial.


## Step 1B: Publishing Sensor Data 
Materials & Libraries: 
* EzTime // adapt londonTime code to your local timezone
* ESP8266WiFi.h
* [ezTime library](https://github.com/ropg/ezTime)
* [PubSubClient library](https://github.com/knolleary/pubsubclient/releases/tag/v2.8)

Ensure that you have the above libraries downloaded in your IDE! Once the build is finished, you should be able to use the [soilData](https://github.com/elinor-oren/Plant-Monitor/blob/00d975345c3ef62f83167b6f4ce0d69060e34b92/_plantMonitor/soilData.ino) code in this repo to start collecting and publishing data. Be sure to update the wifi and server details using [update_arduino_secrets.h](https://github.com/elinor-oren/Plant-Monitor/blob/00d975345c3ef62f83167b6f4ce0d69060e34b92/_plantMonitor/update_arduino_secrets.h). From here, Arduino IDE assigns pins to inputs, starts wifi, communicates the moisture and temperature values as outputs, and sends it to the MQTT connection.


##

## Step 2: Storing + Visualizing Data 
Materials & Libraries:  
* microSD card
* Raspberry Pi 4
* InfluxDB + Telegraf Plug-in
* Grafana + [Raspberry Pi template](https://github.com/influxdata/community-templates/blob/master/raspberry-pi/raspberry-pi-system.yml)
* [MQTT Explorer](http://mqtt-explorer.com/) > check whether your data is publishing

You'll first want to check that your data is publishing to the MQTT Server; you can use MQTT Explorer to see the realtime values your sensor is outputting. 

<img width="1292" alt="image" src="https://github.com/elinor-oren/Plant-Monitor/assets/127933946/57b49c5c-d6cd-4391-9877-266f82068786">


The Raspberry Pi will capture the MQTT data via Telegraf, store it in an InfluxDB based database, and publish it to a Grafana visualization dashboard. You must download InfluxDB, Telegraph, and Grafana to your Raspbeery Pi's SD card via "ssh" using the Terminal (OS) or Putty (Windows). To get help with the SD card setup, download the [imager](https://www.raspberrypi.com/software/) for your operating system and follow along with [this](https://www.tomshardware.com/reviews/raspberry-pi-headless-setup-how-to,6028.html) walkthrough.  

NOTE: You must make sure that your soil sensor and raspberry pi are on the same wifi! 

## Optional: Step 3: Additional Integrations
* Blooming flower powered by an SG90-HV servo
  > this flower takes moisture data to provide a real-time visualization of whether your flower needs to be watered. 
#include <Servo.h>

## Sources 
- 3D Print Files: https://www.thingiverse.com/thing:5889692
- Servo Code: https://docs.arduino.cc/learn/electronics/servo-motors

## Overview of Materials & Libraries 

Boards
> brb adding in my affiliate links 💸
* Feather Huzzah ESP8266
* Arduino Uno 
* Raspberry Pi 4 + microSD Card (at least 8GB)

Soil Sensor
* DHT22 temperature and humidity sensor // you could probably use the DHT12!
* Nails
* Soldering wire + iron 
* Resistors (2 x 10k ohm, 1 x 200 ohm, 1 x 100 ohm)


