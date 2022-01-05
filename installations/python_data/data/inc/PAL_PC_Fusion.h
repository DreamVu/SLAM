# ifndef PAL_PC_FUSION_H
# define PAL_PC_FUSION_H

#include <iostream>
#include <unistd.h>
#include <math.h>
#include "sys/stat.h"

#include <opencv2/opencv.hpp>

# include "Calibration.h"
# include "CameraProperties.h"
# include "DataExchange.h"
# include "Processor.h"

static const float PI = 3.1415926535898f;
#define MAX_FLOOR_EXCLUSION_THRESHOLD 220
#define OBJECT_BREAK_MONODEPTH_THRESHOLD 100
#define DNET_FLOOR_THRESHOLD 125

struct fusion_data
{
    cv::Mat focal_depth;
    cv::Mat focal_map;
};

using namespace cv;
using namespace std;

class PAL_PC_Fusion : public Processor
{
    int m_iHorizon;

protected:

	PAL::Data::FloorFocalMap m_oCurrentOutput;

public:

    PAL_PC_Fusion() {}

    cv::Mat m_matProjectionDepth;
    cv::Mat m_matFocalLengthMap; 

    PAL::Acknowledgement Init(void* arg) override;
    PAL::Acknowledgement ChangeInternalState(PAL::CameraProperties* props, unsigned int *flags) override;
    void* Iterate(void* input) override;
	PAL::Data::FloorFocalMap Process(PAL::Data::FloorMask input);
    fusion_data  GetFusionData(cv::Mat left, cv::Mat depth, cv::Mat floor_mask_non_binary);
    void Destroy();
};



# endif //PAL_PC_FUSION_H
