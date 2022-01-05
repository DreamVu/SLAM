# ifndef REFINEMENT_THREAD_H
# define REFINEMENT_THREAD_H

# include <vector>
 # include "DataExchange.h"
# include "DataLock.h"
# include "ParallelNode.h" 
# include "RefinementProcessor.h"


class RefinementThread : public ParallelNode
{ 

    friend class Pipeline;

public:

protected:

    static const int CriticalBuffer_Left = 0;
    static const int CriticalBuffer_Right = 1;
    static const int CriticalBuffer_RefinedLeft = 2;
    static const int CriticalBuffer_TimeStamp = 3;
    static const int CriticalBuffer_Iterations = 4;
    static const int CriticalBuffer_Count = 5;

    RefinementProcessor m_oRefinement;

    void NotifyOutputNodes(void* output) override;

    PAL::Data::Stereo m_oCurrentData;
    PAL::Data::Stereo m_oLastConsumedData;

    void CreateCriticalBuffer(int index, int rows, int cols, int type, std::string name); 

    void* WaitForInputNodes() override;

public:

    //TODO: Reset the refiner
    void Reset() override;


    RefinementThread() { Reset(); } 

    void CreateCriticalBuffers(void* arg) override; 

    // void Run() override;

    void Init(void* arg, std::string name) override;

    void* Iterate(void* input) override;

    PAL::Acknowledgement ChangeInternalState(PAL::CameraProperties *prop, unsigned int* flags) override;

    void* Consume() override;

    ~RefinementThread();
    
};

# endif //REFINEMENT_THREAD_H
