# ifndef POINT_CLOUD_THREAD_H
# define POINT_CLOUD_THREAD_H

# include <vector>
 # include "DataExchange.h"
# include "DataLock.h"
# include "ParallelNode.h" 
# include "PAL_PointCloudManager.h"


class PointCloudThread : public ParallelNode
{ 

    friend class Pipeline;

public:

protected:

    static const int CriticalBuffer_Left = 0;
    static const int CriticalBuffer_Depth = 1;
    static const int CriticalBuffer_Pointcloud = 2;
    static const int CriticalBuffer_TimeStamp = 3;
    static const int CriticalBuffer_Iterations = 4;
    static const int CriticalBuffer_Count = 5;

    PointCloudManager m_oPointCloud;

    void NotifyOutputNodes(void* output) override;

    PAL::Data::PointCloud m_oCurrentData;
    PAL::Data::PointCloud m_oLastConsumedData;

    void CreateCriticalBuffer(int index, int rows, int cols, int type, std::string name); 

    void* WaitForInputNodes() override;

public:

    //TODO: Reset the refiner
    void Reset() override;


    PointCloudThread() { Reset(); } 

    void CreateCriticalBuffers(void* arg) override; 

    void Init(void* arg, std::string name) override;

    bool SavePointCloud(const char* fileName, cv::Mat pcMat);

    void* Iterate(void* input) override;

    // void Run() override;

    PAL::Acknowledgement ChangeInternalState(PAL::CameraProperties *prop, unsigned int* flags) override;

    void* Consume() override;

    ~PointCloudThread();
    
};

# endif //FUSION_THREAD_H
