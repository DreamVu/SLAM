# ifndef FUSION_MANAGER_H
# define FUSION_MANAGER_H

# include <stdio.h>
# include <opencv2/opencv.hpp>

#include "CameraProperties.h"
#include "Processor.h"
# include "ODOA_Fusion.h"

 

class FusionManager : Processor
{
    ODOA_Fusion m_oFusion;
    
    Processor* m_pProcessor;
    
    PAL::Resolution m_oInitArguments;
    PAL::Data::ODOA_Data m_oCurrentOutput;
     

public:

    FusionManager();

    virtual PAL::Acknowledgement Init(void* arg) override;

    virtual PAL::Acknowledgement ChangeInternalState(PAL::CameraProperties* props, unsigned int *flags) override;

    void* Iterate(void* input) override;
    
    virtual PAL::Acknowledgement GetOdoaData(PAL::CameraProperties* data) ;
    
    PAL::Data::ODOA_Data Process(PAL::Data::ODOA_Data input);


    virtual void Destroy();

    virtual ~FusionManager(){}

};
# endif //FUSION_MANAGER_H
