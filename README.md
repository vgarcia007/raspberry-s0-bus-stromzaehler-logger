# raspberry-s0-bus-stromzaehler-logger

PIN 5 / GPIO 3 = +  
PIN 34 = GROUND

## change BUTTON_PIN var in strom.c  
See WiringPi Pinout  
GPIO 3 = 9 in WiringPi  

## Compile
gcc -lwiringPi -o strom strom.c

##
Edit service  
sudo cp service /etc/init.d/stromlogger  

cd /etc/init.d/  

sudo chmod 755 stromlogger  

sudo update-rc.d stromlogger defaults

### control service  
sudo service stromlogger stop  
sudo service stromlogger start  
sudo service stromlogger restart  


#### credit goes to http://www.skrue.de/wp/?p=41
