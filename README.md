# od_demo

## program
git clone https://github.com/Comverser/od_demo/Optical_Switch_Demo.git

## dependencies
sudo apt install libgtk-3-dev
### for development
sudo apt install build-essential
sudo apt install glade

## compile
gcc -o Optical_Switch_Demo main.c -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic -lwiringPi
