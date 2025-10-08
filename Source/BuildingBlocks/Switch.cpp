// Fill out your copyright notice in the Description page of Project Settings.


#include "Switch.h"
 FOnSwitchTriggeredSignature ASwitch:: OnSwitchTriggeredDelegate;

// Sets default values
ASwitch::ASwitch()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ASwitch::OnBeginOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Display, TEXT("Switch triggered"))
	ESwitchType SwitchTypeEnum = SwitchType.GetValue();
	OnSwitchTriggeredDelegate.Broadcast(SwitchTypeEnum);// this is essentially saving what color the frame is and then broadcasting it, for instance, if we save the gate to be cyan, this will now say okay the frame is cyan and make it available for any other scrips that need to use it
}

void ASwitch::BeginPlay()
{
	Super::BeginPlay();
	BoxTrigger = Cast<UBoxComponent>(GetDefaultSubobjectByName("BoxCollider"));
	if(BoxTrigger)
	{
		BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &ASwitch::OnBeginOverLap );
	} //& means dereferencing
}
#if WITH_EDITOR
void ASwitch::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	UStaticMeshComponent* SwitchMesh = Cast<UStaticMeshComponent>(GetDefaultSubobjectByName("SwitchMesh"));// most things will be pointers with the exception of ints and basic other variables
	if (SwitchMesh == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Switch Mesh does not exsit"));
		return;
	}
	FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName(): NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(ASwitch, SwitchType))
	{
		ESwitchType SwitchTypeEnum = SwitchType.GetValue();
		if(SwitchTypeEnum == White)
		{
			SwitchMesh ->SetMaterial(0, WhiteMaterial);
		}
		if(SwitchTypeEnum == Cyan)
		{
			SwitchMesh ->SetMaterial(0, CyanMaterial);
		}
		if(SwitchTypeEnum == Magenta)
		{
			SwitchMesh ->SetMaterial(0, MagentaMaterial);
		}
		if(SwitchTypeEnum == Yellow)
		{
			SwitchMesh ->SetMaterial(0, YellowMaterial);
		}
	}
}
#endif


// Called when the game starts or when spawned


