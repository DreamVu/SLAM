# ifndef ODOA_FUSION_THREAD_H
# define ODOA_FUSION_THREAD_H

# include <vector>
 # include "DataExchange.h"
# include "DataLock.h"
# include "ParallelNode.h" 
# include "FusionManager.h"
# include "SGBM_Thread.h"


class ODOA_FusionThread : public ParallelNode
{ 

    friend class Pipeline;

public:

protected:

    static const int CriticalBuffer_Left = 0;
    static const int CriticalBuffer_Depth = 1;
    static const int CriticalBuffer_De_out = 2;
    static const int CriticalBuffer_Scan = 3;
    static const int CriticalBuffer_Marked_Left = 4;
    static const int CriticalBuffer_TimeStamp = 5;
    static const int CriticalBuffer_Iterations = 6;
    static const int CriticalBuffer_Count = 7;
    static const int CriticalBuffer_Right = 0;

    FusionManager m_oFusion;

    SGBM_Thread *m_pSGBM;

    void NotifyOutputNodes(void* output) override;

    PAL::Data::ODOA_Data m_oCurrentData;
    PAL::Data::ODOA_Data m_oLastConsumedData;

    void CreateCriticalBuffer(int index, int rows, int cols, int type, std::string name); 

    void* WaitForInputNodes() override;

public:

    //TODO: Reset the refiner
    void Reset() override;


    ODOA_FusionThread() { Reset(); } 

    void CreateCriticalBuffers(void* arg) override; 

    void Init(void* arg, std::string name) override;

    void* Iterate(void* input) override;

    PAL::Acknowledgement ChangeInternalState(PAL::CameraProperties *prop, unsigned int* flags) override;

    PAL::Acknowledgement GetOdoaData(PAL::CameraProperties* data) ;
    
    void* Consume() override;

    void SetSGBM(SGBM_Thread* sgbm) { m_pSGBM = sgbm; }

    ~ODOA_FusionThread();
    
};

# endif //ODOA_FUSION_THREAD_H
