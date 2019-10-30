# od_demo



## dependencies

sudo apt install git

sudo apt install libgtk-3-dev

### for development

sudo apt install build-essential

sudo apt install glade



## git

mkdir -p ~/Desktop/Optical_Switch_Demo && cd $_

git clone https://github.com/Comverser/od_demo.git



## compile

gcc -o Optical_Switch_Demo main.c -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic -lwiringPi
