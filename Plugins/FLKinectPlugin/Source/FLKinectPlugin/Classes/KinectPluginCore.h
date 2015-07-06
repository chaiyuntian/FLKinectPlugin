#pragma once

//#include "FLKinectPluginPrivatePCH.h"
#include "CoreUObject.h"
/*
#include "AllowWindowsPlatformTypes.h"
#include "Kinect.h"
#include "HideWindowsPlatformTypes.h"
*/

class FKinectPluginCore : public FRunnable
{
public:
	FKinectPluginCore();
	~FKinectPluginCore();

	/* Begin FRunnable interface. */
	virtual bool Init();
	virtual uint32 Run();
	virtual void Stop();
	/* End FRunnable interface */

	/* Singleton Interface*/
	static FKinectPluginCore* GetInstance();
	FRunnableThread* Thread;

	/* Public state variables */
	FVector	RightHandLastPosition;
	FVector	LeftHandLastPosition;
	bool		RightHandLastIsClosed;
	bool		LeftHandLastIsClosed;
	


	void					Setup();
	void                    Update();
	bool					GetIsLeftHandClosed();
	bool					GetIsRightHandClosed();
	Joint					GetLeftHandPos();
	Joint					GetRightHandPos();

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
	void					SetIsLeftHandClosed(int gestureIndex);
	void					SetIsRightHandClosed(int gestureIndex);
	bool					rightHandToggle, leftHandToggle;

	//Set Hand Position Variable
	void					SetLeftHandPos(Joint leftHandPos);
	void					SetRightHandPos(Joint rightHandPos);
	Joint					leftHandPosContainer, rightHandPosContainer;


private:

	/* Frunnable Helper. */
	bool bRunning;
	static FKinectPluginCore* Instance;
};



