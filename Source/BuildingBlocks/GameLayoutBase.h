// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CounterWidget.h"
#include "WidgetBase.h"
#include "GameLayoutBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
// this is to bound it
// this is the main canvas in game(ui) use this to bound the health ui stuff
class BUILDINGBLOCKS_API UGameLayoutBase : public UWidgetBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly,Category="Bound Widget", meta=(BindWidget))
	TObjectPtr<UCounterWidget> PickUpCounter = nullptr;
	
	UPROPERTY(BlueprintReadOnly,Category="Bound Widget", meta=(BindWidget))
	TObjectPtr<UCounterWidget> HealthCounter= nullptr;
};
