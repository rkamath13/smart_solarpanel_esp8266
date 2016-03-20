# smart_solarpanel_esp8266
  This is a project where we interface two sensors, temperature and light to an ESP8266 module to monitor the readings from a solar panel in real time and to calculate the power generated in a given session by the panel
##Setup

###1. Install the Arduino IDE 1.6.4 or greater

    Download Arduino IDE from Arduino.cc (1.6.4 or greater) - don't use 1.6.2!
    You can use your existing IDE if you have already installed it

###2. Install the ESP8266 Board Package

    Navigate to File->Preferences and in that 
    Enter the following in Additional Board Manager URLs field
    http://arduino.esp8266.com/stable/package_esp8266com_index.json 

###3. Using Board manager to install ESP8266 package

    Navigate to Tools->Boards->Manage Boards and you will find esp8266 board support package, install it!!

###4. Setup ESP8266 support

    When you've restarted 
    -Select Adafruit HUZZAH ESP8266 from the Tools->Board dropdown
    -80 MHz as the CPU frequency
    -115200 baud upload speed
    -The matching COM port for your FTDI or USB-Serial cable
    
###5. Include the following libraries in your Arduino IDE

    Click on download as zip when you are in the library repository(links provided below)
    In the Arduino IDE, navigate to sketch->include library->add .zip library and browse to the downloaded zip file
    Links:
       Luminosity/Light sensor  --> (https://github.com/sparkfun/TSL2561_Luminosity_Sensor_BOB)
       Json object parsing      --> (https://github.com/bblanchon/ArduinoJson)

###6. Copy the [code](https://github.com/rkamath13/smart_solarpanel_esp8266/blob/master/src.ino) from this repository
    Change the *ssid* in the code
    Change the *password* in the code
    Change the *host name* of the webserver in the code

*Upload the code in the ESP8266 Huzzah Board*

###7. Hardware Setup
    Hardware connections and Sensor setup is given in the Report along with detailed explaination of the entire project
    The code is also explained in detail inside the report in the software->code section
  
