# On Bullseye you need to install WiringPi first:

git clone https://github.com/WiringPi/WiringPi.git

cd ~/wiringPi  
$ ./build


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
sudo cp service_watt /etc/init.d/wattlogger  

sudo chmod 755 /etc/init.d/stromlogger  
sudo chmod 755 /etc/init.d/wattlogger

cd /etc/init.d/  

sudo update-rc.d stromlogger defaults
sudo update-rc.d wattlogger defaults

### control service  
sudo service stromlogger stop  
sudo service stromlogger start  
sudo service stromlogger restart  


sudo service wattlogger stop  
sudo service wattlogger start  
sudo service wattlogger restart 


#### credit goes to http://www.skrue.de/wp/?p=41
