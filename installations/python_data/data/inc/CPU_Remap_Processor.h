# ifndef CPU_REMAP_PROCESSOR_H
# define CPU_REMAP_PROCESSOR_H

# include "RemapProcessor.h"

class CPU_Remap_Processor : public RemapProcessor
{

    int active_image;

public:
    PAL::CameraProperties prop;
    int res[5] = {3120, 2088, 2088, 2088, 2088};
    std::vector<cv::Mat> original_luts;
    std::vector<cv::Mat> equirect_luts;
    cv:: Mat lut;
    cv::Mat buffer_rgb;

    void Init(int max_cols, int max_rows, std::vector<cv::Mat> lutfiles, std::vector<cv::Mat> er_files);

    void ChangeInternalState(PAL::CameraProperties* props);

    void ComputeRemap(cv::Mat input, cv::Mat* output);
    
    void SetCurrentResolution(int active_image_input);

    void SetCameraMode(PAL::CameraProperties prop);

    void HandleCameraChanges(PAL:: CameraProperties prop);

    cv::Mat CropLUT(cv::Mat lut, PAL::CameraProperties prop);
    
    void HandleFlip(bool flip);

    void Synchronize();

    void Destroy();
    
};
# endif //CPU_REMAP_PROCESSOR_H
