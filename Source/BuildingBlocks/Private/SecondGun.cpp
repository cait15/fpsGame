// Fill out your copyright notice in the Description page of Project Settings.


#include "SecondGun.h"

#include "BuildingBlocks/Pc.h"


class APc;
// Sets default values
ASecondGun::ASecondGun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Damage = 12.0f;
	MaxAmmo = 10;
	CurrentAmmo = MaxAmmo;
	WeaponMeshModel->SetStaticMesh(GunOneModel);

}

bool ASecondGun::CanFire() const
{
	return CurrentAmmo > 0;
}

// Called when the game starts or when spawned
void ASecondGun::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASecondGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}



