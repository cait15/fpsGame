// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SwitchType.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

UCLASS()
class BUILDINGBLOCKS_API ADoor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADoor();
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="0_Setup")
	TEnumAsByte<ESwitchType>DoorSwitchType = White;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="0_Setup")
	bool IsOpen = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="0_Setup")
	UMaterial* DWhiteMaterial = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="0_Setup")
	UMaterial* DCyanMaterial = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="0_Setup")
	UMaterial* DMagentaMaterial = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="0_Setup")
	UMaterial* DYellowMaterial = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	UPROPERTY()
	FVector DefaultScale = FVector(2.516526f, 1.0f,1.507088f);

	UPROPERTY()
	FVector OpenScale = FVector(0.0f,0.0f,0.0f);
	
	UPROPERTY()
	UStaticMeshComponent* DoorMesh = nullptr;
	
	UFUNCTION()
	void OnSwitchTriggeredHandler(ESwitchType TriggeredSwitchType);
	
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

#endif


};
