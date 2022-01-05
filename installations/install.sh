#!/bin/bash

chmod +x ./*.sh

./uninstall.sh

sudo ./dependencies.sh

chmod +x ../Explorer/Explorer

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

