// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "HtmlCanvasTools.h"

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#include <cwchar>
#else
#include "Developer/Settings/Public/ISettingsModule.h"
#include "Developer/Settings/Public/ISettingsSection.h"
#include "Developer/Settings/Public/ISettingsContainer.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "CanvasTools.h"
#endif

#define LOCTEXT_NAMESPACE "FHtmlCanvasToolsModule"

void FHtmlCanvasToolsModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
    // #ifndef __EMSCRIPTEN__
    // ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
    // if (SettingsModule)
    // {
    //    TSharedPtr<ISettingsContainer> ProjectSettingsContainer = SettingsModule->GetContainer("Project");
    //    if (SettingsModule != nullptr)
    //    {
    //        SettingsModule->RegisterSettings("Project", "Platforms", "HTML5 - Canvas Tools",
    //            LOCTEXT("TargetSettingsName", "HTML5 - Canvas Tools"),
    //            LOCTEXT("TargetSettingsDescription", "Settings for HTML5 - Canvas Tools"),
    //            GetMutableDefault<UCanvasSettings>()
    //        );
    //    }
    // }
    // #endif
    // ..
    // TO ACCESS SETTINGS
    // const UExampleSettings* ExampleSettings = GetDefault<UExampleSettings>();
    // if(ExampleSettings && ExampleSettings->bTest)
    // ..
    // UCanvasTools::LogMessage("HTML5 Canvas Tools Loaded");
    UE_LOG(LogTemp, Warning, TEXT("HTML5 Canvas Tools Loaded."));
}

void FHtmlCanvasToolsModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
    // #ifndef __EMSCRIPTEN__
    // ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
    // if (SettingsModule != nullptr)
    // {
    //    SettingsModule->UnregisterSettings("Project", "Platforms", "HTML5 - Canvas Tools");
    // }
    // #endif
    // UCanvasTools::LogMessage("HTML5 Canvas Tools Unloaded");
    UE_LOG(LogTemp, Warning, TEXT("HTML5 Canvas Tools Unloaded."));
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FHtmlCanvasToolsModule, HtmlCanvasTools)
