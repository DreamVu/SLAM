# ifndef SGBM_DEPTH_PROCESSOR_H
# define SGBM_DEPTH_PROCESSOR_H
# include "DataExchange.h"
# include "Processor.h"
# include "CameraProperties.h"

class SGBM_Processor : public Processor
{
    PAL:: Resolution current_resolution, highest_resolution;

public:

     struct InitData
    {
        PAL:: Resolution highest_res;
    };



protected:

    PAL::Data::StereoDepthData m_matCurrentOutput;
    InitData m_oParams;

public:

    PAL::Acknowledgement Init(void* arg);

    PAL::Acknowledgement ChangeInternalState(PAL::CameraProperties* props, unsigned int *flags) override;

    void* Iterate(void* input) override;

PAL::Data::StereoDepthData Process(PAL::Data::Stereo input);
    cv::Mat ComputeDisparity(cv::Mat left, cv::Mat right);

    void ComputeDepth(cv::Mat left, cv::Mat right, cv::Mat *depth);

    void ComputeDepthHelper(cv::Mat input, cv::Mat *depth);

    void ComputeDepthFromDisparity(cv::Mat inDisparity, cv::Mat *outDepth);

    void ComputeDisparityFromDepth(cv::Mat inDepth, cv::Mat outDisparity);

    cv::Mat nonLinearCorrection(cv::Mat image, int flag);

    void SetSensorResolution(PAL:: CameraProperties prop);

    PAL:: Resolution GetSensorResolution();

    void Synchronize();

    void Destroy();
    
};
# endif //DEPTH_PROCESSOR_H
