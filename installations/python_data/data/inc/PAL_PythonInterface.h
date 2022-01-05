# ifndef PAL_PYTHON_INTERFACE_H
# define PAL_PYTHON_INTERFACE_H

#include <Python.h>
#include <stdlib.h>
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <numpy/arrayobject.h>

class PAL_PythonInterface
{
	static bool ms_bInitialized;

protected:
	cv::Mat m_mLastOputput;

public:

	static void InitializePython();

	static void ClosePython();

	bool Init();

	virtual void Destroy() = 0;

	int Process(cv::Mat* inputs, int in_count, cv::Mat* outputs);
};


class PAL_HeirarchialStereo : public PAL_PythonInterface
{

	PyObject *m_pName, *m_pModule, *m_pDict, *m_pFuncComputeDisparity, *m_pFuncInit, *m_pInitArgs, *m_pComputeDisparityArgs, *m_pLeftarray, *m_pRightarray, *m_pRows, *m_pCols, *m_pWeights;

public:

	PAL_HeirarchialStereo() :m_pName(0), m_pModule(0), m_pDict(0), m_pFuncComputeDisparity(0), m_pFuncInit(0), m_pInitArgs(0), m_pComputeDisparityArgs(0), m_pRows(0), m_pCols(0), m_pWeights(0) {}

	bool Init();

	void Destroy();

	int Process(cv::Mat* inputs, int in_count, cv::Mat* outputs);

	cv::Mat ComputeDisparityHS(cv::Mat left, cv::Mat right);

};

class PAL_GAN : public PAL_PythonInterface
{

	PyObject *m_pName, *m_pModule, *m_pDict, *m_pFuncDeblurGAN, *m_pFuncInit, *m_pInitArgs, *m_pDeblurGANArgs, *m_pInputarray, *m_pRows, *m_pCols, *m_pWeights, *m_pFuncUpdate, *m_pUpdateArgs;

public:

	PAL_GAN() :m_pName(0), m_pModule(0), m_pDict(0), m_pFuncDeblurGAN(0), m_pFuncInit(0), m_pInitArgs(0), m_pDeblurGANArgs(0), m_pRows(0), m_pCols(0), m_pWeights(0), m_pFuncUpdate(0), m_pUpdateArgs(0){}

	bool Init();

	void Destroy();

	int Process(cv::Mat* inputs, int in_count, cv::Mat* outputs);

	cv::Mat Rectify(cv::Mat& left, cv::Mat& right);

	void Update(int new_width, int new_height, int fov_start, int fov_end);

};

class PAL_SharpNet : public PAL_PythonInterface
{

	PyObject *m_pName, *m_pModule, *m_pDict, *m_pFuncDeblurSN, *m_pFuncInit, *m_pInitArgs, *m_pDeblurSNArgs, *m_pInputarray, *m_pRows, *m_pCols, *m_pWeights;

public:

	PAL_SharpNet() :m_pName(0), m_pModule(0), m_pDict(0), m_pFuncDeblurSN(0), m_pFuncInit(0), m_pInitArgs(0), m_pDeblurSNArgs(0), m_pRows(0), m_pCols(0), m_pWeights(0) {}

	bool Init();

	void Destroy();

	int Process(cv::Mat* inputs, int in_count, cv::Mat* outputs);

	cv::Mat ComputeDepthSN(cv::Mat& input);

};

class PAL_SDE : public PAL_PythonInterface
{

	PyObject *m_pName, *m_pModule, *m_pDict, *m_pFuncDeblurSDE, *m_pFuncInit, *m_pInitArgs, *m_pDeblurSDEArgs, *m_pInputarray, *m_pRows, *m_pCols, *m_pWeights;

public:

	PAL_SDE() :m_pName(0), m_pModule(0), m_pDict(0), m_pFuncDeblurSDE(0), m_pFuncInit(0), m_pInitArgs(0), m_pDeblurSDEArgs(0), m_pRows(0), m_pCols(0), m_pWeights(0) {}

	bool Init();

	void Destroy();

	int Process(cv::Mat* inputs, int in_count, cv::Mat* outputs);

	cv::Mat ComputeDepthSDE(cv::Mat& input);

};


class PAL_MIDAS_NANO : public PAL_PythonInterface
{

	PyObject *m_pName, *m_pModule, *m_pDict, *m_pFuncDeblurSDE, *m_pFuncInit, *m_pInitArgs, *m_pDeblurSDEArgs, *m_pInputarray, *m_pRows, *m_pCols, *m_pWeights;

public:

	PAL_MIDAS_NANO() :m_pName(0), m_pModule(0), m_pDict(0), m_pFuncDeblurSDE(0), m_pFuncInit(0), m_pInitArgs(0), m_pDeblurSDEArgs(0), m_pRows(0), m_pCols(0), m_pWeights(0) {}

	bool Init();

	void Destroy();

	int Process(cv::Mat* inputs, int in_count, cv::Mat* outputs);

	cv::Mat ComputeDepthSDE(cv::Mat& input);

};


class PAL_MIDAS : public PAL_PythonInterface
{

	PyObject *m_pName, *m_pModule, *m_pDict, *m_pFuncDeblurSDE, *m_pFuncInit, *m_pInitArgs, *m_pDeblurSDEArgs, *m_pInputarray, *m_pRows, *m_pCols, *m_pWeights;

public:

	PAL_MIDAS() :m_pName(0), m_pModule(0), m_pDict(0), m_pFuncDeblurSDE(0), m_pFuncInit(0), m_pInitArgs(0), m_pDeblurSDEArgs(0), m_pRows(0), m_pCols(0), m_pWeights(0) {}

	bool Init();

	void Destroy();

	int Process(cv::Mat* inputs, int in_count, cv::Mat* outputs);

	cv::Mat ComputeDepthSDE(cv::Mat& input);

};

class PAL_SharpNetNormals : public PAL_PythonInterface
{

	PyObject *m_pName, *m_pModule, *m_pDict, *m_pFuncDeblurSNN, *m_pFuncInit, *m_pInitArgs, *m_pDeblurSNNArgs, *m_pInputarray, *m_pRows, *m_pCols, *m_pWeights;

public:

	PAL_SharpNetNormals() :m_pName(0), m_pModule(0), m_pDict(0), m_pFuncDeblurSNN(0), m_pFuncInit(0), m_pInitArgs(0), m_pDeblurSNNArgs(0), m_pRows(0), m_pCols(0), m_pWeights(0) {}

	bool Init();

	void Destroy();

    int Process(cv::Mat* inputs, int in_count, cv::Mat* outputs);
    
    cv::Mat GetNormalsSN(cv::Mat& input);
    
};

class PAL_EDET : public PAL_PythonInterface
{

	PyObject *m_pName, *m_pModule, *m_pDict, *m_pFuncDeblurEDET, *m_pFuncInit, *m_pInitArgs, *m_pDeblurEDETArgs, *m_pInputarray, *m_pRows, *m_pCols, *m_pWeights;

public:

	PAL_EDET() :m_pName(0), m_pModule(0), m_pDict(0), m_pFuncDeblurEDET(0), m_pFuncInit(0), m_pInitArgs(0), m_pDeblurEDETArgs(0), m_pRows(0), m_pCols(0), m_pWeights(0) {}

	bool Init(float threshold);

	void Destroy();

	int ProcessBoxes(cv::Mat* inputs, int in_count, std::vector<int>* bbox);

	std::vector<int> Detect(cv::Mat& input);

};

class PAL_SSD : public PAL_PythonInterface
{

	PyObject *m_pName, *m_pModule, *m_pDict, *m_pFuncDeblurSSD, *m_pFuncInit, *m_pInitArgs, *m_pDeblurSSDArgs, *m_pInputarray, *m_pRows, *m_pCols, *m_pWeights;

public:

	PAL_SSD() :m_pName(0), m_pModule(0), m_pDict(0), m_pFuncDeblurSSD(0), m_pFuncInit(0), m_pInitArgs(0), m_pDeblurSSDArgs(0), m_pRows(0), m_pCols(0), m_pWeights(0) {}

	bool Init(float threshold);

	void Destroy();

	int ProcessBoxes(cv::Mat* inputs, int in_count, std::vector<int>* bbox);

	std::vector<int> Detect(cv::Mat& input);

};

class FastFloor : public PAL_PythonInterface
{

	PyObject *m_pName, *m_pModule, *m_pDict, *m_pFuncDeblurEnet, *m_pFuncInit, *m_pInitArgs, *m_pDeblurEnetArgs, *m_pInputarray, *m_pRows, *m_pCols, *m_pWeights;

public:

	FastFloor() :m_pName(0), m_pModule(0), m_pDict(0), m_pFuncDeblurEnet(0), m_pFuncInit(0), m_pInitArgs(0), m_pDeblurEnetArgs(0), m_pRows(0), m_pCols(0), m_pWeights(0) {}

	bool Init(int sets);

	void Destroy();

	int ProcessDual(cv::Mat input, int in_count, cv::Mat& outputs);

	cv::Mat ComputeDepthFloor(cv::Mat input);

};
# endif //PAL_PYTHON_INTERFACE_H
