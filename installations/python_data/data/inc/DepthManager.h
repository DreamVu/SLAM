# ifndef DEPTH_MANAGER_H
# define DEPTH_MANAGER_H
# include <stdio.h>
# include <opencv2/opencv.hpp>

#include "CameraProperties.h"
# include "SGBM_Processor.h"
#include "Processor.h"
 

class DepthManager: public Processor
{
    SGBM_Processor m_oSGBM;
    Processor* m_pProcessor;
    
    PAL::Resolution m_oInitArguments;

protected:
    PAL::Data::StereoDepthData m_oCurrentOutput;
public:

    DepthManager();

    virtual PAL::Acknowledgement Init(void* arg);

    virtual PAL::Acknowledgement ChangeInternalState(PAL::CameraProperties* props, unsigned int *flags) override;

    void* Iterate(void* input) override;

    PAL::Data::StereoDepthData Process(PAL::Data::Stereo input);

    virtual void Destroy();

    virtual ~DepthManager(){}

};
# endif //DEPTH_MANAGER_H
