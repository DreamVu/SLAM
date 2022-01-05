# ifndef PIPELINE_H
# define PIPELINE_H

# include "PanoramaThread.h"
# include "RefinementThread.h"
# include "FusionThread.h"
# include "PointCloudThread.h"
# include "SGBM_Thread.h"
# include "ODOA_FusionThread.h"
# include "DummyPythonThread.h"

class Pipeline
{
public:

protected:

    struct ThreadFlags
    {
        bool stereo;
        bool refined;
        bool sgbm;
        bool floor_fusion;
        bool point_cloud;
        bool python;
        bool odoa_fusion;

        ThreadFlags() : stereo(false), refined(false), sgbm(false), floor_fusion(false), point_cloud(false), python(false), odoa_fusion(false){}
    };

    DataLock m_oPythonInitLock;
    
    ParallelNode *m_pOutputNode;

    ThreadFlags m_oFlag;

    PanoramaThread m_oPanorama; 

    RefinementThread m_oRefinement;

    FusionThread m_oFloorFusion;

    PointCloudThread m_oPointCloud;

    // DetectionThread m_oPeople;

    DummyPythonThread m_oPython;

    SGBM_Thread m_oStereoDepth;

    ODOA_FusionThread m_oFusion;

    // Mode m_eCurrentMode;

    PAL::Mode m_eCurrentMode;

    void SetStereoMode();

    void SetDepthMode(); //implement

    void SetPeopleMode(bool depth);  //modify

    void SetPointCloudMode();

    void SetRefinementMode();    //REMOVE

    void SetSGBMMode(); //remove

    void SetODOAFusionMode();
    
    const char* m_sPath="/home/dreamvu/data5/";

public:

    Pipeline(): m_eCurrentMode(PAL::Mode::IDLE){}
    


    void Init(void*, int camera_index);

    PAL::Acknowledgement ChangeInternalState(PAL::CameraProperties* props, unsigned int *flags);

    void Destroy();

    void DettachAllThreads();

    void Stop();

    void ResumeAfterCIS();
    
    void SetPathtoData(const char* path);


    bool SavePointCloud(const char* fileName, cv::Mat pcMat);

    PAL::Acknowledgement GetCameraSettings(PAL::CameraProperties* data);
    
    PAL::Acknowledgement GetOdoaData(PAL::CameraProperties* data);
    
    PAL::Data::Stereo GrabStereoModeData();

    PAL::Data::Depth GrabDepthModeData();

    PAL::Data::People GrabPeopleModeData(bool depth);

    PAL::Data::Stereo GrabRefinedModeData();   //REMOVE

    PAL::Data::StereoDepthData GrabSGBMModeData(); //remove

    PAL::Data::PointCloud GrabPointCloudModeData();

    PAL::Data::ODOA_Data GrabODOAFusionModeData();

    ~Pipeline() { Destroy(); }
};
# endif //PIPELINE_H
