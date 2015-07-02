// Fill out your copyright notice in the Description page of Project Settings.

#include "PluginDevTest.h"
#include "ActorWithFunctions.h"

 //	UE_LOG(LogTemp, Warning, TEXT("MY FUNCTION WORKS!"));

// Sets default values
AActorWithFunctions::AActorWithFunctions()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AActorWithFunctions::BeginPlay()
{
	Super::BeginPlay();
	PrintOutSomeInfo();

}

// Called every frame
void AActorWithFunctions::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AActorWithFunctions::PrintOutSomeInfo() {

	UE_LOG(LogTemp, Warning, TEXT("MY FUNCTION WORKS!"));


}

FVector AActorWithFunctions::GetSomeVector() {

	return FVector(0.0f, 2.0f, 3.5f);

}