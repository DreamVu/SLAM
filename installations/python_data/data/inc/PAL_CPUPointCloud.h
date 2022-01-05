# ifndef CPU_POINT_CLOUD_H
# define CPU_POINT_CLOUD_H

# include <opencv2/opencv.hpp>
# include "CameraProperties.h"
# include "PAL_PointCloud.h"
# include "Processor.h"

class CPU_PointCLoud : public PointCloud
{
	cv::Mat W_X;			//The x value of the point - for the given pixel column
	cv::Mat W_COS;			// cos and sin for rotation of the point - depending on pixel column
	cv::Mat W_SIN;

	cv::Mat PC_DATA;		//The actual point cloud data

	int m_iCY;
	float focal_x;

public:

	struct InputData
	{
		cv::Mat left;
		cv::Mat depth;
		cv::Mat focal_y;
		timeval timestamp;
	};


	struct OutputData
	{
		cv::Mat pcMat; 
		timeval timestamp;
	};


protected:

    OutputData m_matCurrentOutput;
	PAL::Data::PointCloud m_oLatestOutput;

public:

	PAL::Acknowledgement Init(void* arg);
    PAL::Acknowledgement ChangeInternalState(PAL::CameraProperties* props, unsigned int *flags);
    void* Iterate(void* input);
	void RecomputeOptimizations(int width, int start, int end);
	PAL::Data::PointCloud Process(PAL::Data::FloorFocalMap input);
	cv::Mat ComputePointCloud(cv::Mat left, cv::Mat depth, cv::Mat focal_y);
	bool SavePointCloud(const char* fileName, cv::Mat pcMat);

    void Destroy();
};




# endif //CPU_POINT_CLOUD_H
