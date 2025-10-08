#pragma once
#include "CoreMinimal.h" // adding the core
#include"SwitchType.generated.h"

UENUM(BlueprintType)// to use in blueprints


enum ESwitchType: uint8
{
	White UMETA(DisplayName = "White"),
	Cyan UMETA(DisplayName = "Cyan"),
	Magenta UMETA(DisplayName = "Magenta"),
	Yellow UMETA(DisplayName = "Yellow")
};