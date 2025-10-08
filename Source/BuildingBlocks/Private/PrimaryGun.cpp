// Fill out your copyright notice in the Description page of Project Settings.


#include "PrimaryGun.h"


// Sets default values
APrimaryGun::APrimaryGun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Damage = 3.0f;
	MaxAmmo = 69;
	CurrentAmmo = MaxAmmo;
	WeaponMeshModel->SetStaticMesh(GunOneModel);
	
}

bool APrimaryGun::CanFire() const
{
	
	return true;
}

int32 APrimaryGun::GetCurrentAmmo() const
{
	return  MaxAmmo;
}

void APrimaryGun::Fire()
{
	Super::Fire();
	CurrentAmmo = MaxAmmo;
}

// Called when the game starts or when spawned
void APrimaryGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APrimaryGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

