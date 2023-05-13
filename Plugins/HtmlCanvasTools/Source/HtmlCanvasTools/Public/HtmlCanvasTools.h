// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "HtmlCanvasTools.generated.h"

class FHtmlCanvasToolsModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

UCLASS(config=Engine, defaultconfig)
class HTMLCANVASTOOLS_API UCanvasSettings : public UObject
{
    GENERATED_BODY()

	// ------------------------------------------------------------
	// Use HTML5 .ini files in the editor
	virtual const TCHAR* GetConfigOverridePlatform() const override
	{
		return TEXT("HTML5");
	}

    //UPROPERTY(GlobalConfig, EditAnywhere, Category="Toolchain", Meta = (DisplayName = "Classic Builds"))
    //bool EnableClassicBuilds = false;

    //UPROPERTY(GlobalConfig, EditAnywhere, Category="Toolchain", Meta = (DisplayName = "Set Project Title"))
    //FName ProjectTitle;

    //UPROPERTY(GlobalConfig, EditAnywhere, Category="Toolchain", Meta = (DisplayName = "Set Total Memory"))
    //int32 TotalMemory = 256;

    //UPROPERTY(GlobalConfig, EditAnywhere, Category="Toolchain", Meta = (DisplayName = "Set Fixed Memory"))
    //bool FixedMemory = false;

    //UPROPERTY(GlobalConfig, EditAnywhere, Category="Toolchain", Meta = (DisplayName = "Set Prewarm Timeout"))
    //int32 PrewarmTimeout = 3000;

    //UPROPERTY(GlobalConfig, EditAnywhere, Category="Toolchain", Meta = (DisplayName = "Enable Debug Asserts"))
    //bool ForceAssertions = false;

    //UPROPERTY(GlobalConfig, EditAnywhere, Category="Toolchain", Meta = (DisplayName = "Hide Full Screen Button"))
    //bool HideFullScreenButton = false;

    //UPROPERTY(GlobalConfig, EditAnywhere, Category="Toolchain", Meta = (DisplayName = "Hide Frames Per Second"))
    //bool HideFramesPerSecond = false;

    //UPROPERTY(GlobalConfig, EditAnywhere, Category="Toolchain", Meta = (DisplayName = "Use Legacy Template"))
    //bool UseLegacyTemplate = false;

    //UPROPERTY(GlobalConfig, EditAnywhere, Category="Toolchain", Meta = (DisplayName = "External Server Port"))
    //int32 ExternalServerPort = 0;
};
