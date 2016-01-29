First install userspace USB programming library development files:
sudo apt-get install libusb-1.0-0-dev

This is my /etc/apt/sources.list:
deb http://mirrordirector.raspbian.org/raspbian/ wheezy main contrib non-free rpi
deb http://archive.mene.za.net/raspbian wheezy contrib

copy library to /usr/lib:
sudo cp -p libavs.so.0.1.0 /usr/lib

create symblic links:
cd /usr/lib
sudo ln -sf libavs.so.0.1.0 libavs.so
sudo ln -sf libavs.so.0.1.0 libavs.so.0

