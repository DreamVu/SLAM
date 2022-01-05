# ifndef PAL_CAMERA_PROPERTIES_H
# define PAL_CAMERA_PROPERTIES_H

namespace PAL
{

	enum CameraPropertyFlags
	{
        BRIGHTNESS = 0x1,
		CONTRAST = 0x2,
		SATURATION = 0x4,
		GAMMA = 0x8,
		GAIN = 0x10,
		WHITE_BAL_TEMP = 0x20,
		SHARPNESS = 0x40,
		EXPOSURE = 0x80,
		AUTO_WHITE_BAL = 0x100,
		AUTO_EXPOSURE = 0x200,
		RESOLUTION = 0x400,
		COLOR_SPACE = 0x800,
		POWER_LINE_FREQUENCY = 0x1000,
		VERTICAL_FLIP = 0x2000,
		FILTER_DISPARITY = 0x4000,
		FILTER_SPOTS = 0x8000,
        FOV = 0x10000,
		PROJECTION = 0x20000,
		DISPARITY_COMPUTATION = 0x40000,
		CAMERA_HEIGHT = 0x80000,		
		DETECTION_MODE = 0x100000,
		ALL = 0x1FFFFF,
		
		ODOA_DEPTHTHRESH = 0x200000,
		ODOA_DEPTHSIGMA = 0x400000,
		ODOA_STEREOTHRESH = 0x800000,
		ODOA_STARTHFOV = 0x1000000,
		ODOA_ENDHFOV = 0x2000000,
		ODOA_STARTVFOV = 0x4000000,
		ODOA_ENDVFOV   = 0x8000000,
		ODOA_CAMERAHEIGHT = 0x10000000,
		ODOA_DEPTHREF = 0x20000000,
		ODOA_DEPTHTEMPORAL = 0x40000000,
		ODOA_ALL = 0x7FE00000,
		
	};

	struct Resolution
	{
		int width;
		int height;
	};

    struct ODOA_Properties
	{
		
    int depth_context_threshold;
    int depth_context_sigma;
    int stereo_threshold; 
    int odoa_start_hfov; 
    int odoa_hfov_range; 
    int odoa_start_vfov; 
    int odoa_end_vfov; 
    int camera_height;
    int depth_context_refinement; 
    int depth_context_temporal;
    
    static const int MAX_DEPTH_THRESHOLD = 254;
	static const int MAX_DEPTH_SIGMA = 25;
	static const int MAX_STEREO_THRESHOLD = 25;
	static const int MAX_START_HFOV = 359;
	static const int MAX_END_HFOV = 360;
	static const int MAX_START_VFOV = 100;
	static const int MAX_END_VFOV = 100;
	static const int MAX_ODOA_CAMERA_HEIGHT = 300;
	static const int MAX_DEPTH_REF = 4;
	static const int MAX_DEPTH_TEMPORAL = 10;
    
    
    
    static const int MIN_DEPTH_THRESHOLD = 100;
	static const int MIN_DEPTH_SIGMA = 0;
	static const int MIN_STEREO_THRESHOLD = 0;
	static const int MIN_START_HFOV = 0;
	static const int MIN_END_HFOV = 1;
	static const int MIN_START_VFOV = 0;
	static const int MIN_END_VFOV = 0;
	static const int MIN_ODOA_CAMERA_HEIGHT = 0;
	static const int MIN_DEPTH_REF = 0;
	static const int MIN_DEPTH_TEMPORAL = 0;
    
    
    static const int DEFAULT_DEPTH_THRESHOLD = 200;
	static const int DEFAULT_DEPTH_SIGMA = 0;
	static const int DEFAULT_STEREO_THRESHOLD = 25;
	static const int DEFAULT_START_HFOV = 0;
	static const int DEFAULT_HFOV_RANGE = 360;
	static const int DEFAULT_START_VFOV = 50;
	static const int DEFAULT_END_VFOV = 90;
	static const int DEFAULT_ODOA_CAMERA_HEIGHT = 25;
	static const int DEFAULT_DEPTH_REF = 2;
	static const int DEFAULT_DEPTH_TEMPORAL = 5;
	
	
	ODOA_Properties () :
	depth_context_threshold (DEFAULT_DEPTH_THRESHOLD),
	depth_context_sigma     (DEFAULT_DEPTH_SIGMA),
	stereo_threshold        (DEFAULT_STEREO_THRESHOLD),
	odoa_start_hfov         (DEFAULT_START_HFOV),
	odoa_hfov_range         (DEFAULT_HFOV_RANGE),
	odoa_start_vfov         (DEFAULT_START_VFOV),
	odoa_end_vfov           (DEFAULT_END_VFOV),
	camera_height           (DEFAULT_ODOA_CAMERA_HEIGHT),
	depth_context_refinement (DEFAULT_DEPTH_REF),
	depth_context_temporal   (DEFAULT_DEPTH_TEMPORAL)
    {
    }
	};


	enum CaptureType
	{
		DUMMY,
		CAMERA
	};


	enum Acknowledgement
	{
		IGNORED, 
		SUCCESS, 
		FAILURE, 
		INVALID_PROPERTY_VALUE, 
		ERROR_CAMERA_NOT_INITIALIZED
	};

	enum ColorSpace
	{
		RGB,
		YUV444
	};

	enum PowerLineFrequency
	{
		_AUTO,
		_50HZ,
		_60HZ
	};

	enum Projection
	{
		EQUI_RECTANGULAR = 0,
		PERSPECTIVE = 1,
	};

	enum DisparityComputation
	{
		FAST = 0,
		HIGH_QUALITY_A = 1,
		HIGH_QUALITY_B = 2,
	};
	
	enum DetectionMode
	{
		FLOOR = 1,
		TABLE_TOP = 2,
		CEILING = 3,
		AUTO = 4,
	};

	struct CameraProperties
	{
	    int brightness;
	    int contrast;
		int saturation;
		int gamma;
		int gain;
		int white_bal_temp;
		int sharpness;
		int exposure;
		bool  auto_white_bal;
		bool  auto_exposure;
        

		Resolution resolution;
		CaptureType capture_type;
		ColorSpace color_space;
		PowerLineFrequency power_line_frequency;

        // ODOA Parameteres
		ODOA_Properties odoa_params;
			
		bool  vertical_flip;
		bool  filter_disparity;
		bool  filter_spots;
        
		//horizontal FOV in degrees
		int   fov_start; 
		int   fov_end;

		//Projection type : equi-rectangular or perspective
		Projection projection;

		//Should this be fast but of lower quality?
		//or of high quality but slow
		DisparityComputation computation;
			
		//height of camera centre from floor in cm 
		int camera_height;
		
		//Modes of the camera position to be used in person detection
		DetectionMode detection_mode;
        
        static const int MAX_BRIGHTNESS = 15;
		static const int MIN_BRIGHTNESS = -15;
		static const int DEFAULT_BRIGHTNESS = 0;
		
		static const int MAX_CONTRAST = 30;
		static const int MIN_CONTRAST = 0;
		static const int DEFAULT_CONTRAST = 15;
		
		static const int MAX_SATURATION = 60;
		static const int MIN_SATURATION = 0;
		static const int DEFAULT_SATURATION = 32;

		static const int MAX_GAMMA = 500;
		static const int MIN_GAMMA = 40;
		static const int DEFAULT_GAMMA = 220;

		static const int MAX_GAIN = 100;
		static const int MIN_GAIN = 0;
		static const int DEFAULT_GAIN = 4;

		static const int MAX_WHITE_BAL_TEMP = 10000;
		static const int MIN_WHITE_BAL_TEMP = 1000;
		static const int DEFAULT_WHITE_BAL_TEMP = 5000;
		
		static const int MAX_SHARPNESS = 127;
		static const int MIN_SHARPNESS = 0;
		static const int DEFAULT_SHARPNESS = 0;
		
		static const int MAX_EXPOSURE = 10000;
		static const int MIN_EXPOSURE = 1;
		static const int DEFAULT_EXPOSURE = 500;
				
		static const bool DEFAULT_AUTO_WHITE_BAL = 1;
		static const bool DEFAULT_AUTO_EXPOSURE = 0;

		static const Resolution DEFAULT_RESOLUTION;
		static const CaptureType DEFAULT_CAPTURE_TYPE = CaptureType::CAMERA;
		static const ColorSpace DEFAULT_COLOR_SPACE = RGB;
		static const PowerLineFrequency DEFAULT_POWER_LINE_FREQUENCY = _AUTO;

		static const bool DEFAULT_VERTICAL_FLIP = false;
		static const bool DEFAULT_FILTER_DISPARITY = true;
		static const bool DEFAULT_FILTER_SPOTS = true;
        
		static const int DEFAULT_FOV_START = 0;
		static const int DEFAULT_FOV_END = 360;

		static const Projection DEFAULT_PROJECTION = PERSPECTIVE;
		static const DisparityComputation DEFAULT_COMPUTATION = HIGH_QUALITY_A;

		static const DetectionMode DEFAULT_DETECTION_MODE = TABLE_TOP;

		static const int DEFAULT_CAMERA_HEIGHT = 100;
		
		
		

		CameraProperties() :
			brightness           (DEFAULT_BRIGHTNESS),
			contrast             (DEFAULT_CONTRAST), 
			saturation           (DEFAULT_SATURATION),
			gamma                (DEFAULT_GAMMA),
			gain                 (DEFAULT_GAIN),
			white_bal_temp       (DEFAULT_WHITE_BAL_TEMP),
			sharpness            (DEFAULT_SHARPNESS),
			exposure             (DEFAULT_EXPOSURE),
			auto_white_bal       (DEFAULT_AUTO_WHITE_BAL),
			auto_exposure        (DEFAULT_AUTO_EXPOSURE),
			resolution           (DEFAULT_RESOLUTION),
			capture_type		 (DEFAULT_CAPTURE_TYPE),
			color_space          (DEFAULT_COLOR_SPACE),
			power_line_frequency (DEFAULT_POWER_LINE_FREQUENCY),
			vertical_flip        (DEFAULT_VERTICAL_FLIP),
			filter_disparity     (DEFAULT_FILTER_DISPARITY),
			filter_spots 	     (DEFAULT_FILTER_SPOTS),
			fov_start            (DEFAULT_FOV_START),
			fov_end              (DEFAULT_FOV_END),
			projection           (DEFAULT_PROJECTION),
			computation          (DEFAULT_COMPUTATION),
			camera_height	     (DEFAULT_CAMERA_HEIGHT),			
			detection_mode 	     (DEFAULT_DETECTION_MODE)
			
			//odoa_params.depth_context_threshold (DEFAULT_DEPTH_THRESHOLD),
			//odoa_params.depth_context_sigma     (DEFAULT_DEPTH_SIGMA),
			//odoa_params.stereo_threshold        (DEFAULT_STEREO_THRESHOLD),
			//odoa_params.odoa_start_hfov         (DEFAULT_START_HFOV),
			//odoa_params.odoa_end_hfov           (DEFAULT_END_HFOV),
			//odoa_params.odoa_start_vfov         (DEFAULT_START_VFOV),
			//odoa_params.odoa_end_vfov           (DEFAULT_END_VFOV),
			//odoa_params.camera_height           (DEFAULT_ODOA_CAMERA_HEIGHT),
			//odoa_params.depth_context_refinement (DEFAULT_DEPTH_REF),
			//odoa_params.depth_context_temporal   (DEFAULT_DEPTH_TEMPORAL)
		
		{
		}
	};

}//namespace

# endif //PAL_CAMERA_PROPERTIES_H

