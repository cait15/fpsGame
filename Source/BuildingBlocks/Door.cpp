// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

#include "Switch.h"

// if this code is being used for display purposes, do note that Jacob's, Nj's and Erin's unreal/rider blew up hence the code is on my pc :D
// BUT WE DID IT TOGETHER !!! POWER OF FRIENDSHIP YAHHHH!!!
// HENK WE DID PAIR PROGRAMMING, BE PROUD 
// Sets default values
ADoor::ADoor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	DoorMesh = Cast<UStaticMeshComponent>(GetDefaultSubobjectByName("DoorStaticMesh"));

	ASwitch::OnSwitchTriggeredDelegate.AddUObject(this, &ADoor::OnSwitchTriggeredHandler);// this subsribes the event to a method, think of on disable and on enable
	
}

void ADoor::OnSwitchTriggeredHandler(ESwitchType TriggeredSwitchType)
{
	if(TriggeredSwitchType != DoorSwitchType.GetValue())
		return;

	IsOpen = !IsOpen; // coz we triggering(by passing through the gate/frame) it we need to switch it around

	if(IsOpen)
	{
		//DoorMesh->SetActive(false);

		DoorMesh->SetRelativeScale3D(OpenScale);
		DoorMesh->SetCollisionEnabled((ECollisionEnabled::NoCollision));
	}
	else
	{
		//DoorMesh->SetActive(true);

		DoorMesh->SetRelativeScale3D(DefaultScale);
		DoorMesh->SetCollisionEnabled((ECollisionEnabled::QueryAndPhysics));
	}
}
#if WITH_EDITOR
void ADoor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	DoorMesh = Cast<UStaticMeshComponent>(GetDefaultSubobjectByName("DoorStaticMesh"));

	if(DoorMesh == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Door Mesh does not exsit"));
		return;
	}

	FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName(): NAME_None;

	if ( PropertyName == GET_MEMBER_NAME_CHECKED(ADoor, DoorSwitchType))
	{
		ESwitchType SwitchTypeEnum = DoorSwitchType.GetValue();

		if(SwitchTypeEnum == White)
		{ 
			DoorMesh ->SetMaterial(0, DWhiteMaterial);
			
		}
		if(SwitchTypeEnum == Cyan)
		{
			DoorMesh ->SetMaterial(0, DCyanMaterial);
			
		}
		if(SwitchTypeEnum == Magenta)
		{
			DoorMesh->SetMaterial(0, DMagentaMaterial);
			
		}
		if(SwitchTypeEnum == Yellow)
		{
			DoorMesh ->SetMaterial(0, DYellowMaterial);
			
		}
		
	}
	if ( PropertyName == GET_MEMBER_NAME_CHECKED(ADoor, IsOpen))
	{

		//IsOpen = !IsOpen; Dont need this, it fks it up

		if(IsOpen)
		{
			
			DoorMesh->SetRelativeScale3D(OpenScale);
			DoorMesh->SetCollisionEnabled((ECollisionEnabled::NoCollision));
		}
		else
		{
			
			DoorMesh->SetRelativeScale3D(DefaultScale);
			DoorMesh->SetCollisionEnabled((ECollisionEnabled::QueryAndPhysics));
		}
		
	}
	
}
#endif



