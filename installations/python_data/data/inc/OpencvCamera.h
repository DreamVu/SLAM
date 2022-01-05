# ifndef OPENCVCAMERA_H
# define OPENCVCAMERA_H

# include "Camera.h"
# include "Semaphore.h"
# include <libudev.h>
#include <linux/hidraw.h>
#include "/usr/include/libusb-1.0/libusb.h"

#include <libudev.h>

#include <SDL/SDL.h>
#include <SDL/SDL_keysym.h>
#include <errno.h>
#include <sys/types.h>	
#include <sys/stat.h>	
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <asm/types.h>
#include <sys/mman.h>
#include <string.h>
#include <malloc.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>
#include <getopt.h>
#include <dirent.h>
#include <signal.h>

#include <linux/videodev2.h>
#include <linux/fb.h>
#include <linux/media.h>
#include <linux/v4l2-subdev.h>

#define CAMERA_CONTROL_CU135 0x81
#define SET_FRAME_RATE_CU135 0x1C
#define BUFFER_LENGTH 65
#define SET_FAIL 0x00
#define SET_SUCCESS 0x01
#define GET_FAIL		0x00
#define GET_SUCCESS		0x01
#define GET_FRAME_RATE_CU135 0x1B

class OpencvCamera : public Camera
{


    cv::Mat raw_image;
    cv::VideoCapture cap;
    PAL::CaptureType capture_type;
    int res[5] = {3120, 2088, 2088, 2088, 2088};
    
    int active_image;
    int hid_fd;
    char hid_device[20];    
    Semaphore m_oSemaphore;
    unsigned char g_out_packet_buf[BUFFER_LENGTH];
    unsigned char g_in_packet_buf[BUFFER_LENGTH];
    
public:

    int Init(int Width, int Height, int CameraIndex);

    void ChangeInternalState(PAL::CameraProperties* props, unsigned int& flags);

    int GrabFrame(cv::Mat* cfm_frame, timeval& timestamp);
    
    void SetSensorResolution(PAL::Resolution sensor);
    
    int GetCurrentResolution();
    
    void Synchronize();
    
    void SetSensorProperty(int id, int value) override;
    
    // PAL::Acknowledgement SetData(PAL::CameraProperties *data, unsigned int& flags);

    // PAL::Acknowledgement GetData(PAL::CameraProperties *data);
    void initializeBuffers();
    int initextensionunit(int index);
    bool sendHidCmd(unsigned char *outBuf, unsigned char *inBuf, int len);   
    bool setFrameRateCtrlValue(uint frameRate);
    bool getFrameRateCtrlValue(int& fps);     
    void Destroy();
    
};
# endif //OPENCVCAMERA_H
