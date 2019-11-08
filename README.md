# od_demo



## dependencies

sudo apt install git

sudo apt install libgtk-3-dev

### for development

sudo apt install build-essential

sudo apt install glade



## git

cd ~/Desktop && git clone https://github.com/Comverser/Optical_Switch_Demo.git



## compile

gcc -o Optical_Switch_Demo main.c -Wall \`pkg-config --cflags --libs gtk+-3.0\` -export-dynamic -lwiringPi
