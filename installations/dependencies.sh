#!/bin/sh
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
sudo apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654

sudo apt-get update -y # To get the latest package lists
sudo apt-get upgrade -y # To install the latest package 
sudo apt-get install xorg -y
sudo apt-get install build-essential -y
sudo apt-get install g++ libglu1-mesa-dev freeglut3 freeglut3-dev mesa-common-dev qt5-default -y
sudo apt-get install curl gstreamer1.0-tools gstreamer1.0-alsa gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav libgstreamer-plugins-base1.0-dev libgstreamer1.0-dev libjpeg-dev libglu1-mesa-dev freeglut3 freeglut3-dev mesa-common-dev libusb-1.0-0-dev libusb-1.0-0 libudev-dev -y
sudo apt-get install libsdl1.2-dev libsdl2-dev -y


