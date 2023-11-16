## Overview
This repository contains (an attempt at) documention for a plant monitor, with the main code located in 'soilData'. ('_plantMonitor.ino' just has more comments.) The end result is a data dashboard visualized in Grafana and webpage with live moisture, temperature, and humidity data for your ✨ beloved ✨ houseplant. This project is part of the coursework for the Connected Environments module (CASA0014) at UCL CASA, and a tutorial for this project can be found [here.](https://workshops.cetools.org/codelabs/CASA0014-2-Plant-Monitor/index.html?index=..%2F..casa0014#0)

![plant-with-monitor](https://github.com/elinor-oren/Plant-Monitor/assets/127933946/4257876b-0220-4251-a2c7-f1a88bc011da)


The sensor uses a DHT 22 to detect temperature and humidity as well as the resistance levels of two nails embedded in the plant to detect soil moisture; moisture readings are _highly variable_ and are _dependent on nail placement._ Make sure that the nails are close enough to get a moisture reading. We use the Adafruit Feather HUZZAH ESP8266 as a base to connect to Wi-Fi and transmit data via MQTT for display. 

## Workflow 
* Step 1: Sensor Set-up
* Step 2: Publishing Sensor Data 
* Step 3: Storing + Visualizing Data
>All materials are listed below. *INSERT LINK TO BELOW*

## Step 1: Sensor Set-up 
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


## Step 2: Publishing Sensor Data 
Materials & Libraries: 
* EzTime // adapt londonTime code to your local timezone
* ESP8266WiFi.h
* [ezTime library](https://github.com/ropg/ezTime)
* [PubSubClient library](https://github.com/knolleary/pubsubclient/releases/tag/v2.8)
* [MQTT Explorer](http://mqtt-explorer.com/) > check whether your data is publishing

Ensure that you have the above libraries downloaded in your IDE! Once the build is finished, you should be able to clone the [soilData](https://github.com/elinor-oren/Plant-Monitor/blob/00d975345c3ef62f83167b6f4ce0d69060e34b92/_plantMonitor/soilData.ino) code in this repo to start collecting and publishing data. This code assigns pins to inputs, starts wifi, communicates the moisture and temperature values as outputs, and sends it to the MQTT connection. Be sure to update the wifi and server details by using [update_arduino_secrets.h](https://github.com/elinor-oren/Plant-Monitor/blob/00d975345c3ef62f83167b6f4ce0d69060e34b92/_plantMonitor/update_arduino_secrets.h) and placing it in the same folder. 

From here, you should ve able to check whether your data is publishing to the MQTT Server; you can use MQTT Explorer to see the realtime values your sensor is outputting. 

<img width="1292" alt="image" src="https://github.com/elinor-oren/Plant-Monitor/assets/127933946/57b49c5c-d6cd-4391-9877-266f82068786">



##

## Step 3: Storing + Visualizing Data 
Materials & Libraries:  
* microSD card
* Raspberry Pi 4
* InfluxDB + Telegraf Plug-ins
* Grafana + [Raspberry Pi template](https://github.com/influxdata/community-templates/blob/master/raspberry-pi/raspberry-pi-system.yml)
NOTE: You must make sure that your soil sensor and raspberry pi are on the same wifi! You can use the ESP8266WifiMulti.h library to add wifi networks.


The Raspberry Pi will capture the MQTT data via Telegraf, store it in a time-based InfluxDB based database, and publish it to a Grafana visualization dashboard to view and collect historical data. You must download InfluxDB, Telegraph, and Grafana to your Raspbeery Pi's SD card via "SSH" using the Terminal (OS) or Putty (Windows). To get help with the SD card setup, download the [imager](https://www.raspberrypi.com/software/) for your operating system and follow along with [this](https://www.tomshardware.com/reviews/raspberry-pi-headless-setup-how-to,6028.html) walkthrough. (When installing, be sure to navigate to the Services tab and toggle enable SSH to on.)

#### Database Setup (InfluxDB) 
We first must create the shell for our data to load and display to using InfluxDB. To install InfluxDB to your Rasberry Pi and display your timeseries data, SSH into your pi and use the Ubuntu & Debian code [here](https://www.influxdata.com/downloads/#influxdb). Check to see that it's working by running a local instance by navigating to ```<your-hostname>:8086``` into your web browser. 

Add the Grafana + Raspberry Pi template linked above.

Then create a new ```mqtt-data``` bucket in the Load Data section to create a storage for your plant data. At this point, your screen should look like this:

<img width="1715" alt="mqtt-data" src="https://github.com/elinor-oren/Plant-Monitor/assets/127933946/6c6ab601-b5e4-405a-ad0b-6bcaa8fd2d55">


#### Streaming Data Setup (Telegraf)
Install telegraf via SSH 

```sudo apt-get update && sudo apt-get install telegraf -y```

Update the telegraf config file to include your API keys - you can use the main one for convenience or your MQTT bucket API. 


#### Enhanced Visualization (Grafana)
Grafana can be used for better visualizations of your data. Still in your Raspberry Pi’s terminal, via SSH, type the following to add the Grafana GPG key, install it, and run it as a service:

```
wget -O- https://packages.grafana.com/gpg.key | gpg --dearmor | sudo tee /usr/share/keyrings/grafana-archive-keyring.gpg >/dev/null
echo "deb [signed-by=/usr/share/keyrings/grafana-archive-keyring.gpg] https://packages.grafana.com/oss/deb stable main" | sudo tee /etc/apt/sources.list.d/grafana.list

sudo apt update && sudo apt install -y grafana

sudo systemctl unmask grafana-server.service
sudo systemctl start grafana-server
sudo systemctl enable grafana-server.service
```
<img width="1225" alt="grafana-data" src="https://github.com/elinor-oren/Plant-Monitor/assets/127933946/471c1c59-c999-45c3-b71d-2a2973c34864">



## Optional: Step 4: Additional Integrations
* Blooming flower powered by an SG90-HV servo
  > this code takes moisture data to provide a real-time visualization of whether your plant needs to be watered by applying a blooming effect when the moisture data is too low. 
#include <Servo.h> // this library is pre-installed on the Arduino IDE

![image](https://github.com/elinor-oren/Plant-Monitor/assets/127933946/1c3ecb10-ea9a-4a76-9736-2ccb57addce3)

I'm still troubleshooting this bit... (and haven't figured out how to resize images)

![scrap-plastic](https://github.com/elinor-oren/Plant-Monitor/assets/127933946/d0ef62b4-89ab-47bc-b63a-a2e194d6bc63)


but have made a simplified representation of what this blooming flower *could* look like and have included sample code of this. 


https://github.com/elinor-oren/Plant-Monitor/assets/127933946/013af9c1-617a-4b49-9db3-cbb94b92e9f9



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


