// Fill out your copyright notice in the Description page of Project Settings.


#include "NightSkyWTPlayerController.h"


// Sets default values
ANightSkyWTPlayerController::ANightSkyWTPlayerController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ANightSkyWTPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANightSkyWTPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

