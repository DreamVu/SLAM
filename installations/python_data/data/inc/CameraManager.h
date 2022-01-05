# ifndef CAMERA_MANAGER_H
# define CAMERA_MANAGER_H

# include <stdio.h>
# include <opencv2/opencv.hpp>

#include "CameraProperties.h"
#include "Camera.h"
# include "OpencvCamera.h"
# include "DummyCamera.h"
 

class CameraManager
{
    OpencvCamera m_oCAMERA;
    DummyCamera m_oDUMMY;
    Camera* m_pProcessor;
    PAL::Resolution m_oInitArguments;

public:

    CameraManager();

    virtual int InitRGB(int width, int height, int CameraIndex);
    
    virtual int InitDummy(int width, int height, std::vector<cv::Mat> cfm_images);

    virtual void ChangeImplementation(PAL::CameraProperties* props);

    virtual void ChangeInternalState(PAL::CameraProperties* props, unsigned int& flags);

    virtual int GrabFrame(cv::Mat* cfm_frame, timeval& timestamp);

    virtual void SetSensorResolution(PAL::Resolution sensor);

    virtual int GetCurrentResolution();
    
    virtual void Synchronize();
    
    virtual void SetSensorProperty(int id, int value);

    virtual PAL::Acknowledgement GetData(PAL::CameraProperties* data);

    virtual PAL::Acknowledgement SetData(PAL::CameraProperties *data, unsigned int& flags);
    
    virtual void Destroy();

    virtual ~CameraManager(){}

};
# endif //CAMERA_MANAGER_H
