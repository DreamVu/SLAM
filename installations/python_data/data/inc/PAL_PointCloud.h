# ifndef POINT_CLOUD_H
# define POINT_CLOUD_H

# include <opencv2/opencv.hpp>
# include "CameraProperties.h"
#include "DataExchange.h"
# include "Processor.h"

class PointCloud : public Processor
{
public:

	PAL::Acknowledgement Init(void* arg) override;
	void* Iterate(void* input) override;
	PAL::Acknowledgement ChangeInternalState(PAL::CameraProperties* prop, unsigned int *flags) override;
    void Destroy();
	virtual void RecomputeOptimizations(int width, int start, int end);
	virtual cv::Mat Compute(cv::Mat left, cv::Mat depth, cv::Mat matfocal_y);
	virtual PAL::Data::PointCloud Process(PAL::Data::FloorFocalMap input);
	virtual bool SavePointCloud(const char* fileName, cv::Mat pcMat);

	virtual ~PointCloud(){};

};




# endif //POINT_CLOUD_H
