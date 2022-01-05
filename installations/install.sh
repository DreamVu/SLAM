#!/bin/bash

chmod +x ./*.sh

chmod +x ../Explorer/Explorer

read -s -p "password for $USER: " PASSWORD
echo $PASSWORD
echo "echo $PASSWORD | sudo -S jetson_clocks" >> ~/.bashrc

./uninstall.sh 

sudo ./dependencies.sh

./ros_cmake.sh

./setup_python_env.sh

./setup_camera_data.sh 

cd python_data

chmod +x setup_python_lib.sh
./setup_python_lib.sh


if [ $# -ge 1 ]; 
then 
	echo "[INFO] Rebuilding Engines"
	if [ "$1" -eq 1 ];
	then
		chmod +x make_engines.sh 
		if [ $# -eq 2 ];
		then
			./make_engines.sh $2
		else
			./make_engines.sh 3500
	    fi
	else
	echo "[INFO] Skipping Rebuilding Engines"	
	fi    

else
	echo "[INFO] Skipping Rebuilding Engines"
fi

cd ..

source dreamvu_ws/bin/activate
python test_py_installations.py

./timeout_patch.sh

./setup_connection.sh

sudo ./PAL_udev.sh

cd ../code_samples
chmod +x compile.sh
./compile.sh
