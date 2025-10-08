// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletProjectile.h"
#include "BuildingBlocks/HudBase.h"
#include "Components/ArrowComponent.h"
#include "GunBase.generated.h"


UCLASS()
class BUILDINGBLOCKS_API AGunBase : public AActor
{
	GENERATED_BODY()
	
public:

	
	// Sets default values for this actor's properties
	AGunBase();


	UFUNCTION(BlueprintCallable, Category=  "WeaponBs")
	virtual void setDamage(float NewDamage);// this is for setting up the health bar functions

	UFUNCTION(BlueprintCallable, Category=  "WeaponBs")
	virtual float GetDamage() const;
	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SetWeaponVisibility(bool bIsVisible);

	// Ammo functions
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	 virtual int32 GetCurrentAmmo() const;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	int32 GetMaxAmmo() const;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Reload();

	UPROPERTY(EditAnywhere, Category= "Weapon")
	TSubclassOf<class ABulletProjectile> BulletProjectile;

	virtual bool CanFire() const;

	UPROPERTY( EditDefaultsOnly , Category= "Stats")
	int32 MaxAmmo = 30;

	UPROPERTY( EditDefaultsOnly , Category= "Stats")
	int32 CurrentAmmo = 30;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Stats")
	TSubclassOf<ABulletProjectile>BulletLogic;

	UFUNCTION(BlueprintCallable, Category = "Stats")
	 virtual void Fire();

	virtual void Tick(float DeltaTime) override;
	UPROPERTY( EditDefaultsOnly , Category= "Stats")
	
	UStaticMeshComponent* WeaponMeshModel;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY( EditDefaultsOnly , Category= "Stats")
	float Damage = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UArrowComponent* ArrowComponent;

private:

	

};
