// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "FLKinectPluginPrivatePCH.h"
#include "KinectPluginCore.h"
//#include "KinectComponent.generated.inl" // NOTE (MR) Added after being put into the plug in folder


class FFLKinectPlugin : public IFLKinectPlugin
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE( FFLKinectPlugin, FLKinectPlugin )


void FFLKinectPlugin::StartupModule()
{
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)
	
	
	UE_LOG(LogTemp, Warning, TEXT("Hi Mike, I'm your plugin. Treat me well"))

	//NOTE (MR) : Uncommented after (OS) changes 7.6.15
	//FKinectPluginCore* kinect = FKinectPluginCore::GetInstance();
	
}


void FFLKinectPlugin::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}



