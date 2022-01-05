# ifndef REMAP_PROCESSOR_H
# define REMAP_PROCESSOR_H

# include <stdio.h>
# include <opencv2/opencv.hpp>

# include "CameraProperties.h"


# define FUNC() printf("INSIDE %s --> %d : %s\n\n", __FILE__, __LINE__, __func__)

class RemapProcessor
{

public:

    virtual void Init(int max_cols, int max_rows, std::vector<cv::Mat> lutfiles);

    virtual void ChangeInternalState(PAL::CameraProperties* props);

    virtual void ComputeRemap(cv::Mat input, cv::Mat* output);
    
    virtual void SetCurrentResolution(int active_image_input);

    virtual void SetCameraMode(PAL::CameraProperties prop);

    virtual void HandleFlip(bool flip);

    virtual void Synchronize();

    virtual void Destroy();

    virtual ~RemapProcessor(){}

};
# endif //DEPTH_PROCESSOR_H
