// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletProjectile.generated.h"

UCLASS()
class BUILDINGBLOCKS_API ABulletProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletProjectile();

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "Shooter Info")
	FString ShooterName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Stats")
	UStaticMeshComponent* BulletMesh;

	UPROPERTY( EditDefaultsOnly , Category= "Stats")
	float Speed = 3500.0f;
	
	UPROPERTY( EditDefaultsOnly , Category= "Stats")
	float Damage = 1.0f;
	
	UPROPERTY( EditDefaultsOnly , Category= "Stats")
	UStaticMesh* BulletModel;

	void FireInDirection(const FVector& ShootDirection);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent*
	OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	class UProjectileMovementComponent* ProjectileMovement;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
