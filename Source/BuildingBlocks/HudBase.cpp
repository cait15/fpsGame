// Fill out your copyright notice in the Description page of Project Settings.


#include "HudBase.h"

#include "characterbase.h"
#include "GameLayoutBase.h"
#include "Pc.h"

void AHudBase::SetScore(int32 Score)
{
	

	//GameLayoutWidget ->PickUpCounter -> SetCounterValue(Score);
	// this is grabbing the pickup counter from gameLayoutWidget and then its assigning the pickupcounter to the counterWidgets text that handles the actual counter
}

void AHudBase::SetImage(const FSlateBrush& NewIconBrush)
{
	//GameLayoutWidget ->PickUpCounter ->SetIconImageValue(NewIconBrush);
}

void AHudBase::SetHealth(int32 Health)
{
	GameLayoutWidget ->HealthCounter -> SetCounterValue(Health);
}

void AHudBase::onAmmoDelegate(int32 ammoBS)
{
	ammoSet = ammoBS;
	UE_LOG(LogTemp, Warning, TEXT("Ammo ui should show :  %d"), ammoSet);
	GameLayoutWidget ->PickUpCounter -> SetCounterValue(ammoSet);
	
}

void AHudBase::onIconUpdate(FSlateBrush iconUpdate)
{
	iconBrush = iconUpdate;
	GameLayoutWidget ->PickUpCounter ->SetIconImageValue(iconBrush);
}


void AHudBase::onHealthDelegate(int32 healthbs)
{
	healthSet = healthbs;
	GameLayoutWidget ->HealthCounter -> SetCounterValue(healthSet);
	
	
}

void AHudBase::BeginPlay()
{
	Super::BeginPlay();
	Acharacterbase::onHealthUpdateDelegate.AddUObject(this, &AHudBase::onHealthDelegate);
	APc::onScoreUpdateDelegate.AddUObject(this, &AHudBase::onAmmoDelegate);
	APc::onIconUpdateDelegate.AddUObject(this, &AHudBase::onIconUpdate);
	World = GetWorld();
	
	checkf(World, TEXT("failed to reference world"))
	
	checkf(GameLayoutBaseClass,TEXT("GameLayoutBase not specified"));\

	GameLayoutWidget = CreateWidget<UGameLayoutBase>(World, GameLayoutBaseClass);//creates the widget in class

	GameLayoutWidget -> AddToViewport();
	GameLayoutWidget->SetVisibility(ESlateVisibility::Visible);

	}
