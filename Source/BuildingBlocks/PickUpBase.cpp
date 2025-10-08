// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpBase.h"

#include "characterbase.h"

FOnPickUpCollected APickUpBase::OnPickUpCollectedDelegate;
// Sets default values
APickUpBase::APickUpBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APickUpBase::BeginPlay()
{
	Super::BeginPlay();
	PickUpSphereTrigger = Cast<USphereComponent>(GetDefaultSubobjectByName("SphereCollider"));
	 if (PickUpSphereTrigger)
	 {
		 PickUpSphereTrigger -> OnComponentBeginOverlap.AddDynamic(this, &APickUpBase::OnBeginOverLap);
	 }
}

void APickUpBase::OnBeginOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Display, TEXT("PickUp triggered"))
	if (OtherActor && OtherActor != this)
	{
		if (OtherActor->ActorHasTag("AI")) // trying to only allow the player to pick up
		{
			UE_LOG(LogTemp, Warning, TEXT("Ai PickedUp"));
			// this is broadcasting that the pickup has been picked, this is usefull because player controller needs it
			Destroy();
		
		}

		if (OtherActor->IsA(Acharacterbase::StaticClass())) // trying to only allow the player to pick up
		{
			UE_LOG(LogTemp, Warning, TEXT("Player PickedUp"));
			OnPickUpCollectedDelegate.Broadcast(this);// this is broadcasting that the pickup has been picked, this is usefull because player controller needs it
			Destroy();
		
		}
		
	}
}

// Called every frame
void APickUpBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

