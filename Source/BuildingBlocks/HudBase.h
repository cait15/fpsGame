// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HudBase.generated.h"

class UGameLayoutBase;
/**
 * 
 */
UCLASS()
// this actually displays the ui into the game
class BUILDINGBLOCKS_API AHudBase : public AHUD


{
public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameLayoutBase> GameLayoutBaseClass = nullptr;
	
	void SetScore(int32 Score);
	
	void SetImage(const FSlateBrush& NewIconBrush);

	void SetHealth(int32 Health);
	void onAmmoDelegate(int32 ammoBS);
	
	void onIconUpdate(FSlateBrush iconUpdate);
	int32 ammoSet;
	FSlateBrush iconBrush;
     int32 healthSet;

	void onHealthDelegate(int32 healthbs);
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TObjectPtr<UWorld> World = nullptr;
	
	 UPROPERTY()
	TObjectPtr<UGameLayoutBase> GameLayoutWidget = nullptr;
	
	GENERATED_BODY()
};
