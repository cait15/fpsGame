// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "PickUpBase.generated.h"

 
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPickUpCollected, APickUpBase* pickup )
UCLASS()
class BUILDINGBLOCKS_API APickUpBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APickUpBase();

	TObjectPtr<USphereComponent> PickUpSphereTrigger = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	UFUNCTION()
	void OnBeginOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor
		, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,bool bFromSweep, const FHitResult& SweepResult
		);

	virtual void Tick(float DeltaTime) override;

	static FOnPickUpCollected OnPickUpCollectedDelegate;

private:
	//UPROPERTY()
	//UShapeComponent* TriggerShape = nullptr;
};
