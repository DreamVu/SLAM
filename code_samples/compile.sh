 g++ 004_laser_scan.cpp ../lib/libPAL.so ../lib/libPAL_DE1.so ../lib/libPAL_DE2.so ../lib/libPAL_SSD.so ../lib/libPAL_DEPTH.so /usr/src/tensorrt/bin/common/logger.o `pkg-config --libs --cflags opencv python3 libusb-1.0`   -g  -o 004_laser_scan.out -I../include/ -lv4l2 -lpthread -lcudart -L/usr/local/cuda/lib64 -lnvinfer -I/usr/local/bin/data/inc -w -ludev -std=c++11

