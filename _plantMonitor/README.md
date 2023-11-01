
## Overview
This repository contains (an attempt at) documention for a plant monitor, with the main code located in 'soilData'. ('_plantMonitor.ino' just has more comments.) The end result is a data dashboard visualized in Grafana and webpage with live moisture, temperature, and humidity data for your ✨ beloved ✨ houseplant. This project is part of the coursework for the Connected Environments module (CASA0014) at UCL CASA, and a tutorial for this project can be found [here.](https://workshops.cetools.org/codelabs/CASA0014-2-Plant-Monitor/index.html?index=..%2F..casa0014#0)

*INSERT IMAGE OF PLANT*

The sensor uses electrolysis and resistance levels to detect moisture, which means that these readings are _highly variable_ and are _dependet on nail placement._ Make sure that the nails are close enough to get a moisture reading! 

## Workflow 
* Step 1A: Sensor Set-up
* Step 1B: Publishing Sensor Data 
* Step 2: Storing + Visualizing Data
>All materials are listed below. *INSERT LINK TO BELOW*

## Step 1A: Sensor Set-up 
Materials: 
* Feather Huzzah ESP8266
* Arduino Uno
* DHT22 temperature and humidity sensor // you could probably use the DHT12!
* Nails
* Soldering wire + iron 
* Resistors (2 x 10k ohm, 1 x 200 ohm, 1 x 100 ohm)

Hardware Assembly: 
 *FIGURE OUT HOW TO INSERT PICTURES*
 

## Step 1B: Publishing Sensor Data 
Materials & Libraries 
* EzTime 
* Wifi
* MQTT
  
Once the build is finished, the Arduino IDE function assigns pins to inputs, starts wifi, communicates the moisture and temperature values as outputs, and sends it to the MQTT connection.

## Step 2: Storing + Visualizing Data 
Materials & Libraries:  
* microSD card
* Raspberry Pi 4
* InfluxDB + Telegraf Plug-in
* Grafana + [Raspberry Pi template](https://github.com/influxdata/community-templates/blob/master/raspberry-pi/raspberry-pi-system.yml)

The Raspberry Pi captures the MQTT data via Telegraf, stores it in an InfluxDB based database, and publishes to a Grafana visualization dashboard. It is essential that the Raspberry Pi is on the same WiFi network as the Soil Sensor.
You must download InfluxDB, Telegraph, and Grafana to your SD card via "ssh" using the Terminal (OS).


## Additional Integrations
* Blooming flower powered by an SG90-HV servo
  > this flower takes moisture data to provide a real-time visualization of whether your flower needs to be watered. 
#include <Servo.h>
  
* NO2 sensor 

## Sources 
- 3D Print Files: https://www.thingiverse.com/thing:5889692
- Servo Code 

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

Arduino  
> add these on the Arduino IDE
* ESP8266WiFi.h
* [ezTime library](https://github.com/ropg/ezTime)
* [PubSubClient library](https://github.com/knolleary/pubsubclient/releases/tag/v2.8)

Data Visualization
* [MQTT Explorer](http://mqtt-explorer.com/)
> to install on your raspberry pi with command line
* InfluxDB + Telegraf plug-in) 
* Grafana


