// Fill out your copyright notice in the Description page of Project Settings.

#include "PluginDevTest.h"
#include "KinectComponent.h"

//	UE_LOG(LogTemp, Warning, TEXT("My Function Works!!! Woo!"));


// Sets default values for this component's properties
UKinectComponent::UKinectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;


	// ...
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

FVector UKinectComponent::GetLeftHandPos(){

	return FVector(2.0f, 3.0f, 5.0f);
}

FVector UKinectComponent::GetRightHandPos(){

	return FVector(9.0f, 35.0f, 20.0f);
}

bool UKinectComponent::GetIsLeftHandClosed(){

	return true;
}

bool UKinectComponent::GetIsRightHandClosed(){

	return false;
}
