#pragma once

#include "Engine.h"
#include "Browser.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CanvasTools.generated.h"

/*
*    Function library class.
*    Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*    When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*    BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*    BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*    DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*                Its lets you name the node using characters not allowed in C++ function names.
*    CompactNodeTitle - the word(s) that appear on the node.
*    Keywords -    the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu.
*                Good example is "Print String" node which you can find also by using keyword "log".
*    Category -    the category your node will be under in the Blueprint drop-down menu.
*
*    For more info on custom blueprint nodes visit documentation:
*    https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/


UCLASS()
class HTMLCANVASTOOLS_API UCanvasTools : public UBlueprintFunctionLibrary
{
    GENERATED_UCLASS_BODY()
    
public:

    static void InitTools();

    UFUNCTION(BlueprintCallable, meta = (DisplayName = "Load Scene Group", Keywords = "Html Canvas Tools"), Category = "Canvas Tools")
        static void LoadSceneGroup(FString scene);

    UFUNCTION(BlueprintCallable, meta = (DisplayName = "Travel To Level", Keywords = "Html Canvas Tools"), Category = "Canvas Tools")
        static void TravelToLevel(FString level, bool bTravelAbsolute = true);

    UFUNCTION(BlueprintCallable, meta = (DisplayName = "Print To Screen", Keywords = "Html Canvas Tools", AdvancedDisplay = "1"), Category = "Canvas Tools")
        static void PrintToScreen(FString message, int key = -1, float timeout = 30.0f, FColor color = FColor::White);

    UFUNCTION(BlueprintCallable, meta = (DisplayName = "Log Message", Keywords = "Html Canvas Tools", AdvancedDisplay = "1"), Category = "Canvas Tools")
        static void LogMessage(FString message, bool UE_Logging = true);

    UFUNCTION(BlueprintCallable, meta = (DisplayName = "Log Warning", Keywords = "Html Canvas Tools", AdvancedDisplay = "1"), Category = "Canvas Tools")
        static void LogWarning(FString message, bool UE_Logging = true);

    UFUNCTION(BlueprintCallable, meta = (DisplayName = "Log Error", Keywords = "Html Canvas Tools", AdvancedDisplay = "1"), Category = "Canvas Tools")
        static void LogError(FString message, bool UE_Logging = true);

    UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Url Parameter", Keywords = "Html Canvas Tools", AdvancedDisplay = "1"), Category = "Canvas Tools")
        static FString GetUrlParameter(FString name);

    UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Query String", Keywords = "Html Canvas Tools", AdvancedDisplay = "1"), Category = "Canvas Tools")
        static FString GetUrlQueryString();

    UFUNCTION(BlueprintCallable, meta = (DisplayName = "Post Window Message", Keywords = "Html Canvas Tools", AdvancedDisplay = "1"), Category = "Canvas Tools")
        static void PostWindowMessage(FString command, FString param1, FString param2, FString param3, FString param4, FString param5, FString param6, FString param7, FString param8, FString sourceKey = "unreal", FString targetOrigin = "*", EBrowserWindow browserWindow = EBrowserWindow::Local);

    UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Local Storage Item", Keywords = "Html Canvas Tools"), Category = "Canvas Tools")
        static FString GetLocalStorageItem(FString key, EBrowserWindow browserWindow = EBrowserWindow::Local);

    UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Local Storage Item", Keywords = "Html Canvas Tools"), Category = "Canvas Tools")
        static void SetLocalStorageItem(FString key, FString value, EBrowserWindow browserWindow = EBrowserWindow::Local);

    UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Session Storage Item", Keywords = "Html Canvas Tools"), Category = "Canvas Tools")
        static FString GetSessionStorageItem(FString key, EBrowserWindow browserWindow = EBrowserWindow::Local);

    UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Session Storage Item", Keywords = "Html Canvas Tools"), Category = "Canvas Tools")
        static void SetSessionStorageItem(FString key, FString value, EBrowserWindow browserWindow = EBrowserWindow::Local);

    UFUNCTION(BlueprintCallable, meta = (DisplayName = "Execute Console Command", Keywords = "Html Canvas Tools"), Category = "Canvas Tools")
        static void ExecuteConsoleCommand(FString command);

    // Internal Broadcast Window Message Event
    static void InternalBroadcastWindowMessage(FString command, FString param1, FString param2, FString param3, FString param4, FString param5, FString param6, FString param7, FString param8);

private:

    // Private Internal Get Local Storage Item
    static FString InternalGetLocalStorageItem(FString key, int browserWindow = 0);

    // Private Internal Get Local Storage Item
    static void InternalSetLocalStorageItem(FString key, FString value, int browserWindow = 0);

    // Private Internal Get Session Storage Item
    static FString InternalGetSessionStorageItem(FString key, int browserWindow = 0);

    // Private Internal Get Session Storage Item
    static void InternalSetSessionStorageItem(FString key, FString value, int browserWindow = 0);

    // Private Internal Post Window Message Event
    static void InternalProcessWindowMessage(FString command, FString param1, FString param2, FString param3, FString param4, FString param5, FString param6, FString param7, FString param8, FString sourceKey = "unreal", FString targetOrigin = "*", int browserWindow = 0);
};
