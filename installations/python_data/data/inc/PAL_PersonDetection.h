# ifndef PersonDetection_H
# define PersonDetection_H

# include <opencv2/opencv.hpp>
# include "PAL_PythonInterface.h"
# include "Processor.h"
# include "DataExchange.h"

class PAL_PersonDetection : public Processor
{
    struct CircularBuffer
    {
        int read_index;
        int write_index;
        std::vector<cv::Mat> mats;

        void Init(int rows, int cols, int type, int size)
        {
            read_index = 0;
            write_index = 0;
            mats.resize(size);
            for(int i = 0; i < size; i++)
            {
                mats[i] = cv::Mat::zeros(rows, cols, type);
            }
        }

        CircularBuffer(int rows, int cols, int type, int size)
        {
            Init(rows, cols, type, size);	
        }

        CircularBuffer()
        {
            //TODO: Replace these numbers with Macros/const
            Init(1016, 3440, CV_8UC3, 4);
        }

        void Write(cv::Mat m)
        {
            int index = write_index % mats.size();
            write_index++;
            memcpy(mats[index].data, m.data, m.rows*m.step);
        }


        cv::Mat Read()
        {
            int index = read_index % mats.size();
            read_index++;
            return mats[index].clone();
        }

    };

    PAL_SSD m_pySsd;

    CircularBuffer cb_refined_lefts;

    void WriteRefinedLeftPanorama(cv::Mat left);

    cv::Mat ReadRefinedLeftPanorama();


public:

     struct InitData
    {
        float threshold;
    };

protected:

    InitData m_oParams;
    PAL::Data::People m_oLatestOutput;

public:
    
    std::vector<PAL::BoundingBox> GetPeopleDetection(cv::Mat leftmat);

    PAL::Acknowledgement Init(void* arg) override;

    PAL::Acknowledgement ChangeInternalState(PAL::CameraProperties* props, unsigned int *flags) override;

    void* Iterate(void* input) override;
    
    PAL::Data::People Process(PAL::Data::Stereo);

    void Destroy();

};

# endif //PersonDetection_H
