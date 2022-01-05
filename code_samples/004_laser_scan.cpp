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


int main( int argc, char** argv )
{

    namedWindow( "PAL Laser Scan", WINDOW_NORMAL ); // Create a window for display.
    
    int width, height;
    PAL::Mode mode = PAL::Mode::LASER_SCAN;
    if(PAL::Init(width, height,-1, &mode) != PAL::SUCCESS) //Connect to the PAL camera
    {
        printf("Init failed\n");
        return 1;
    }
    
    usleep(10);
    
    PAL::CameraProperties data; 
    PAL::Acknowledgement ack = PAL::LoadProperties("../Explorer/SavedPalProperties.txt", &data);
	if(ack != PAL::SUCCESS)
	{
	    printf("Error Loading settings\n");
	}
	
    //width and height are the dimensions of each panorama.
    //Panorama is displayed at their original resolution.
    resizeWindow("PAL Laser Scan", 2*width, 2*height);
    
    int key = ' ';
    
    printf("Press ESC to close the window.\n");

	printf("The image resolution is .... %dx%d\n", width, height);
   
    Mat output = cv::Mat::zeros(height, width, CV_8UC3);
    
    //Display the concatenated image
    imshow( "PAL Laser Scan", output);
    
    //27 = esc key. Run the loop until the ESC key is pressed

    while(key != 27)
    {

        PAL::Data::ODOA_Data data;

        data = PAL::GrabLaserScanData();

        cv::Mat output = data.marked_left;
        
        //Display the concatenated image
        imshow( "PAL Laser Scan", output);  
        
        //Wait for the keypress - with a timeout of 1 ms
        key = waitKey(1) & 255;

    }

    printf("exiting the application\n");
    PAL::Destroy();
    
    return 0;
}

