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

	void					Setup();
	void                    Update();
	bool					GetIsLeftHandClosed();
	bool					GetIsRightHandClosed();
	
	//Joint					GetLeftHandPos();
	//Joint					GetRightHandPos();

	//Joint					GetLeftWristPos();
	//Joint					GetRightWristPos();

	//bool					IsKinectTracking;

	/* Last Position Variables */
	FVector	RightHandLastPosition;
	FVector	LeftHandLastPosition;

	//FVector RightWristLastPosition;
	//FVector LeftWristLastPosition;


	bool		RightHandLastIsClosed;
	bool		LeftHandLastIsClosed;

	//Note (MR) : moved these to public

	//Set a toggle bool for Hand Open / Close
	void					SetIsLeftHandClosed(int gestureIndex);
	void					SetIsRightHandClosed(int gestureIndex);

	//Set Hand Position 
	void					SetLeftHandPos(Joint leftHandPos);
	void					SetRightHandPos(Joint rightHandPos);

	//Set Wrist Position
	//void					SetLeftWristPos(Joint leftWristPos);
	//void					SetRightWristPos(Joint rightWristPos);

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

	//Used for setters and getters
	bool					rightHandToggle, leftHandToggle;
	//Joint leftHandPosContainer, rightHandPosContainer;
	//Joint leftWristPosContainer, rightWristPosContainer;
	FVector leftHandPosContainer, rightHandPosContainer;
		
	

private:

	/* Frunnable Helper. */
	bool bRunning;
	static FKinectPluginCore* Instance;
};



//NOTE (MR) : Still need to get these Joints

/*JointType_AnkleLeft
JointType_AnkleRight
JointType_ElbowLeft
JointType_ElbowRight
JointType_FootLeft
JointType_FootRight
JointType_Head
JointType_HipLeft
JointType_HipRight
JointType_KneeLeft
JointType_KneeRight
JointType_KneeRight
JointType_Neck
JointType_ShoulderLeft
JointType_ShoulderRight
JointType_SpineBase
JointType_SpineMid
JointType_SpineShoulder
JointType_ThumbLeft
JointType_ThumbRight*/

