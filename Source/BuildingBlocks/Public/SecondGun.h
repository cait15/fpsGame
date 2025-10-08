// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GunBase.h"
#include "SecondGun.generated.h"

UCLASS()
class BUILDINGBLOCKS_API ASecondGun : public AGunBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASecondGun();

	virtual  bool CanFire() const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY( EditDefaultsOnly , Category= "Stats")
	UStaticMesh* GunOneModel;
};
