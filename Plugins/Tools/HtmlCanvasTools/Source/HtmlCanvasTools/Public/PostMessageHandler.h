// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Core/Public/Delegates/DelegateCombinations.h"
#include "PostMessageHandler.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_NineParams(FPostMessageHandlerDelegate, FString, command, FString, param1, FString, param2, FString, param3, FString, param4, FString, param5, FString, param6, FString, param7, FString, param8);

UCLASS()
class HTMLCANVASTOOLS_API APostMessageHandler : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APostMessageHandler();
	static APostMessageHandler* Instance;

	UPROPERTY(BlueprintAssignable, Category = "Canvas Tools")
	FPostMessageHandlerDelegate OnWindowMessage;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
