# ifndef FUSION_THREAD_H
# define FUSION_THREAD_H

# include <vector>
 # include "DataExchange.h"
# include "DataLock.h"
# include "ParallelNode.h" 
# include "PAL_PC_Fusion.h"

class FusionThread : public ParallelNode
{ 

    friend class Pipeline;

public:

protected:

    static const int CriticalBuffer_Left = 0;
    static const int CriticalBuffer_Depth = 1;
    static const int CriticalBuffer_Focalmap = 2;
    static const int CriticalBuffer_TimeStamp = 3;
    static const int CriticalBuffer_Iterations = 4;
    static const int CriticalBuffer_Count = 5;

    PAL_PC_Fusion m_oFusion;

    void NotifyOutputNodes(void* output) override;

    PAL::Data::FloorFocalMap m_oCurrentData;
    PAL::Data::FloorFocalMap m_oLastConsumedData;

    void CreateCriticalBuffer(int index, int rows, int cols, int type, std::string name); 

    void* WaitForInputNodes() override;

public:

    //TODO: Reset the refiner
    void Reset() override;


    FusionThread() { Reset(); } 

    void CreateCriticalBuffers(void* arg) override; 

    void Init(void* arg, std::string name) override;

    // void Run() override;

    void* Iterate(void* input) override;

    PAL::Acknowledgement ChangeInternalState(PAL::CameraProperties *prop, unsigned int* flags) override;

    void* Consume() override;

    ~FusionThread();
    
};

# endif //FUSION_THREAD_H
