#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <sensor_msgs/LaserScan.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sstream>
#include <signal.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <boost/make_shared.hpp>
#include <sys/time.h>

#include <iomanip>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <math.h>

#include "opencv2/core.hpp"
#include <opencv2/core/utility.hpp>
#include "opencv2/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

#include "PAL.h"
#include "filters/filter_chain.h"


using namespace std;
using namespace cv;
using namespace PAL;

static const float Pi = 3.1415926535898f;

/*
Specify the absolute file path from which the settings are to be read.

If the specified file can't be opened, default properties from the API are used.
See PAL Documentation for more information.
*/
#define PROPERTIES_FILE_PATH "../catkin_ws/src/dreamvu_pal_navigation/src/SavedPalProperties.txt"
                              

static int camera_index = -1;
int width = -1;
int height = -1;

bool g_bRosOK = true;

PAL::CameraProperties g_CameraProperties;

image_transport::Publisher leftpub1;
ros::Publisher laserPub1;
filters::FilterChain<sensor_msgs::LaserScan> filter_chain_("sensor_msgs::LaserScan");

void publishLaser(cv::Mat scan_mat, ros::Publisher laserPub, timeval timestamp)
{
	
	sensor_msgs::LaserScan scan, scan1;
    //scan.header.stamp = timestamp;
	scan.header.stamp.sec = timestamp.tv_sec;
	scan.header.stamp.nsec = timestamp.tv_usec*1000;

	scan.header.frame_id = "pal";
	scan.angle_min = Pi / 6;
	scan.angle_max = 2 * Pi + scan.angle_min;
	scan.angle_increment = 6.28 / scan_mat.cols;
	scan.range_min = 0.0;
	scan.range_max = 50.0;
	scan.ranges.resize(scan_mat.cols);
	scan.intensities.resize(scan_mat.cols);

	float* pscan = (float*) scan_mat.data;

	for (int i = 0; i < scan_mat.cols; i++)
	{
	    scan.ranges[i] = *(pscan+i);
	    scan.intensities[i] = 0.5;	
	}

    filter_chain_.update(scan, scan);
	laserPub.publish(scan);

}

void publishimage(cv::Mat imgmat, image_transport::Publisher &pub, string encoding, timeval timestamp)
{
	int type;
	if (encoding == "mono8")
		type = CV_8UC1;
	else if (encoding == "mono16")
		type = CV_16SC1;
	else
		type = CV_8UC3;

    std_msgs::Header header;
    header.stamp.sec = timestamp.tv_sec;
    header.stamp.nsec = timestamp.tv_usec*1000;
    sensor_msgs::ImagePtr imgmsg = cv_bridge::CvImage(header, encoding, imgmat).toImageMsg();

	pub.publish(imgmsg);
}

PAL::Mini g_oCam;

int main(int argc, char **argv)
{
	
	ros::init(argc, argv, "depth_scan_node");

	ros::NodeHandle nh;
	image_transport::ImageTransport it(nh);
    filter_chain_.configure("/scan_filter_chain", nh);
	//Creating all the publishers
	leftpub1 = it.advertise("/dreamvu/pal/odoa/get/left", 1);		
	laserPub1 = nh.advertise<sensor_msgs::LaserScan>("/dreamvu/pal/odoa/get/scan", 1);  



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
		printf("Init failed\n");
		return 1;
	}


	//Loading properties from the file
	PAL::Acknowledgement ack_load1 = g_oCam.LoadProperties(PROPERTIES_FILE_PATH, &g_CameraProperties);

	
	if (ack_load1 != PAL::SUCCESS)
	{

		ROS_WARN("Not able to load PAL settings from properties file at default location.\n\n"
				 "Please update the file location by setting the Macro: PROPERTIES_FILE_PATH in pal_camera_node.cpp and run catkin_make to build the package again.");
		ROS_INFO("Setting default properties to PAL.");

	}


	ros::Rate loop_rate(30);
	g_bRosOK = ros::ok();
    

    for(int i=0; i<10; i++)
    {
            PAL::Data::ODOA_Data discard;
            discard = g_oCam.GrabLaserScanData();
    }
    
	while (g_bRosOK)
	{

		//Getting no of subscribers for each publisher
		int left1Subnumber = leftpub1.getNumSubscribers();
		int laserscan1Subnumber = laserPub1.getNumSubscribers();
		int subnumber = left1Subnumber + laserscan1Subnumber;
		
        bool overlaid1 = false;
        PAL::Data::ODOA_Data data1;
        
		if (subnumber > 0)
		{
			ros::WallTime t1 = ros::WallTime::now();
			overlaid1 = (left1Subnumber && laserscan1Subnumber);       

            data1 = g_oCam.GrabLaserScanData();
                       
			ros::WallTime t2 = ros::WallTime::now();						
			//ROS_INFO_STREAM("Grab time (ms): " << (t2 - t1).toNSec()*1e-6);					
		}

		if (left1Subnumber > 0)
		{
            publishimage(overlaid1 ? data1.marked_left  : data1.left, leftpub1, "bgr8", data1.timestamp);
        }
        
		if (laserscan1Subnumber > 0)
		{
			publishLaser(data1.scan, laserPub1, data1.timestamp);
		}

		ros::spinOnce();
		loop_rate.sleep();
		g_bRosOK = ros::ok();
	}
	
	g_oCam.Destroy();
}
