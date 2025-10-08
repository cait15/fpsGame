// Fill out your copyright notice in the Description page of Project Settings.


#include "GunBase.h"

#include "BuildingBlocks/HudBase.h"

// Sets default values
AGunBase::AGunBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WeaponMeshModel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	RootComponent = WeaponMeshModel;
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
    // please please please, this is so important, if you dont initialize certain things, it crashes and burns omfg
	// this attaches the arrow to the gun model, it becomes a child... idk why the socket didnt work but this was my other solution
	ArrowComponent->SetupAttachment(WeaponMeshModel); 
	CurrentAmmo = MaxAmmo;
}

void AGunBase::setDamage(float NewDamage)
{
	Damage = NewDamage;
}

float AGunBase::GetDamage() const
{
	return Damage;
}

void AGunBase::SetWeaponVisibility(bool bIsVisible)
{
	WeaponMeshModel -> SetVisibility(bIsVisible);
}

int32 AGunBase::GetCurrentAmmo() const
{
	return CurrentAmmo;
}

int32 AGunBase::GetMaxAmmo() const
{
	return MaxAmmo;
}

void AGunBase::Reload()
{
	CurrentAmmo = MaxAmmo;
}

bool AGunBase::CanFire() const
{
	return CurrentAmmo >0;
}

void AGunBase::Fire()
{
	if (CurrentAmmo > 0 && BulletLogic)
	{

		

		// Get the shooter name from the Blueprint's variable
		
		UWorld* World = GetWorld();
		if (World)
		{
			FVector MuzzleLocation = ArrowComponent->GetComponentLocation(); // Arrows world location, bullet knows where to spawn
			FRotator MuzzleRotation = ArrowComponent->GetComponentRotation(); // Arrows  world rotation, bullet knows where to rotate im assuming?

			
			// Spawn parameters
			FActorSpawnParameters SpawnParams;
			SpawnParams.Instigator = GetInstigator(); // The instigator is the one causing the death

			// Explicitly set the Owner
			AActor* OwnerActor = GetOwner(); // Get the owner actor , might be player or ai
			if (OwnerActor)
			{
				SpawnParams.Owner = OwnerActor; // Assigning the owner
			//	UE_LOG(LogTemp, Warning, TEXT("Owner Actor: %s"), *OwnerActor->GetName());  
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Owner is null!"));
			}

			// Spawns the bullet
			ABulletProjectile* Bullet = GetWorld()->SpawnActor<ABulletProjectile>(
				BulletLogic, MuzzleLocation, MuzzleRotation, SpawnParams);

			if (Bullet)
			{
				// Set the owner of the bullet
				Bullet->SetOwner(OwnerActor);
				Bullet->ShooterName = OwnerActor->GetName();
				//UE_LOG(LogTemp, Warning, TEXT("Shooter Name: %s"), *Bullet->ShooterName);
			}

				// Fire the bullet
				Bullet->FireInDirection(MuzzleRotation.Vector());
				 // Uses the rotation to determine the direction
			}
			

			// Decreases ammo count
			CurrentAmmo--;
		}
	}


// Called when the game starts or when spawned
void AGunBase::BeginPlay()
{
	Super::BeginPlay();
}
// Called every frame
void AGunBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/* Debug the muzzle location every tick
	if (ArrowComponent)
	{
		FVector ArrowLocation = ArrowComponent->GetComponentLocation();
		//FVector ArrowDirection = ArrowComponent->GetForwardVector() * 100.0f; // Adjust length as needed

		// Draw a debug line pointing in the direction of the arrow
		//DrawDebugLine(GetWorld(), ArrowLocation, ArrowLocation + ArrowDirection, FColor::Red, false, -1, 0, 2);

		// Draw a debug sphere at the arrow's location
		DrawDebugSphere(GetWorld(), ArrowLocation, 10.0f, 12, FColor::Green, false, -1, 0, 2); // 10.0f is the radius
	}*///God why does coding have to be so stressfull!! ignore this, this is for debugging purposes
	}
		
	



