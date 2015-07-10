// Fill out your copyright notice in the Description page of Project Settings.

#include "FLKinectPluginPrivatePCH.h" //NOTE (MR) Added this after putting it into plugin folder! DOESN"T WORK

#include "KinectComponent.h"


UKinectComponent::UKinectComponent(class FObjectInitializer const &)
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	kinectInstance = FKinectPluginCore::GetInstance();
}

// Called when the game starts
void UKinectComponent::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UKinectComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UKinectComponent::Debug(FString Msg) {

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Cyan, Msg);
	}

}

void UKinectComponent::KinectDebug(){

	Debug("Kinect Component is Working!!");

}

FVector UKinectComponent::GetLeftHandPosition(){
	//NOTE (MR) : 7.10.15
	//Currently note in use
	return kinectInstance->LeftHandLastPosition;
	
}

FVector UKinectComponent::GetRightHandPosition(){
	//NOTE (MR) : 7.10.15
	//Currently note in use
	return kinectInstance->RightHandLastPosition;
	
}

bool UKinectComponent::GetIsLeftHandClosed(){
	//NOTE (MR) : 7.10.15
	//Currently note in use
	return kinectInstance->LeftHandLastIsClosed;
	
}

bool UKinectComponent::GetIsRightHandClosed(){
	//NOTE (MR) : 7.10.15
	//Currently note in use
	return kinectInstance->RightHandLastIsClosed;

}


/* Note (MR) : Removed this for the moment
FVector UKinectComponent::GetLeftWristPosition(){

	return kinectInstance->LeftWristLastPosition;
}

FVector UKinectComponent::GetRightWristPosition(){

	return kinectInstance->RightWristLastPosition;
}*/

