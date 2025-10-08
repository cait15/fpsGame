// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SwitchType.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Switch.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FOnSwitchTriggeredSignature, ESwitchType)// triggered switch type
UCLASS()
class BUILDINGBLOCKS_API ASwitch : public AActor
{
	GENERATED_BODY()

public:
	ASwitch();
	static FOnSwitchTriggeredSignature OnSwitchTriggeredDelegate; // static means we can access it through the class name instead of needing an instance
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="0_Setup")
	UBoxComponent* BoxTrigger = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="0_Setup")
	UMaterial* WhiteMaterial = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="0_Setup")
	UMaterial* CyanMaterial = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="0_Setup")
	UMaterial* MagentaMaterial = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="0_Setup")
	UMaterial* YellowMaterial = nullptr;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="0_Setup")
	TEnumAsByte<ESwitchType>SwitchType = White;

	UFUNCTION()
	void OnBeginOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor
		, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,bool bFromSweep, const FHitResult& SweepResult
		);

protected:
	virtual void BeginPlay() override;
private:
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

#endif
	
};

