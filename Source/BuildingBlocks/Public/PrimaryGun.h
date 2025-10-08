// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GunBase.h"
#include "PrimaryGun.generated.h"

UCLASS()
class BUILDINGBLOCKS_API APrimaryGun : public AGunBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APrimaryGun();
	
	virtual  bool CanFire() const override;
	
	virtual int32 GetCurrentAmmo() const override;
	virtual void Fire() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY( EditDefaultsOnly , Category= "Stats")
	UStaticMesh* GunOneModel;
};
