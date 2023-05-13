#pragma once

#include "Engine.h"

UENUM(BlueprintType)
enum class EBrowserWindow : uint8 {
    Local       UMETA(DisplayName = "Local"),
    Parent      UMETA(DisplayName = "Parent"),
    Top         UMETA(DisplayName = "Top"),
};
