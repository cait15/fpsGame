// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HudBase.h"
#include "GameFramework/Character.h"
#include "characterbase.generated.h"

class UCameraComponent;
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthUpdate, int32 )
UCLASS()
class BUILDINGBLOCKS_API Acharacterbase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	Acharacterbase();
// Camera component we are making
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* ArmsMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	int32 MainCharacterHealth = 100;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void UpdateHealthUi();
	static FOnHealthUpdate onHealthUpdateDelegate;

	USkeletalMeshComponent* GetArmsMesh() const;
	void UpdateArmsOrientation();

};
