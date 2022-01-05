# ifndef REFINEMENT_PROCESSOR_H
# define REFINEMENT_PROCESSOR_H

# include <stdio.h>
# include <sys/time.h>
# include <opencv2/opencv.hpp>

# include "Processor.h" 
# include "DataExchange.h"

#if 0
struct Normalizer
{
    float mean_r, mean_g, mean_b;
    float std_x, std_y, std_z;

    cv::Mat out;

    Normalizer()
    {
        float scale = 255.0f;

# if 1
        mean_r = 0.485f*scale;
        mean_g = 0.456f*scale;
        mean_b = 0.406f*scale;

        std_x = 0.229f*scale;
        std_y = 0.224f*scale;
        std_z = 0.225f*scale;
# else
        mean_r = mean_g = mean_b = 0.0f;
        std_x = std_y = std_z = scale;
# endif 

    }


    cv::Mat Process(cv::Mat input)
    {
        if(out.cols != input.cols || out.rows != input.rows)
        {
            out = cv::Mat::zeros(input.rows*3, input.cols, CV_32FC1);
        }

        int jump = out.step*out.rows/3;
        unsigned char* src = input.data;
        float* dst1 = (float*)out.data;
        float* dst2 = (float*)(out.data + jump);
        float* dst3 = (float*)(out.data + jump*2);
        
        for(int i = 0; i < input.rows; i++)
        {
            unsigned char* src = input.data + i*input.step;
            float* dst = (float*)(out.data + i*out.step);
            for(int j = 0; j < input.cols; j++)
            {
# if 0
                float x = *src++;
                float y = *src++;
                float z = *src++;
# else

                float z = *src++;
                float y = *src++;
                float x = *src++;
# endif

                *dst1++ = (x - mean_r)/std_x;
                *dst2++ = (y - mean_g)/std_y;
                *dst3++ = (z - mean_b)/std_z;

            }
        }
        return out;
    }

};

#else
struct Normalizer
{
    float mean_r, mean_g, mean_b;
    float std_r, std_g, std_b;
    cv::Mat out;
    Normalizer()
    {
        float scale = 255.0f;
        mean_r = 0.485f*scale;
        mean_g = 0.456f*scale;
        mean_b = 0.406f*scale;
        std_r = 0.229f*scale;
        std_g = 0.224f*scale;
        std_b = 0.225f*scale;
    }
    cv::Mat Process(cv::Mat input)
    {
        if(out.cols != input.cols || out.rows != input.rows)
        {
            out = cv::Mat::zeros(input.rows, input.cols, CV_32FC3);
        }
        int jump = out.step*out.rows/3;
        //unsigned char* src = input.data;
        float* dst1 = (float*)out.data;
        float* dst2 = (float*)(out.data + jump);
        float* dst3 = (float*)(out.data + jump*2);
        for(int i = 0; i < out.rows; i++)
        {
            unsigned char* src = input.data + i*input.step;
            //float* dst = (float*)(out.data + i*out.step);
            for(int j = 0; j < out.cols; j++)
            {
                float b = *src++;
                float g = *src++;
                float r = *src++;
                *dst1++ = (r - mean_r)/std_r;
                *dst2++ = (g - mean_g)/std_g;
                *dst3++ = (b - mean_b)/std_b;
            }
        }
        return out;
    }
};

#endif

class RefinementProcessor : public Processor
{

public:

    struct InitData
    {
        int sigma;
        int inc_blur;
        int start_hfov;
        int end_hfov;
    };

protected:

    PAL::Data::Stereo m_oCurrentOutput;

    InitData m_oParams;
    
    Normalizer normalizer;

public:

    PAL::Acknowledgement Init(void* arg) override;

    PAL::Acknowledgement ChangeInternalState(PAL::CameraProperties* props, unsigned int *flags) override;

    void* Iterate(void* input) override;

    PAL::Data::Stereo Process(PAL::Data::Stereo input);

    void Destroy() override;

    ~RefinementProcessor();

};

# endif //REFINEMENT_PROCESSOR_H
