g++ 004_laser_scan.cpp ../lib/libPAL.so ../lib/libPAL_DE.so ../lib/libPAL_SSD.so ../lib/libPAL_DEPTH.so /usr/src/tensorrt/bin/common/logger.o `pkg-config --libs --cflags opencv`   -O3  -o 004_laser_scan.out -I../include/ -lv4l2 -lpthread -lcudart -L/usr/local/cuda/lib64 -lnvinfer

