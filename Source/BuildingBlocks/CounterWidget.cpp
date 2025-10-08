// Fill out your copyright notice in the Description page of Project Settings.


#include "CounterWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void UCounterWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UCounterWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	UpdateWidget();
}

void UCounterWidget::UpdateWidget()
{
	if(CounterText == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("CounterText does not exsit"));
		return;
	}
	if(CounterIcon == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("CounteIcon does not exsit"));
	
		return;
	}
	CounterText->SetText(FText::AsNumber(CurrentValue));
	CounterIcon ->SetBrush(CounterIconBrush);
}

void UCounterWidget::SetCounterValue(int32 NewValue)
{
   CurrentValue = NewValue;
	UpdateWidget();
}

void UCounterWidget::SetIconImageValue(const FSlateBrush& NewIconBrush)
{
	CounterIconBrush = NewIconBrush;
	UpdateWidget();
}

void UCounterWidget::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	
		UpdateWidget();
}
