# ifndef PANORAMA_THREAD_H
# define PANORAMA_THREAD_H

# include <vector>

# include "DataLock.h"
# include "ParallelNode.h" 
# include "DataExchange.h"
# include "PanoramaManager.h"
# include "SGBM_Thread.h"

class PanoramaThread : public ParallelNode
{ 


    friend class Pipeline;
public: 

    // struct Data
    // {
    //     cv::Mat left;
    //     cv::Mat right;
    //     int     timestamp;
    //     int     iterations;
    // };

protected:

    static const int CriticalBuffer_Left = 0;
    static const int CriticalBuffer_Right = 1;
    static const int CriticalBuffer_RefinedLeft = 2;
    static const int CriticalBuffer_TimeStamp = 3;
    static const int CriticalBuffer_Iterations = 4;
    static const int CriticalBuffer_Count = 5;

    void* WaitForInputNodes() override;

    void NotifyOutputNodes(void* output) override;

    // Data m_oCurrentData;
    // Data m_oLastConsumedData;
    PAL::Data::Stereo m_oCurrentData;
    PAL::Data::Stereo m_oLastConsumedData;

    SGBM_Thread *m_pSGBM;

    PanoramaManager m_oPanorama;

    void CreateCriticalBuffer(int index, int rows, int cols, int type, std::string name); 

public:

    void Reset() override;

    PanoramaThread() { Reset(); } 

    void CreateCriticalBuffers(void* arg) override; 

    void Run() override;

    void Init(void* arg, std::string name) override;

    PAL::Acknowledgement InitPanorama();

    void* Iterate(void* input) override;

    PAL::Acknowledgement ChangeInternalState(PAL::CameraProperties *prop, unsigned int* flags) override;

    void* Consume() override;

    void SetSGBM(SGBM_Thread* sgbm) { m_pSGBM = sgbm; }

    PAL::Acknowledgement GetData(PAL::CameraProperties* data);

    ~PanoramaThread();
    
};

# endif //PANORAMA_THREAD_H
