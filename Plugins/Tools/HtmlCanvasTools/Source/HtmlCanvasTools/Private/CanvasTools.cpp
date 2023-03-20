#include "CanvasTools.h"
#include "PostMessageHandler.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"

#ifdef __EMSCRIPTEN__
#define PLATFORM_HTML5_BROWSER 1
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#include <cwchar>
#else
#define EM_ASM(x)
#define EM_ASM_(...)
#define EM_ASM_ARGS(...)
#define MAIN_THREAD_ASYNC_EM_ASM(...)
#define EMSCRIPTEN_KEEPALIVE
#endif

/* ************************ */
/* Toolkit Plugin Functions */
/* ************************ */

UCanvasTools::UCanvasTools(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    UCanvasTools::InitTools();
}

void UCanvasTools::InitTools()
{
#ifdef PLATFORM_HTML5_BROWSER

    EM_ASM(
    {

        console.warn("HTML5 Canvas Tools Initialized.");

    });

#else
    UE_LOG(LogTemp, Display, TEXT("HTML5 Canvas Tools Initialized."));
#endif
}

void UCanvasTools::LoadSceneGroup(FString scene)
{
#ifdef PLATFORM_HTML5_BROWSER

    MAIN_THREAD_EM_ASM(
    {

        var gameWindowUrl = (Module.UTF8ToString($0) + ".html" + window.location.search);
        window.location.replace(gameWindowUrl);

    }, TCHAR_TO_UTF8(*scene));

#else
    UCanvasTools::TravelToLevel(scene, true);
#endif
}

void UCanvasTools::TravelToLevel(FString level, bool bTravelAbsolute)
{
    UWorld* world = nullptr;
    // ..
    // TODO: Better Way To Get Current World
    // ..
    if (GEngine)
    {
        TArray<APlayerController*> Players;
        GEngine->GetAllLocalPlayerControllers(Players);
        if (Players.Num())
        {
            world = Players[0]->GetWorld();
        }
    }
    if (world != nullptr)
    {
        UGameplayStatics::OpenLevel(world, FName(*level), bTravelAbsolute);
    }
    else
    {
        UCanvasTools::LogError("Open level failed to locate default world conext");
    }
}

void UCanvasTools::PrintToScreen(FString message, int key, float timeout, FColor color)
{
    if (GEngine) GEngine->AddOnScreenDebugMessage(key, timeout, color, message);
}

void UCanvasTools::LogMessage(FString message, bool UE_Logging)
{
#ifdef PLATFORM_HTML5_BROWSER
    if (UE_Logging == true)
    {
        UE_LOG(LogTemp, Display, TEXT("%s"), *message);
    }
    else
    {
        EM_ASM(
        {

            console.log(Module.UTF8ToString($0));

        }, TCHAR_TO_UTF8(*message));
    }
#else
    UE_LOG(LogTemp, Display, TEXT("%s"), *message);
#endif
}

void UCanvasTools::LogWarning(FString message, bool UE_Logging)
{
#ifdef PLATFORM_HTML5_BROWSER
    if (UE_Logging == true)
    {
        UE_LOG(LogTemp, Warning, TEXT("%s"), *message);
    }
    else
    {
        EM_ASM(
        {

            console.warn(Module.UTF8ToString($0));

        }, TCHAR_TO_UTF8(*message));
    }
#else
    UE_LOG(LogTemp, Warning, TEXT("%s"), *message);
#endif
}

void UCanvasTools::LogError(FString message, bool UE_Logging)
{
#ifdef PLATFORM_HTML5_BROWSER
    if (UE_Logging == true)
    {
        UE_LOG(LogTemp, Error, TEXT("%s"), *message);
    }
    else
    {
        EM_ASM(
        {

            console.error(Module.UTF8ToString($0));

        }, TCHAR_TO_UTF8(*message));
    }
#else
    UE_LOG(LogTemp, Error, TEXT("%s"), *message);
#endif
}

FString UCanvasTools::GetUrlParameter(FString name)
{
    char* result = nullptr;

#ifdef PLATFORM_HTML5_BROWSER

    result = (char*)MAIN_THREAD_EM_ASM_INT(
    {

        return window.getUrlParameter(Module.UTF8ToString($0));

    }, TCHAR_TO_UTF8(*name));

#else
    UE_LOG(LogTemp, Display, TEXT("NATIVE: GET URL PARAMETER"));
#endif

    if (result != nullptr)
    {
        FString item(ANSI_TO_TCHAR(result));
        free(result);
        return item;
    }
    else
    {
        return FString();
    }
}

FString UCanvasTools::GetUrlQueryString()
{
    char* result = nullptr;

#ifdef PLATFORM_HTML5_BROWSER

    result = (char*)MAIN_THREAD_EM_ASM_INT(
    {
        return window.getUrlQueryString();
    });

#else
    UE_LOG(LogTemp, Display, TEXT("NATIVE: GET URL QUERY STRING"));
#endif

    if (result != nullptr)
    {
        FString item(ANSI_TO_TCHAR(result));
        free(result);
        return item;
    }
    else
    {
        return FString();
    }
}

void UCanvasTools::PostWindowMessage(FString command, FString param1, FString param2, FString param3, FString param4, FString param5, FString param6, FString param7, FString param8, FString sourceKey, FString targetOrigin, EBrowserWindow browserWindow)
{
    UCanvasTools::InternalProcessWindowMessage(command, param1, param2, param3, param4, param5, param6, param7, param8, sourceKey, targetOrigin, (int)browserWindow);
}

FString UCanvasTools::GetLocalStorageItem(FString key, EBrowserWindow browserWindow)
{
    return UCanvasTools::InternalGetLocalStorageItem(key, (int)browserWindow);
}

void UCanvasTools::SetLocalStorageItem(FString key, FString value, EBrowserWindow browserWindow)
{
    UCanvasTools::InternalSetLocalStorageItem(key, value, (int)browserWindow);
}

FString UCanvasTools::GetSessionStorageItem(FString key, EBrowserWindow browserWindow)
{
    return UCanvasTools::InternalGetSessionStorageItem(key, (int)browserWindow);
}

void UCanvasTools::SetSessionStorageItem(FString key, FString value, EBrowserWindow browserWindow)
{
    UCanvasTools::InternalSetSessionStorageItem(key, value, (int)browserWindow);
}

void UCanvasTools::ExecuteConsoleCommand(FString command)
{
    if (GEngine)
    {
        TArray<APlayerController*> Players;
        GEngine->GetAllLocalPlayerControllers(Players);
        if (Players.Num())
        {
            Players[0]->ConsoleCommand(command);
        }
    }
}

/* ************************** */
/* Internal Message Functions */
/* ************************** */

FString UCanvasTools::InternalGetLocalStorageItem(FString key, int browserWindow)
{
    char* result = nullptr;

#ifdef PLATFORM_HTML5_BROWSER

    result = (char*)MAIN_THREAD_EM_ASM_INT(
    {

        return window.getLocalStorageItem(Module.UTF8ToString($0), $1);

    }, TCHAR_TO_UTF8(*key), browserWindow);

#else
    UE_LOG(LogTemp, Display, TEXT("NATIVE: INTERNAL GET LOCAL STORAGE ITEM"));
#endif

    if (result != nullptr)
    {
        FString item(ANSI_TO_TCHAR(result));
        free(result);
        return item;
    }
    else
    {
        return FString();
    }
}

void UCanvasTools::InternalSetLocalStorageItem(FString key, FString value, int browserWindow)
{
#ifdef PLATFORM_HTML5_BROWSER

    MAIN_THREAD_EM_ASM(
    {

        window.setLocalStorageItem(Module.UTF8ToString($0), Module.UTF8ToString($1), $2);

    }, TCHAR_TO_UTF8(*key), TCHAR_TO_UTF8(*value), browserWindow);

#else
    UE_LOG(LogTemp, Display, TEXT("NATIVE: INTERNAL SET LOCAL STORAGE ITEM"));
#endif
}

FString UCanvasTools::InternalGetSessionStorageItem(FString key, int browserWindow)
{
    char* result = nullptr;

#ifdef PLATFORM_HTML5_BROWSER

    result = (char*)MAIN_THREAD_EM_ASM_INT(
    {

        return window.getSessionStorageItem(Module.UTF8ToString($0), $1);

    }, TCHAR_TO_UTF8(*key), browserWindow);

#else
    UE_LOG(LogTemp, Display, TEXT("NATIVE: INTERNAL GET SESSION STORAGE ITEM"));
#endif

    if (result != nullptr)
    {
        FString item(ANSI_TO_TCHAR(result));
        free(result);
        return item;
    }
    else
    {
        return FString();
    }
}

void UCanvasTools::InternalSetSessionStorageItem(FString key, FString value, int browserWindow)
{
#ifdef PLATFORM_HTML5_BROWSER

    MAIN_THREAD_EM_ASM(
    {

        window.setSessionStorageItem(Module.UTF8ToString($0), Module.UTF8ToString($1), $2);

    }, TCHAR_TO_UTF8(*key), TCHAR_TO_UTF8(*value), browserWindow);

#else
    UE_LOG(LogTemp, Display, TEXT("NATIVE: INTERNAL SET SESSION STORAGE ITEM"));
#endif
}

void UCanvasTools::InternalProcessWindowMessage(FString command, FString param1, FString param2, FString param3, FString param4, FString param5, FString param6, FString param7, FString param8, FString sourceKey, FString targetOrigin, int browserWindow)
{
    FString message = FString::Printf(TEXT("{ \"source\":\"%s\", \"command\":\"%s\", \"param1\":\"%s\", \"param2\":\"%s\", \"param3\":\"%s\", \"param4\":\"%s\", \"param5\":\"%s\", \"param6\":\"%s\", \"param7\":\"%s\", \"param8\":\"%s\" }"), *sourceKey, *command, *param1, *param2, *param3, *param4, *param5, *param6, *param7, *param8);

#ifdef PLATFORM_HTML5_BROWSER

    MAIN_THREAD_EM_ASM(
    {

        window.parseWindowMessage(Module.UTF8ToString($0), Module.UTF8ToString($1), $2);

    }, TCHAR_TO_UTF8(*message), TCHAR_TO_UTF8(*targetOrigin), browserWindow);

#else
    UE_LOG(LogTemp, Warning, TEXT("POST WINDOW MESSAGE: %s"), *message);
#endif
}

void UCanvasTools::InternalBroadcastWindowMessage(FString command, FString param1, FString param2, FString param3, FString param4, FString param5, FString param6, FString param7, FString param8)
{
    if (APostMessageHandler::Instance != nullptr)
    {
        APostMessageHandler::Instance->OnWindowMessage.Broadcast(command, param1, param2, param3, param4, param5, param6, param7, param8);
    }
    else
    {
        UE_LOG(LogTemp, Display, TEXT("Warning: Null Static Post Message Handler Instance Encountered."));
    }
}

/* ************************ */
/* Browser Module Functions */
/* ************************ */

#ifdef PLATFORM_HTML5_BROWSER

extern "C" void EMSCRIPTEN_KEEPALIVE PrintToScreen0(char* message, int key, float timeout, char* hexcolor)
{
    FString inputString(message);       // Note: This converts the char* message from JavaScript to a UE4 FString
    FString inputHexColor(hexcolor);    // Note: This converts the char* hexcolor from JavaScript to a UE4 FString
    UCanvasTools::PrintToScreen(inputString, key, timeout, FColor::FromHex(inputHexColor));
}

extern "C" void EMSCRIPTEN_KEEPALIVE DispatchWindowMessage0(char* command, char* param1, char* param2, char* param3, char* param4, char* param5, char* param6, char* param7, char* param8)
{
    FString inputString(command);       // Note: This converts the char* command from JavaScript to a UE4 FString
    FString paramString1(param1);       // Note: This converts the char* param1 from JavaScript to a UE4 FString
    FString paramString2(param2);       // Note: This converts the char* param2 from JavaScript to a UE4 FString
    FString paramString3(param3);       // Note: This converts the char* param3 from JavaScript to a UE4 FString
    FString paramString4(param4);       // Note: This converts the char* param4 from JavaScript to a UE4 FString
    FString paramString5(param5);       // Note: This converts the char* param5 from JavaScript to a UE4 FString
    FString paramString6(param6);       // Note: This converts the char* param6 from JavaScript to a UE4 FString
    FString paramString7(param7);       // Note: This converts the char* param7 from JavaScript to a UE4 FString
    FString paramString8(param8);       // Note: This converts the char* param8 from JavaScript to a UE4 FString
    UCanvasTools::InternalBroadcastWindowMessage(inputString, paramString1, paramString2, paramString3, paramString4, paramString5, paramString6, paramString7, paramString8);
}
#endif
