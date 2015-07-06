
#include "FLKinectPluginPrivatePCH.h"
#include "KinectPluginCore.h"


FKinectPluginCore::FKinectPluginCore():

		m_nStartTime(0),
		m_nLastCounter(0),
		m_nFramesSinceUpdate(0),
		m_fFreq(0),
		m_nNextStatusTime(0LL),
		m_pKinectSensor(NULL),
		m_pCoordinateMapper(NULL),
		m_pBodyFrameReader(NULL),

		rightHandToggle(false),
		leftHandToggle(false)

{
	UE_LOG(LogTemp, Warning, TEXT("Kinect Plugin Core Activated"))
		// NOTE (MR): Couldn't figure what this bit is for

		//LARGE_INTEGER qpf = { 0 };
		//if (QueryPerformanceFrequency(&qpf))
		//{
		//	m_fFreq = double(qpf.QuadPart);
		//}
}

// NOTE (OS): FUCK C++
FKinectPluginCore* FKinectPluginCore::Instance;

FKinectPluginCore* FKinectPluginCore::GetInstance()
{	
	if (Instance == nullptr)
	{
		//Save Singleton
		Instance = new FKinectPluginCore();
		//Run Thread	
		Instance->Thread = FRunnableThread::Create(Instance, TEXT("KinectThread"), 0, EThreadPriority::TPri_Normal);
	}
	return Instance;
}

	FKinectPluginCore::~FKinectPluginCore()
	{


		// done with body frame reader
		SafeRelease(&m_pBodyFrameReader);

		// done with coordinate mapper
		SafeRelease(&m_pCoordinateMapper);

		// close the Kinect Sensor
		if (m_pKinectSensor)
		{
			m_pKinectSensor->Close();
		}
	
		SafeRelease(&m_pKinectSensor);
	}


	bool FKinectPluginCore::Init()
	{
		Setup();
		bRunning = true;
		//HACK (OS): should return status
		return bRunning;
	}

	uint32 FKinectPluginCore::Run()
	{
		while (bRunning)
		{
			Update();
		}
		//TODO (OS): Should return status;
		return 0;
	}

	void FKinectPluginCore::Stop()
	{
		//TODO (OS - @MR): Implement this;
		bRunning = false;
	}


	void FKinectPluginCore::Setup() {

		InitializeDefaultSensor();

	}

	void FKinectPluginCore::Update()
	{
		if (!m_pBodyFrameReader)
		{
			return;
		}
		IBodyFrame* pBodyFrame = NULL;

		HRESULT hr = m_pBodyFrameReader->AcquireLatestFrame(&pBodyFrame);

		if (SUCCEEDED(hr))
		{
			INT64 nTime = 0;

			hr = pBodyFrame->get_RelativeTime(&nTime);

			IBody* ppBodies[BODY_COUNT] = { 0 };

			if (SUCCEEDED(hr))
			{
				hr = pBodyFrame->GetAndRefreshBodyData(_countof(ppBodies), ppBodies);
			}

			if (SUCCEEDED(hr))
			{
				GetBody(nTime, BODY_COUNT, ppBodies);

				// NOTE (MR) : Updating last Hand Positins and Gestures
				Joint rj = GetRightHandPos();
				Joint lj = GetLeftHandPos();
				RightHandLastPosition	= FVector(rj.Position.X, rj.Position.Z, rj.Position.Y);
				LeftHandLastPosition	= FVector(lj.Position.X, lj.Position.Z, lj.Position.Y);
				RightHandLastIsClosed	= GetIsRightHandClosed();
				LeftHandLastIsClosed	= GetIsLeftHandClosed();
			}

			for (int i = 0; i < _countof(ppBodies); ++i)
			{
				SafeRelease(&(ppBodies[i]));
			}
		}

		SafeRelease(&pBodyFrame);
	}


	HRESULT FKinectPluginCore::InitializeDefaultSensor()
	{
		HRESULT hr;

		hr = GetDefaultKinectSensor(&m_pKinectSensor);
		if (FAILED(hr))
		{
			return hr;
		}

		if (m_pKinectSensor)
		{
			// Initialize the Kinect and get coordinate mapper and the body reader
			IBodyFrameSource* pBodyFrameSource = NULL;

			hr = m_pKinectSensor->Open();

			if (SUCCEEDED(hr))
			{
				hr = m_pKinectSensor->get_CoordinateMapper(&m_pCoordinateMapper);
			}

			if (SUCCEEDED(hr))
			{
				hr = m_pKinectSensor->get_BodyFrameSource(&pBodyFrameSource);
			}

			if (SUCCEEDED(hr))
			{
				hr = pBodyFrameSource->OpenReader(&m_pBodyFrameReader);
			}

			SafeRelease(&pBodyFrameSource);
			
		}

		if (!m_pKinectSensor || FAILED(hr))
		{
			//SetStatusMessage(L"No ready Kinect found!", 10000, true);
			UE_LOG(LogTemp, Warning, TEXT("No Kinect Fonud!"))
			return E_FAIL;
		}

		return hr;
	}

	void FKinectPluginCore::GetBody(INT64 nTime, int nBodyCount, IBody** ppBodies) {
		for (int i = 0; i < nBodyCount; ++i)
		{
			IBody* pBody = ppBodies[i];
			if (pBody)
			{
				Joint joints[JointType_Count];
				//D2D1_POINT_2F jointPoints[JointType_Count];
				HandState leftHandState = HandState_Unknown;
				HandState rightHandState = HandState_Unknown;


				//Hands
				pBody->get_HandLeftState(&leftHandState);
				pBody->get_HandRightState(&rightHandState);

				//Joints
				pBody->GetJoints(_countof(joints), joints);
				for (int j = 0; j < _countof(joints); ++j)
				{
					//MR Note: In case we need to utilize this later
					//std::cout << "Joint X: " << jointPoints[j].x << endl;
					//std::cout << "Joint Y: " << jointPoints[j].y << endl;
				}

				//Set Left / Right Hand Pos
				SetLeftHandPos(joints[JointType_HandLeft]);
				SetRightHandPos(joints[JointType_HandRight]);

				//Set whether Left / Right Hand is closed
				SetIsLeftHandClosed(leftHandState);
				SetIsRightHandClosed(rightHandState);

				//Will need to make this so I can write it in the public update
				//cout << "Left Hand Pos X: " << getLeftHandPos().Position.X << endl;
				//cout << "Left Hand Pos Y: " << getLeftHandPos().Position.Y << endl;
				//cout << "Left Hand Pos Z: " << getLeftHandPos().Position.Z << endl;


				//cout << "Left Hand: " << kinect.getIsLeftHandClosed() << endl;
				//cout << "Right Hand: " << kinect.getIsRightHandClosed() << endl;
			}

		}
	}

	void FKinectPluginCore::SetIsLeftHandClosed(int gestureIndex) {

		//MR Report if hand is open or closed
		//open
		if (gestureIndex == 2) {

			leftHandToggle = false;
		}
		//close
		if (gestureIndex == 3) {

			leftHandToggle = true;
		}

	}

	void FKinectPluginCore::SetIsRightHandClosed(int gestureIndex) {

		//open
		if (gestureIndex == 2) {

			rightHandToggle = false;
		}
		//close
		if (gestureIndex == 3) {

			rightHandToggle = true;
		}


	}

	bool FKinectPluginCore::GetIsLeftHandClosed() {

		return leftHandToggle;

	}

	bool FKinectPluginCore::GetIsRightHandClosed() {

		return rightHandToggle;

	}

	void FKinectPluginCore::SetLeftHandPos(Joint leftHandPos) {

		leftHandPosContainer = leftHandPos;
	}

	void FKinectPluginCore::SetRightHandPos(Joint rightHandPos) {

		rightHandPosContainer = rightHandPos;

	}

	Joint FKinectPluginCore::GetLeftHandPos() {

		return leftHandPosContainer;
	}

	Joint FKinectPluginCore::GetRightHandPos() {

		return rightHandPosContainer;

	}


	