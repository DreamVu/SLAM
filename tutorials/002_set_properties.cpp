/*

PAL TUTORIAL # 002: Changinging the camera properties

This tutorial shows the minimal code required to...
1. Query PAL API for the current camera properties.
2. Change the camera properties
3. Write the panoramas captured with different camera properties


Compile this file using the following command....
g++ 002_set_properties.cpp ../lib/libPAL.so `pkg-config --libs --cflags opencv`   -lv4l2 -lpthread -g -o 002_set_properties.out -I../include/

Run the output file using the following command....
./002_set_properties.out


*/
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>


# include <opencv2/opencv.hpp>


# include "PAL.h"


//Same as previous tutorial
inline cv::Mat Convert(PAL::Image img)
{
	//CV_8UC3  is for 3 channel RGB image (for e.g., left/right panorama)
	int type = CV_8UC3;

	return cv::Mat(img.rows, img.cols, type, img.Raw.u8_data);
}


int main(int argc, char** argv)
{

	//Same as previous tutorial
	int camera_index = -1;
    int image_width = -1;
    int image_height = -1;
    if(PAL::Init(image_width,image_height, camera_index, nullptr) == PAL::FAILURE)
        return 1; //Init failed


	// ***** NEW CODE - SPECIFIC TO THIS TUTORIAL *****
	//Get the current camera properties
	PAL::CameraProperties properties;
	unsigned int flags = PAL::CameraPropertyFlags::ALL;
    PAL::GetCameraProperties(&properties);

	//Modify the camera properties
	properties.auto_white_bal = false;
    properties.white_bal_temp = PAL::CameraProperties::MIN_WHITE_BAL_TEMP;
    flags = PAL::CameraPropertyFlags::WHITE_BAL_TEMP;
    PAL::SetCameraProperties(&properties, &flags);


	//Same as previous tutorial
    PAL::Data::Stereo stereo;
    cv::Mat frame;
	//Let the camera take some time to change the properties
	for(int i = 0; i < 10; i++)
		stereo = PAL::GetStereoData();
	frame = stereo.left;
	cv::imwrite("left1.png", stereo.left);


	// ***** NEW CODE - SPECIFIC TO THIS TUTORIAL *****
	properties.white_bal_temp = PAL::CameraProperties::MAX_WHITE_BAL_TEMP;
	flags = PAL::CameraPropertyFlags::WHITE_BAL_TEMP;
	PAL::SetCameraProperties(&properties, &flags);


	//Same as previous tutorial
	for(int i = 0; i < 10; i++)
		stereo = PAL::GetStereoData();
	frame =stereo.left;
	cv::imwrite("left2.png", frame);
    PAL::Destroy();
    
    return 0;
}
