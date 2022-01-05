# ifndef CRITICAL_BUFFER_H
# define CRITICAL_BUFFER_H


# include <string>
# include <opencv2/opencv.hpp>

# include "DataLock.h"
# include "Semaphore.h"


 struct CriticalSlot
 {
    Semaphore semaphore;
    DataLock lock;
    cv::Mat  buffer; 
    cv::Mat  valid_data;

    bool active;

    CriticalSlot() : active(true) {}

    void Write(cv::Mat m);

    const cv::Mat& Read();
    
    void Exit();

    const cv::Mat& Access();

    void Deactivate();

    void Activate();

 };


struct CriticalBuffer
{


    CriticalSlot critical_slots[1];

    int read_count;
    int write_count;
    static const int SLOTS_SIZE = 1;
    std::string NAME;

    void Init(int rows, int cols, int type, std::string name);

    CriticalBuffer();

    CriticalBuffer(int rows, int cols, int type, std::string name);


    void Produce(cv::Mat mat);

    const cv::Mat& Consume();

    void Consume(cv::Mat& target);

    const cv::Mat& Access();

    void Exit();

    void Deactivate();

    void Activate();

    ~CriticalBuffer();

};

# endif //CRITICAL_BUFFER_H
