# ifndef PERSON_DETECTION_MANAGER_H
# define PERSON_DETECTION_MANAGER_H
# include <stdio.h>

# include "PAL_PersonDetection.h"
# include "DataExchange.h"
# include "CameraProperties.h"
#include "Processor.h"
 

class PersonDetectionManager: public Processor
{
    PAL_PersonDetection m_oPD;
    Processor *m_pProcessor, *m_pDepthProcessor;

protected:
    PAL::Data::People m_oCurrentOutput;

public:

    PersonDetectionManager();

    PAL::Acknowledgement Init(void* arg) override;

    PAL::Acknowledgement ChangeImplementation(void* arg) override;

    PAL::Acknowledgement ChangeInternalState(PAL::CameraProperties* props, unsigned int *flags) override;

    void* Iterate(void* input) override;

    PAL::Data::People Process(PAL::Data::Stereo); 

    void Destroy() override;

    void SetDepthProcessor(Processor* processor) { m_pDepthProcessor = processor; }

    virtual ~PersonDetectionManager(){}

};
# endif //PERSON_DETECTION_MANAGER_H