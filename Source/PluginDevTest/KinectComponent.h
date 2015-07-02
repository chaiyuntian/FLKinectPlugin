// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "KinectComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLUGINDEVTEST_API UKinectComponent : public UActorComponent
{
	GENERATED_BODY() 

public:	
	// Sets default values for this component's properties
	UKinectComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
	

	void Debug(FString Msg);

	//Method that does a draw debug to screen from c++
	UFUNCTION(BlueprintCallable, Category = "FL Kinect Functions")
		void KinectDebug();
	
	//Get Left Hand Position
	UFUNCTION(BlueprintCallable, Category = "FL Kinect Functions")
		FVector GetLeftHandPos();
	
	//Get Right Hand Position
	UFUNCTION(BlueprintCallable, Category = "FL Kinect Functions")
		FVector GetRightHandPos();
	
	//Get a bool that represents if the Left Hand is Closed
	UFUNCTION(BlueprintCallable, Category = "FL Kinect Functions")
		bool GetIsLeftHandClosed();

	//Get a bool that represents if the Right Hand is Closed
	UFUNCTION(BlueprintCallable, Category = "FL Kinect Functions")
		bool GetIsRightHandClosed();
	

};
