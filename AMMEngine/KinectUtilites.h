#pragma once
//Download the kinect 2.0 SDK: https://www.microsoft.com/en-us/download/details.aspx?id=44561
#include <Windows.h>
#include <Ole2.h>
#include <Kinect.h>
#include "GLFW\glfw3.h"

class KinectUtilities {
private:
	void GetDepthData(IMultiSourceFrame* frame, GLubyte* dest);
	void GetColorData(IMultiSourceFrame* frame, GLubyte* dest);
	void GetBodyData(IMultiSourceFrame* frame);

	static KinectUtilities* m_kinectInstance;

	bool InitKinect();
public:
	static KinectUtilities* GetInstance();

	static void ReleaseInstance();

	void GetKinectData();

	GLubyte m_rgbImage[1920 * 1080 * 4];
	GLubyte m_ColorData[1920 * 1080 * 4];
	GLubyte m_DepthData[512 * 424 * 4];

	ColorSpacePoint depth2rgb[512 * 424];
	CameraSpacePoint depth2xyz[512 * 424];

	BOOLEAN m_tracked;
	Joint joints[JointType_Count];

	IKinectSensor* m_sensor;
	IMultiSourceFrameReader* m_reader;
	ICoordinateMapper* m_mapper;
};