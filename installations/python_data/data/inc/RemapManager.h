# ifndef REAMP_MANAGER_H
# define REAMP_MANAGER_H

# include <stdio.h>
# include <opencv2/opencv.hpp>

#include "CameraProperties.h"
#include "RemapProcessor.h"
# include "CPU_Remap_Processor.h"

 

class RemapManager
{
    CPU_Remap_Processor m_oCPU_Remap_Live;
    CPU_Remap_Processor m_oCPU_Remap_Dummy;
    //Remap-2_Processor m_oRemap-2;          // Add diffrent remaps method
    RemapProcessor* m_pProcessor;
    
    PAL::Resolution m_oInitArguments;

    PAL::CaptureType capture_mode;
    
    const char* file;

public:

    RemapManager();

    void InitLive(int max_cols, int max_rows, std::vector<cv::Mat> lutfiles, std::vector<cv::Mat> er_files);
    void InitDummy(int max_cols, int max_rows, std::vector<cv::Mat> lutfiles, std::vector<cv::Mat> er_files);

    void ChangeInternalState(PAL::CameraProperties* props);

    void ChangeImplementation(PAL::CameraProperties* props);

    void ComputeRemap(cv::Mat input, cv::Mat* output);
    
    void SetCurrentResolution(int active_image_input);

    void SetCameraMode(PAL::CameraProperties prop);

    void HandleFlip(bool flip);

    void Synchronize();

    void Destroy();

    ~RemapManager(){}

};
# endif //REAMP_MANAGER_H
