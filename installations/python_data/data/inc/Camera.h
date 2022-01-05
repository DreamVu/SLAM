# ifndef CAMERA_H
# define CAMERA_H

# include <stdio.h>
# include <opencv2/opencv.hpp>

# include "CameraProperties.h"


# define FUNC() //printf("INSIDE %s --> %d : %s\n\n", __FILE__, __LINE__, __func__)

class Camera
{

protected:
    
    PAL::CameraProperties current_properties;
	PAL::Resolution current_sensor;

public:

    virtual int Init(int max_cols, int max_rows);

    virtual void ChangeInternalState(PAL::CameraProperties* props, unsigned int& flags);

    virtual int GrabFrame(cv::Mat* cfm_frame, timeval& timestamp);

    virtual int GetCurrentResolution();
  
    virtual void Synchronize();

    virtual void Destroy();
    
    virtual void SetSensorProperty(int id, int value);

    virtual PAL::Acknowledgement SetData(PAL::CameraProperties *data, unsigned int& flags);

    virtual PAL::Acknowledgement GetData(PAL::CameraProperties *data);

    virtual ~Camera(){}

};
# endif //CAMERA_H
