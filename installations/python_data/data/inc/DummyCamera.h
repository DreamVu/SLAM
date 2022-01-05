# ifndef DUMMY_CAMERA_H
# define DUMMY_CAMERA_H

# include "Camera.h"

class DummyCamera : public Camera
{
    PAL::CaptureType capture_type;
    std::vector<cv::Mat> raw_images;
    int active_image;
    
    PAL::Resolution current_sensor;

public:

    int Init(int width, int height, std::vector<cv::Mat> cfm_images);

    void ChangeInternalState(PAL::CameraProperties* props);

    int GrabFrame(cv::Mat* cfm_frame);
    
    void SetSensorResolution(PAL::Resolution sensor);
    
    int GetCurrentResolution();
    
    void Synchronize();

    void Destroy();
    
};
# endif //DUMMY_CAMERA_H
