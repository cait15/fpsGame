// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletProjectile.h"

#include "BuildingBlocks/PickUpBase.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABulletProjectile::ABulletProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// This is creating the bullet mesh
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	BulletMesh->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	BulletMesh->SetNotifyRigidBodyCollision(true); // Enable onhit events
	RootComponent = BulletMesh;

	// Creating the Movement stuffs
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 3000.0f; // Set the initial speed
	ProjectileMovement->MaxSpeed = 3000.0f;// sets the max speed the bullet will reach
	ProjectileMovement->bRotationFollowsVelocity = true; // Rotate to follow velocity direction
	ProjectileMovement->bShouldBounce = false; // Disable bounce 
	BulletMesh->OnComponentHit.AddDynamic(this, &ABulletProjectile::OnHit);

}

void ABulletProjectile::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovement->Velocity = ShootDirection * Speed;
}

// Called when the game starts or when spawned
void ABulletProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	if (BulletMesh && BulletModel)
	{
		BulletMesh->SetStaticMesh(BulletModel);  // assigning the mesh
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("BulletMesh or BulletModel idk killed itself ig?"));
	}
	
}

void ABulletProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)// on hit function, think of unity
{

	if (OtherActor && OtherActor!= this)
	{
		if (!OtherActor->IsA(APickUpBase::StaticClass())) // this is so the bullet doesnt trigger the pickup
		{
			UE_LOG(LogTemp, Warning, TEXT("Bullet hit something other than a pickup"));
			Destroy();
		}
		
	}
}

void ABulletProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

