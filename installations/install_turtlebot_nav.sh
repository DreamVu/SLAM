#!/usr/bin/env sh

# necessary on a fresh bionic install
sudo apt-get install git -y

cd ~/catkin_ws
mkdir -p src
cd src

git clone https://github.com/turtlebot/turtlebot.git
git clone https://github.com/turtlebot/turtlebot_msgs.git
git clone https://github.com/turtlebot/turtlebot_simulator.git

git clone https://github.com/yujinrobot/kobuki_msgs.git
git clone --single-branch --branch melodic https://github.com/yujinrobot/kobuki.git
mv kobuki/kobuki_description kobuki/kobuki_node \
  kobuki/kobuki_keyop kobuki/kobuki_safety_controller \
  kobuki/kobuki_bumper2pc ./
rm -rf kobuki

git clone --single-branch --branch melodic https://github.com/yujinrobot/kobuki_desktop.git
rm -rf kobuki_desktop

git clone https://github.com/yujinrobot/yujin_ocs.git
mv yujin_ocs/yocs_cmd_vel_mux yujin_ocs/yocs_controllers .
rm -rf yujin_ocs

sudo apt-get install ros-melodic-kobuki-* -y
sudo apt-get install ros-melodic-ecl-streams -y

# necessary for build and gazebo
sudo apt-get install ros-melodic-depthimage-to-laserscan -y
sudo apt-get install ros-melodic-joy -y
sudo apt-get install ros-melodic-yocs-velocity-smoother -y

cd ..
catkin_make

sudo apt-get install ros-melodic-gmapping -y
sudo apt-get install ros-melodic-laser-filters -y
sudo apt-get install ros-melodic-amcl -y
sudo apt-get install ros-melodic-move-base -y
sudo apt-get install ros-melodic-map-server -y
