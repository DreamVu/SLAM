# ifndef PANORAMA_MANAGER_H
# define PANORAMA_MANAGER_H

# include <stdio.h>
# include <sys/time.h>
# include <opencv2/opencv.hpp>

# include "Processor.h"
# include "DataExchange.h"
# include "RemapManager.h"
# include "CameraManager.h" 

class PanoramaManager : public Processor
{


    std::vector<cv::Mat> dummy_cfm_files;
	std::vector<cv::Mat> dummy_lut_files;
    std::vector<cv::Mat> live_lut_files;
    std::vector<cv::Mat> er_files;

public: 

    struct InitData
    {
        int width;
        int height;
        int camera_index;
    };

    enum class Mode
    {
        DUMMY_MODE,
        LIVE_CAMERA_MODE
    };

    PAL::Data::Stereo m_oLatestOutput;
    
protected: 
    
    RemapManager m_oRemap;
    
    CameraManager m_oCamera;   

    Mode m_eCurrentMode = Mode::LIVE_CAMERA_MODE;

public:

    PanoramaManager();
    
    PAL::Acknowledgement Init(void* arg) override;
    
    PAL::Acknowledgement ChangeImplementation(void* arg);

    PAL::Acknowledgement ChangeInternalState(PAL::CameraProperties* props, unsigned int *flags)  override;

    void* Iterate(void* input) override;

    PAL::Data::Stereo Process(); 

    void Destroy();

    void InstantSetGain(cv::Mat leftmat);

    PAL::Acknowledgement GetData(PAL::CameraProperties* data);

    ~PanoramaManager() { Destroy(); }

};

# endif //PANORAMA_MANAGER_H
