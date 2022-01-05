# ifndef POINT_CLOUD_MANAGER_H
# define POINT_CLOUD_MANAGER_H

# include <opencv2/opencv.hpp>
# include "CameraProperties.h"
# include "PAL_CPUPointCloud.h"
# include "PAL_PointCloud.h"
# include "Processor.h" 

class PointCloudManager : public Processor
{

	PointCloud *m_pPointCloud;
	CPU_PointCLoud m_oCPUPointCloud;

protected:
	PAL::Data::PointCloud m_oCurrentOutput;

public:
	PointCloudManager();

	PAL::Acknowledgement Init(void* arg) override;

	PAL::Acknowledgement ChangeInternalState(PAL::CameraProperties* props, unsigned int *flags) override;

	void* Iterate(void* input) override;

	PAL::Data::PointCloud Process(PAL::Data::FloorFocalMap input);

	virtual bool SavePointCloud(const char* fileName, cv::Mat pcMat);
	
	void Destroy() override;

	virtual ~PointCloudManager(){};

};




# endif //POINT_CLOUD_MANAGER_H
