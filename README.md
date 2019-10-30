# od_demo

## git
mkdir -p ~/dev_s && cd dev_s

git clone https://github.com/Comverser/od_demo

## dependencies
sudo apt install libgtk-3-dev
### for development
sudo apt install build-essential
sudo apt install glade

## compile
gcc -o Optical_Switch_Demo main.c -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic -lwiringPi
