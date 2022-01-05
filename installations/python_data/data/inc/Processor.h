# ifndef PROCESSOR_H
# define PROCESSOR_H

# include <stdio.h>
# include <opencv2/opencv.hpp>

# include "CameraProperties.h" 
# include "PAL_Log.h"

void Info(const char* module, int iteration, cv::Mat m);

class Processor
{
protected:
    PAL::CameraProperties m_oProperties;

public:

    virtual PAL::Acknowledgement Init(void* arg) { return PAL::Acknowledgement::FAILURE; }

    virtual PAL::Acknowledgement ChangeImplementation(void* arg) { return PAL::Acknowledgement::IGNORED; }

    virtual PAL::Acknowledgement ChangeInternalState(PAL::CameraProperties* props, unsigned int *flags) { return PAL::Acknowledgement::IGNORED; }
    
    virtual PAL::Acknowledgement GetOdoaData(PAL::CameraProperties* data) {return PAL::Acknowledgement::IGNORED; }

    virtual void* Iterate(void* input) = 0;  

    virtual void Destroy(){}

    virtual ~Processor(){ Destroy(); }

};

# endif //PROCESSOR_H
