#include "KinectUtilites.h"

KinectUtilities* KinectUtilities::m_kinectInstance = nullptr;

bool KinectUtilities::InitKinect()
{
	if (FAILED(GetDefaultKinectSensor(&m_sensor))) {
		return false;
	}
	if (m_sensor) {
		m_sensor->get_CoordinateMapper(&m_mapper);

		m_sensor->Open();
		m_sensor->OpenMultiSourceFrameReader(
			FrameSourceTypes::FrameSourceTypes_Depth 
			| FrameSourceTypes::FrameSourceTypes_Color
			| FrameSourceTypes::FrameSourceTypes_Body,
			&m_reader);
		return m_reader;
	}
	else {
		return false;
	}
}

KinectUtilities * KinectUtilities::GetInstance()
{
	if (m_kinectInstance == nullptr)
	{
		m_kinectInstance = new KinectUtilities();
		if (!m_kinectInstance->InitKinect())
		{
			delete m_kinectInstance;
			m_kinectInstance = nullptr;
		}
	}
	return m_kinectInstance;
}

void KinectUtilities::ReleaseInstance()
{
	if (m_kinectInstance != nullptr)
	{
		delete m_kinectInstance;
		m_kinectInstance = nullptr;
	}
}

void KinectUtilities::GetKinectData() 
{	
	IMultiSourceFrame* frame = NULL;
	if (SUCCEEDED(m_reader->AcquireLatestFrame(&frame))) {
		//GetDepthData(frame, m_ColorData);
		//GetColorData(frame, m_DepthData);
		GetBodyData(frame);
	}
	if (frame) frame->Release();
}

void KinectUtilities::GetDepthData(IMultiSourceFrame * frame, GLubyte * dest)
{
	IDepthFrame* depthFrame;
	IDepthFrameReference* frameref = NULL;
	frame->get_DepthFrameReference(&frameref);
	frameref->AcquireFrame(&depthFrame);
	if (frameref) frameref->Release();
	if (!depthFrame) return;

	unsigned int sz;
	unsigned short* buf;
	depthFrame->AccessUnderlyingBuffer(&sz, &buf);

	m_mapper->MapDepthFrameToCameraSpace(
		512*424, buf,        // Depth frame data and size of depth frame
		512 * 424, depth2xyz); // Output CameraSpacePoint array and size
	float* fdest = (float*)dest;
	for (int i = 0; i < 512 * 424; i++) {
		*fdest++ = depth2xyz[i].X;
		*fdest++ = depth2xyz[i].Y;
		*fdest++ = depth2xyz[i].Z;
	}

	m_mapper->MapDepthFrameToColorSpace(
		512 * 424, buf,        // Depth frame data and size of depth frame
		512 * 424, depth2rgb); // Output ColorSpacePoint array and size

	if (depthFrame) depthFrame->Release();
}

void KinectUtilities::GetColorData(IMultiSourceFrame * frame, GLubyte * dest)
{
	IColorFrame* colorFrame;
	IColorFrameReference* frameref = NULL;
	frame->get_ColorFrameReference(&frameref);
	frameref->AcquireFrame(&colorFrame);
	if (frameref) frameref->Release();
	if (!colorFrame) return;
	
	colorFrame->CopyConvertedFrameDataToArray(1920*1080 * 4, m_rgbImage, ColorImageFormat_Bgra);

	float* fdest = (float*)dest;
	for (int i = 0; i < 512 * 424; i++) {
		ColorSpacePoint p = depth2rgb[i];
		// Check if color pixel coordinates are in bounds
		if (p.X < 0 || p.Y < 0 || p.X > 1920 || p.Y > 1080) {
			*fdest++ = 0;
			*fdest++ = 0;
			*fdest++ = 0;
		}
		else {
			int idx = (int)p.X + 1920*(int)p.Y;
			*fdest++ = m_rgbImage[4 * idx + 0] / 255.;
			*fdest++ = m_rgbImage[4 * idx + 1] / 255.;
			*fdest++ = m_rgbImage[4 * idx + 2] / 255.;
		}
		// Don't copy alpha channel
	}

	if (colorFrame) colorFrame->Release();
}

void KinectUtilities::GetBodyData(IMultiSourceFrame * frame)
{
	IBodyFrame* bodyframe;
	IBodyFrameReference* frameref = NULL;
	frame->get_BodyFrameReference(&frameref);
	frameref->AcquireFrame(&bodyframe);
	if (frameref) frameref->Release();

	if (!bodyframe) return;

	IBody* body[BODY_COUNT] = {0, 0, 0, 0, 0, 0};
	bodyframe->GetAndRefreshBodyData(BODY_COUNT, body);
	for (int i = 0; i < BODY_COUNT; i++) {
		body[i]->get_IsTracked(&m_tracked);
		if (m_tracked) {
			body[i]->GetJoints(JointType_Count, joints);
			break;
		}
	}

	if (bodyframe) bodyframe->Release();
}
