# ifndef CPU_REMAP_PROCESSOR_H
# define CPU_REMAP_PROCESSOR_H

# include "RemapProcessor.h"

class CPU_Remap_Processor : public RemapProcessor
{

    int active_image;
    PAL::CameraProperties prop;
    int res[4] = {3120, 2088, 1560, 780};
    std::vector<cv::Mat> original_luts;
    cv::Mat lut, output;
    cv::Mat buffer_rgb;

public:

    cv::Mat output2;

    void Init(int max_cols, int max_rows, std::vector<cv::Mat> lutfiles);

    void ChangeInternalState(PAL::CameraProperties* props);

    void ComputeRemap(cv::Mat input, cv::Mat* output);
    
    void SetCurrentResolution(int active_image_input);

    void SetCameraMode(PAL::CameraProperties prop);

    void HandleCameraChanges(PAL:: CameraProperties prop);

    cv::Mat CropLUT(cv::Mat lut, PAL::CameraProperties prop);
    
    void ReAdjust();

    // void HandleFlip(bool flip);

    void Synchronize();

    void Destroy();
    
};
# endif //CPU_REMAP_PROCESSOR_H
