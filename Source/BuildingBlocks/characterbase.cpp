// Fill out your copyright notice in the Description page of Project Settings.


#include "characterbase.h"

#include "Camera/CameraComponent.h"
#include "HudBase.h"
#include "GameFramework/CharacterMovementComponent.h"

FOnHealthUpdate Acharacterbase::onHealthUpdateDelegate;
// Sets default values
Acharacterbase::Acharacterbase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
// camera stuffs
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(RootComponent);
	CameraComponent->bUsePawnControlRotation = true; 

	// Creates the arms mesh for us, SO IT DOESNT CRASHH AND BURNNN!
	ArmsMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ArmsMesh"));
	ArmsMesh->SetupAttachment(CameraComponent);
}

// Called when the game starts or when spawned
void Acharacterbase::BeginPlay()
{
	Super::BeginPlay();
	if(GetMovementComponent())
		GetMovementComponent() -> GetNavAgentPropertiesRef().bCanCrouch = true;
	
}

// Called every frame
void Acharacterbase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateArmsOrientation();// Just so the arms follow the camera
}

// Called to bind functionality to input
void Acharacterbase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void Acharacterbase::UpdateHealthUi()
{
	onHealthUpdateDelegate.Broadcast(MainCharacterHealth);
}

USkeletalMeshComponent* Acharacterbase::GetArmsMesh() const
{
	return ArmsMesh; // this is more for our Player Controller;
}

void Acharacterbase::UpdateArmsOrientation()
{
	FRotator CameraRotation = CameraComponent->GetComponentRotation();
	ArmsMesh->SetWorldRotation(CameraRotation);
}

