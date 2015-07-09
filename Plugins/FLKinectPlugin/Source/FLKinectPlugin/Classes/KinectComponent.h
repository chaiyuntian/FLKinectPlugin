// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Components/ActorComponent.h"

#include "KinectPluginCore.h"
#include "KinectComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) ) 
class FLKINECTPLUGIN_API UKinectComponent : public UActorComponent
{
	GENERATED_UCLASS_BODY()

public:	
	
	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;


	void Debug(FString Msg);

	//Method that says if our plugin is working
	UFUNCTION(BlueprintCallable, Category = "FL Kinect Debug")
		void KinectDebug();

	//Get Left Hand Position
	UFUNCTION(BlueprintCallable, Category = "FL Kinect Functions")
		FVector GetLeftHandPosition();
	
	//Get Right Hand Position
	UFUNCTION(BlueprintCallable, Category = "FL Kinect Functions")
		FVector GetRightHandPosition();
	
	//Get a bool that represents if the Left Hand is Closed
	UFUNCTION(BlueprintCallable, Category = "FL Kinect Functions")
		bool GetIsLeftHandClosed();

	//Get a bool that represents if the Right Hand is Closed
	UFUNCTION(BlueprintCallable, Category = "FL Kinect Functions")
		bool GetIsRightHandClosed();
	
	/* NOTE (MR) : Removed this until position data is working
	UFUNCTION(BlueprintCallable, Category = "FL Kinect Functions")
		FVector GetLeftWristPosition();
	Get Right Wrist Position
	UFUNCTION(BlueprintCallable, Category = "FL Kinect Functions")
		FVector GetRightWristPosition();
		*/

private:
	FKinectPluginCore* kinectInstance;

};
