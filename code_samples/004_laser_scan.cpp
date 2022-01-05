/*

CODE SAMPLE # 004: Laser scan panorama
This code will grab the left panorama with laser scan overlayed on it and would be displayed in a window using opencv


>>>>>> Compile this code using the following command....


g++ 004_laser_scan.cpp ../lib/libPAL.so ../lib/libPAL_DE.so ../lib/libPAL_SSD.so ../lib/libPAL_DEPTH.so /usr/src/tensorrt/bin/common/logger.o `pkg-config --libs --cflags opencv`   -O3  -o 004_laser_scan.out -I../include/ -lv4l2 -lpthread -lcudart -L/usr/local/cuda/lib64 -lnvinfer




>>>>>> Execute the binary file by typing the following command...


./004_laser_scan.out


>>>>>> KEYBOARD CONTROLS:

       ESC key closes the window
       

*/


# include <stdio.h>

# include <opencv2/opencv.hpp>

# include "PAL.h"
#include "TimeLogger.h"
#include <time.h>
#include <unistd.h>

using namespace cv;
using namespace std;

PAL::Mini g_oCam;

int main( int argc, char** argv )
{

	namedWindow( "PAL Laser Scan", WINDOW_NORMAL ); // Create a window for display.

	int width, height;
	PAL::Mode mode = PAL::Mode::LASER_SCAN;

	int index = 5;
	if(argc > 1) 
	index = std::atoi(argv[1]);

	PAL::Mode def_mode = PAL::Mode::LASER_SCAN;

	char path[1024];
	sprintf(path,"/home/dreamvu/data%d/",index);

	g_oCam.SetPathtoData(path);

	if (g_oCam.Init(width, height, index, &def_mode) != PAL::SUCCESS) //Connect to the PAL camera
	{
		cout<<"Init failed"<<endl;
		return 1;
	}

	usleep(1000000);

	//discarding initial frames
	PAL::Data::ODOA_Data discard;
	discard =  g_oCam.GrabLaserScanData();		

	PAL::CameraProperties data;
	PAL::Acknowledgement ack_load = g_oCam.LoadProperties("../Explorer/SavedPalProperties.txt", &data);

	if(ack_load != PAL::SUCCESS)
	{
		cout<<"Error Loading settings! Loading default values."<<endl;
	}

	//width and height are the dimensions of each panorama.
	//Each of the panoramas are displayed at otheir original resolution.
	resizeWindow("PAL Laser Scan", width, height);

	int key = ' ';

	cout<<"Press ESC to close the window."<<endl;

	Mat output = cv::Mat::zeros(height, width, CV_8UC3);

	//Display the overlayed image
	imshow( "PAL Laser Scan", output);

	//27 = esc key. Run the loop until the ESC key is pressed

	    while(key != 27)
	    {

		PAL::Data::ODOA_Data data;

		data =  g_oCam.GrabLaserScanData();
		
		cv::Mat output = data.marked_left;

		//Display the overlayed image
		imshow( "PAL Laser Scan", output);  
		
		//Wait for the keypress - with a timeout of 1 ms
		key = waitKey(1) & 255;


	}
	// DISPLAY_LOG();
	printf("exiting the application\n");
	g_oCam.Destroy();

   
    return 0;
}

