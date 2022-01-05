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

#include <stdio.h>      
#include <sys/socket.h> 
#include <arpa/inet.h>  
#include <stdlib.h>     
#include <string.h>     


using namespace std;
using namespace cv;
using namespace PAL;

static const float Pi = 3.1415926535898f;

struct Timestamp
{
    unsigned long int tv_sec;
    unsigned long int tv_nsec;    
};

struct Header
{
    unsigned short magic;   
    unsigned short num_points_scan;
    float protocol_version;
       
    float min_scan_angle;
    float max_scan_angle;

    Timestamp stamp;
     
    Header ():
    magic (0xA25C),
    protocol_version (3.40),
    num_points_scan (1312),
    min_scan_angle (Pi/6),
    max_scan_angle (2*Pi + Pi/6)
    {
    }
};

struct Packet
{
     Header header;
     unsigned int distance[1312];
};

/*
Specify the absolute file path from which the settings are to be read.

If the specified file can't be opened, default properties from the API are used.
See PAL Documentation for more information.
*/
#define PROPERTIES_FILE_PATH "../catkin_ws/src/dreamvu_pal_navigation/src/SavedPalProperties.txt"
                              

static int camera_index = -1;
int width = -1;
int height = -1;

extern int valid_hfov_widths[5];
extern int valid_angle_widths[5];

bool g_bRosOK = true;

PAL::CameraProperties g_CameraProperties;
filters::FilterChain<sensor_msgs::LaserScan> filter_chain_("sensor_msgs::LaserScan");

PAL::Mini g_oCam;

sensor_msgs::LaserScan FilterLaser(cv::Mat scan_mat, Header header)
{
	sensor_msgs::LaserScan scan;

	scan.header.stamp.sec = header.stamp.tv_sec;
	scan.header.stamp.nsec = header.stamp.tv_nsec;

	scan.header.frame_id = "pal";
	scan.angle_min = Pi / 6 + 2 * Pi * (header.min_scan_angle)/360.0;
	scan.angle_max =  Pi / 6 + 2 * Pi * (header.max_scan_angle)/360.0;
	scan.angle_increment = (scan.angle_max-scan.angle_min) / scan_mat.cols;
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

    return scan;

}

int main(int argc, char **argv)
{
	
	ros::init(argc, argv, "broadcast_scan_node");

	ros::NodeHandle nh;
    filter_chain_.configure("/scan_filter_chain", nh);	

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
        std::cout<<ack_load1<<std::endl;
		ROS_WARN("Not able to load PAL settings from properties file at default location.\n\n"
				 "Please update the file location by setting the Macro: PROPERTIES_FILE_PATH in pal_camera_node.cpp and run catkin_make to build the package again.");
		ROS_INFO("Setting default properties to PAL.");

	}

	ros::Rate loop_rate(30);
	g_bRosOK = ros::ok();
    

    //discarding initial frames
	PAL::Data::ODOA_Data odoa;
	
	for(int i=0; i<10; i++)
	    odoa = g_oCam.GrabLaserScanData();
	
    
    int sock;                         /* Socket */
    struct sockaddr_in broadcastAddr; /* Broadcast address */
    char *broadcastIP;                /* IP broadcast address */
    unsigned short broadcastPort;     /* Server port */
    int broadcastPermission;          /* Socket opt to set permission to broadcast */   

    broadcastIP = "192.168.0.118";         
    broadcastPort = 5000;    


    /* Create socket for sending/receiving datagrams */
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        std::cout<<"socket() failed"<<std::endl;

    /* Set socket to allow broadcast */
    broadcastPermission = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (void *) &broadcastPermission, 
          sizeof(broadcastPermission)) < 0)
        std::cout<<"setsockopt() failed"<<std::endl;

    /* Construct local address structure */
    memset(&broadcastAddr, 0, sizeof(broadcastAddr));   
    broadcastAddr.sin_family = AF_INET;                 
    broadcastAddr.sin_addr.s_addr = inet_addr(broadcastIP); //INADDR_BROADCAST
    broadcastAddr.sin_port = htons(broadcastPort);         

    g_oCam.GetOdoaData(&g_CameraProperties);
    
    int start_angle = g_CameraProperties.odoa_params.odoa_start_hfov; 
    int hfov_range = g_CameraProperties.odoa_params.odoa_hfov_range;
    int start_col = start_angle * 1312 / 360;
    int hfov_width = 192;	

    for(int i=0; i<5; i++)
    {
        if(hfov_range == valid_angle_widths[i])
        {
    	    hfov_width = valid_hfov_widths[i];
    	    break;	        
        }
    }
           
	cv::Rect hfov_crop = Rect(start_col, 0 , hfov_width, 1);
    int size = sizeof(float)*hfov_width + sizeof(Header);
      
    std::cout<<"Starting Broadcast.\n"<<std::endl; 
    
	while (g_bRosOK)
	{
        
        Packet p;

        odoa =  g_oCam.GrabLaserScanData();
        p.header.stamp.tv_sec = odoa.timestamp.tv_sec;
        p.header.stamp.tv_nsec = odoa.timestamp.tv_usec*1000;
        p.header.min_scan_angle = start_angle + 30;
        p.header.max_scan_angle = start_angle + hfov_range + 30;
        p.header.num_points_scan = hfov_width;


        cv::flip(odoa.scan, odoa.scan, 1);
        cv::Mat laser_scan = odoa.scan(hfov_crop).clone();
        cv::flip(laser_scan, laser_scan, 1);        
        cv::flip(odoa.scan, odoa.scan, 1);

        sensor_msgs::LaserScan filtered_scan = FilterLaser(laser_scan, p.header);
            
        for (int i = 0; i < laser_scan.cols; i++)
        {
            p.distance[i] = isnan(filtered_scan.ranges[i]) ? 0xFFFFFFFF: 1000.0*(filtered_scan.ranges[i]);
        }

        if(sendto(sock, &(p.header), size, 0, (struct sockaddr *) 
               &broadcastAddr, sizeof(broadcastAddr)) != size)
             std::cout<<"sendto() sent a different number of bytes than expected"<<std::endl;


		ros::spinOnce();
		loop_rate.sleep();
		g_bRosOK = ros::ok();
	}
	
	g_oCam.Destroy();
}
