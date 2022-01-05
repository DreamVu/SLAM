# ifndef DUMMY_PYTHON_THREAD_H
# define DUMMY_PYTHON_THREAD_H

# include <vector>

# include "DataLock.h"
# include "Processor.h"
# include "ParallelNode.h" 
# include "DataExchange.h"  
//# include "PAL_PythonInterface.h"


class DummyDepth : public Processor
{
    PAL::Data::Depth m_oLatestOutput;

public:

    PAL::Acknowledgement Init(void* arg) override; 

    void* Iterate(void* input) override;  

    void Destroy() override;
};

class DummyDetection : public Processor
{
    PAL::Data::People m_oLatestOutput;

public:

    PAL::Acknowledgement Init(void* arg) override; 

    void* Iterate(void* input) override;  

    void Destroy() override;

};

class DummyDE : public Processor
{
    PAL::Data::FloorMask m_oLatestOutput;
    //FastFloor fastfloor;
    int m_iCameraIndex = 0;    
public:

    PAL::Acknowledgement Init(void* arg) override; 

    void* Iterate(void* input) override;  

    void Destroy() override;
    
    PAL::Acknowledgement ReInitFloor(int sets);
    
    void setIndex(int index);
        
}; 


class DummyPythonThread : public ParallelNode
{  
public:
    struct RunFlags
    {
        bool depth;
        bool floor;
        bool people;

        RunFlags() : depth(true), floor(false), people(false){}
    };
    

protected:

    DataLock* m_pPythonInitLock;
    
    DummyDepth m_oDepthManager;
    DummyDE    m_oFloorManager;
    DummyDetection   m_oPeopleManager;

    //This struct is used internally in this class
    struct PythonOutput
    {
        cv::Mat left;
        cv::Mat right;
        cv::Mat refined_left;
        cv::Mat depth;
        cv::Mat floor;
        cv::Mat people;
        timeval timestamp;
        int iterations;
    };

    PythonOutput m_oWriteData;
    PythonOutput m_oReadData;
    

    //This struct is used to exchange data with other classes - depending on which mode is active
    struct ExchangeData
    {
        PAL::Data::Depth depth;
        PAL::Data::FloorMask floor;
        PAL::Data::People people;
    };
    
    ExchangeData m_oExchangeData; 

    PAL::Mode m_eCurrentMode;

    DummyPythonThread::RunFlags m_oFlags;
    
    int g_sets = 5;

    static const int CriticalBuffer_Left = 0;
    static const int CriticalBuffer_Right = 1;
    static const int CriticalBuffer_RefinedLeft = 2;
    static const int CriticalBuffer_Depth = 3;
    static const int CriticalBuffer_Floor = 4;
    static const int CriticalBuffer_People = 5;
    static const int CriticalBuffer_TimeStamp = 6;
    static const int CriticalBuffer_Iterations = 7;
    static const int CriticalBuffer_Count = 8;  

public:
   

    void CreateCriticalBuffers(void* arg) override;  

    void Run() override;

    void Init(void* arg, int index);


    void NotifyOutputNodes(void* output);

    void* Iterate(void* input) override;

    void* Consume() override;

    void Resume(void* arg) override;
    
    void SetPythonInitLock(DataLock* lock);
    
    PAL::Acknowledgement ReInitFloor(int sets);
    
    PAL::Acknowledgement ChangeInternalState(PAL::CameraProperties *prop, unsigned int* flags) override;
    
};

# endif //DUMMY_PYTHON_THREAD_H
