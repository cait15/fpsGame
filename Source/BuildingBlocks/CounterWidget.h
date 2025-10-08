// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WidgetBase.h"
#include "CounterWidget.generated.h"

class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS()
class BUILDINGBLOCKS_API UCounterWidget : public UWidgetBase
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativePreConstruct() override;

	UPROPERTY(BlueprintReadOnly, Category="BoundWidgets", meta=(BindWidget))
	TObjectPtr<UImage> CounterIcon = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="BoundWidgets", meta=(BindWidget))
	TObjectPtr<UTextBlock> CounterText = nullptr;

private:
	UPROPERTY(EditAnywhere, Category="0_Setup")
	FSlateBrush CounterIconBrush;

	UPROPERTY(EditAnywhere, Category="0_Setup")
	int32 CurrentValue = 0;

	void UpdateWidget();
public:
	void SetCounterValue(int32 NewValue);

	UFUNCTION(BlueprintCallable, Category = "Counter")
	void SetIconImageValue(const FSlateBrush& NewIconBrush);

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

#endif

};
