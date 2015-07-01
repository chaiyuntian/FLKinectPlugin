
#pragma once

#include "FLKinectPluginPrivatePCH.h"

class FKinectPluginCore
{
public:
	FKinectPluginCore();
	~FKinectPluginCore();

	void					Setup();
	void                    Update();
	bool					getIsLeftHandClosed();
	bool					getIsRightHandClosed();
	Joint					getLeftHandPos();
	Joint					getRightHandPos();

private:
	int64                   m_nStartTime;
	int64                   m_nLastCounter;
	double                  m_fFreq;
	int64                   m_nNextStatusTime;
	uint32                   m_nFramesSinceUpdate;

	// Current Kinect
	IKinectSensor*          m_pKinectSensor;
	ICoordinateMapper*      m_pCoordinateMapper;

	// Body reader
	IBodyFrameReader*       m_pBodyFrameReader;

	//Initialize Kinect
	HRESULT                 InitializeDefaultSensor();

	//Process the body
	void					GetBody(INT64 nTime, int nBodyCount, IBody** ppBodies);

	//Set a toggle bool for Hand Open / Close
	void					setIsLeftHandClosed(int gestureIndex);
	void					setIsRightHandClosed(int gestureIndex);
	bool					rightHandToggle, leftHandToggle;

	//Set Hand Position Variable
	void					setLeftHandPos(Joint leftHandPos);
	void					setRightHandPos(Joint rightHandPos);
	Joint					leftHandPosContainer, rightHandPosContainer;



};



