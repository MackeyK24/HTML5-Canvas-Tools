// Fill out your copyright notice in the Description page of Project Settings.

#include "PostMessageHandler.h"

// Must Initialize Static Singleton Instance
APostMessageHandler* APostMessageHandler::Instance = nullptr;

// Sets default values
APostMessageHandler::APostMessageHandler()
{
	APostMessageHandler::Instance = this;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void APostMessageHandler::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APostMessageHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

