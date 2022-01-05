# ifndef ODOA_FUSION_H
# define ODOA_FUSION_H

# include "Processor.h"
# include "DataExchange.h"

#define SCAN_WIDTH 1312

using namespace cv;
//# define FUNC() printf("INSIDE %s --> %d : %s\n\n", __FILE__, __LINE__, __func__)
class ODOA_Fusion : public Processor
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

    cv::Mat floor_boundary;
    
    cv::Mat g_fpdepth;
    
    std::vector<cv::Mat> inverseNLCLUT;
    
    CircularBuffer cb_refined_lefts;
    



public:

    
    PAL::Resolution current_resolution;
    
    int fov_start;
    int fov_end;
    
    int widths[5] = {3440, 1312, 760, 1200, 434};
    int heights[5] = {1016,  350,  224, 300, 128};
    int nlc_crops[4] = {224, 224, 222, 111};
    int inc_crops[4] = {224, 224, 236, 123};
    
    int active_image = 0;

    cv::Mat laser_scan = cv::Mat::zeros(1, SCAN_WIDTH, CV_32FC1);
    
    struct ODOAParams
    {
	    float floor_mask_threshold, floor_mask_percentile, stereo_threshold, stereo_col_sum_threshold, stereo_row_sum_threshold, canny_blur, canny_lower_thresh, canny_higher_thresh, refine_laser_search, start_hfov, end_hfov, start_vfov, end_vfov, camera_height, laser_start_vfov, laser_end_vfov, sigma, close_obs, inc_blur, nlc, hc, temporal;

	    ODOAParams() : floor_mask_threshold(0), floor_mask_percentile(0), stereo_threshold(10), stereo_col_sum_threshold(10), stereo_row_sum_threshold(0), canny_blur(5), canny_lower_thresh(40), canny_higher_thresh(120), refine_laser_search(50), start_hfov(0), end_hfov(360), start_vfov(0), end_vfov(1), camera_height(20), laser_start_vfov(50), laser_end_vfov(90), sigma(0), close_obs(0), inc_blur(2), nlc(1), hc(0), temporal(5)
		    {

		    } 

    };

    //void Init(const char* odoa, std::vector<cv::Mat> ReadInverseNLCLUT, int width, int height);

    
    ODOA_Fusion::ODOAParams g_sparams;   

    std::vector<cv::Mat> frames;


    
    
    
    
     struct InitData
    {
        const char* odoa;
        std::string prefix;
        std::vector<cv::Mat> ReadInverseNLCLUT;
        int width;
        int height;
        
    };

    
    PAL::Data::ODOA_Data m_matCurrentOutput;
    InitData m_oParams;
    
    cv::Mat Fuse(cv::Mat disp_depth, cv::Mat dual, cv::Mat left);
    
    PAL::Acknowledgement Init(void* arg) ;
    
    void* Iterate(void* input) override;
    
    PAL::Data::ODOA_Data Process(PAL::Data::ODOA_Data input);

    PAL::Acknowledgement ChangeInternalState(PAL::CameraProperties* props, unsigned int *flags) override;
    
    PAL::Acknowledgement GetOdoaData(PAL::CameraProperties* data);

    cv::Mat MarkBoundary(cv::Mat pano, cv::Mat depth);
    
    cv::Mat getProjectionDepthMat(Mat focal_map, float bot_height);
    
    cv::Mat getFocalLengthMat();
    
    void LoadODOAFileProperties(const char* fileName);
    
    void ValidateODOAProperties();

    void Synchronize();

    void Destroy();
    
    
};
# endif //ODOA_FUSION_H











