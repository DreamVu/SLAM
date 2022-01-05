# ifndef SGBM_THREAD_H
# define SGBM_THREAD_H

# include <vector>
 # include "DataExchange.h"
# include "DataLock.h"
# include "ParallelNode.h" 
# include "DepthManager.h"


class SGBM_Thread : public ParallelNode
{ 

    friend class Pipeline;

public:

protected:

    static const int CriticalBuffer_Left = 0;
    static const int CriticalBuffer_Right = 1; 
    static const int CriticalBuffer_Depth = 2;
    static const int CriticalBuffer_Disparity = 3;

    static const int CriticalBuffer_TimeStamp = 4;
    static const int CriticalBuffer_Iterations = 5;
    static const int CriticalBuffer_Count = 6;

    DataLock* m_pPythonInitLock;
    
    DepthManager m_oStereoDepth;

    void NotifyOutputNodes(void* output) override;

    PAL::Data::StereoDepthData m_oCurrentData;
    PAL::Data::StereoDepthData m_oLastConsumedData;
    cv::Mat m_oValidDepthData;
    
    void CreateCriticalBuffer(int index, int rows, int cols, int type, std::string name); 

    void* WaitForInputNodes() override;

public:

    //TODO: Reset the refiner
    void Reset() override;


    SGBM_Thread() { Reset(); } 

    void CreateCriticalBuffers(void* arg) override; 

    void Init(void* arg, std::string name) override;

    void* Iterate(void* input) override;

    void Run() override;

    PAL::Acknowledgement ChangeInternalState(PAL::CameraProperties *prop, unsigned int* flags) override;

    void* Consume() override;

    cv::Mat GetLatestDepth() { return m_oCurrentData.depth; }

    void Update(cv::Mat left, cv::Mat right);// { std::memcy(m_oCurrentData.left.dataleft; m_oCurrentData.right = right; }

    void SetPythonInitLock(DataLock* lock);
    
    ~SGBM_Thread();
    
};

# endif //SGBM_THREAD_H
