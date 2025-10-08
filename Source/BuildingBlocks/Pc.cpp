// Fill out your copyright notice in the Description page of Project Settings.


#include "Pc.h"
#include "EnhancedInputComponent.h"
#include "characterbase.h"
#include "EnhancedInputSubsystems.h"
#include "HudBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

FOnScoreUpdate APc::onScoreUpdateDelegate;
FOnIconUpdate APc::onIconUpdateDelegate;
void APc::BeginPlay()
{
	Super::BeginPlay();

	APickUpBase::OnPickUpCollectedDelegate.AddUObject(this, &APc::OnPickupCollectedHandler);
	PlayerName = TEXT("PlayerOne");
	//PlayerHud = Cast<AHudBase>(GetHUD());
	IsSecondaryWeaponUnlocked = false;
	GetWorld()->GetTimerManager().SetTimer(EquipWeaponTimerHandle, this, &APc::EquipPrimaryWeapon, 0.1f, false);
	GetWorld()->GetTimerManager().SetTimer(SetHealthTimer, this, &APc::SetHealth, 0.2f, false);


	UCharacterMovementComponent* CharacterMovement = Playercharacter->GetCharacterMovement();
	if (CharacterMovement)
	{
		// Ensure proper speed is set when the game starts
		CharacterMovement->MaxWalkSpeed = WalkSpeed;  // Set default walk speed
	}
}
void APc::HandleMove(const FInputActionValue& InputActionValue)
{
	const FVector2D MoveVector = InputActionValue.Get<FVector2D>();
	UCharacterMovementComponent* CharacterMovement = Playercharacter->GetCharacterMovement();

	float SpeedMultiplier = IsSprinting ? SprintSpeed : WalkSpeed;  // Toggling my sprint or normal walk speed
	CharacterMovement->MaxWalkSpeed = SpeedMultiplier;
	
	if (!MoveVector.IsNearlyZero())  // Just a check  if there is movement input
	{
		// Forward and Right movement based on input vector
		Playercharacter->AddMovementInput(Playercharacter->GetActorForwardVector(), MoveVector.Y);
		Playercharacter->AddMovementInput(Playercharacter->GetActorRightVector(), MoveVector.X);
	}

	// Debug to check the current speed
	//UE_LOG(LogTemp, Warning, TEXT("Speed Multiplier (MaxWalkSpeed): %f"), CharacterMovement->MaxWalkSpeed);
}

void APc::HandeJump()
{
	Playercharacter-> UnCrouch();
	Playercharacter-> Jump();
	
}

void APc::HandleSneak()
{
		Playercharacter-> Crouch();
		IsCrouching = true;
}

void APc::HandleUnsneak()
{
	if(IsCrouching == true)
	{
		Playercharacter-> UnCrouch();
		IsCrouching = false;
	}
}

void APc::HandleUnsprint()
{
	if(IsSprinting == true)
	{
		IsSprinting = false;
	}
}

void APc::HandeLook(const FInputActionValue& InputActionValue)
{
	const FVector2d LookVector = InputActionValue.Get<FVector2d>();

	AddYawInput(LookVector.X);
	AddPitchInput(LookVector.Y);
}

void APc::HandleSprint()
{
		IsSprinting = true;
}

void APc::EquipPrimaryWeapon()
{
	
	if (PrimaryWeaponClass)
	{
		// If there's a weapon already equipped, sets it to invisable
		if (CurrentWeaponEquipped)
		{
			CurrentWeaponEquipped->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			CurrentWeaponEquipped->SetWeaponVisibility(false);
			
		}
		if (!PrimaryWeaponInstance)// if theres no instance of it
		{
			PrimaryWeaponInstance = GetWorld()->SpawnActor<AGunBase>(PrimaryWeaponClass);
		}
		
		if (PrimaryWeaponInstance)
		{
			PrimaryWeaponInstance->SetOwner(this);
			if (SecondaryWeaponInstance)
			{
				// idk for some odd reason the instance of the gun stays visable even tho im setting it to invis, so im quite literally chucking it to hell
				SecondaryWeaponInstance->SetWeaponVisibility(false);
				FVector HiddenLocation = FVector(-10000.0f, -10000.0f, -10000.0f);
				SecondaryWeaponInstance->SetActorLocation(HiddenLocation);
			}

			// this is attaching the weapon to the players arm
			PrimaryWeaponInstance->SetWeaponVisibility(true);
			AttachWeaponToHand(PrimaryWeaponInstance, "GripPoint");
			CurrentWeaponEquipped = PrimaryWeaponInstance;
			updateAmmoUi();
			//PlayerHud ->SetScore(PrimaryWeaponInstance ->GetCurrentAmmo());// updates the ammo
		}
	}
	}
		
	


void APc::EquipSecondaryWeapon()
{
	//follows the same logic as the primary weapon
	if (SecondaryWeaponClass && IsSecondaryWeaponUnlocked)
	{
		updateAmmoUi();
		//PlayerHud ->SetImage(GunIcon2);
		
		if (CurrentWeaponEquipped)
		{
			CurrentWeaponEquipped->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			CurrentWeaponEquipped->SetWeaponVisibility(false);
		}

	
		if (!SecondaryWeaponInstance && IsSecondaryWeaponUnlocked)
		{
			SecondaryWeaponInstance = GetWorld()->SpawnActor<AGunBase>(SecondaryWeaponClass);
		}
		
		if (SecondaryWeaponInstance && IsSecondaryWeaponUnlocked)
		{
			SecondaryWeaponInstance->SetOwner(this);
			if (PrimaryWeaponInstance)
			{
				PrimaryWeaponInstance->SetWeaponVisibility(false);
				FVector HiddenLocation = FVector(-10000.0f, -10000.0f, -10000.0f);
				PrimaryWeaponInstance->SetActorLocation(HiddenLocation);
			}
			
			SecondaryWeaponInstance->SetWeaponVisibility(true);
			AttachWeaponToHand(SecondaryWeaponInstance, "GripPoint");
			CurrentWeaponEquipped = SecondaryWeaponInstance;
			updateAmmoUi();
			//PlayerHud ->SetScore(SecondaryWeaponInstance ->GetCurrentAmmo());
		}
	}
}


void APc::updateAmmoUi()
{
	//UE_LOG(LogTemp, Warning, TEXT("Testing if event fires"));
	if (CurrentWeaponEquipped == PrimaryWeaponInstance)
	{
		AmmoCounter = PrimaryWeaponInstance -> GetCurrentAmmo();
		onScoreUpdateDelegate.Broadcast(AmmoCounter);
		onIconUpdateDelegate.Broadcast(GunIconone);
	}
	else
	{
		AmmoCounter = SecondaryWeaponInstance -> GetCurrentAmmo();
		onScoreUpdateDelegate.Broadcast(AmmoCounter);
		onIconUpdateDelegate.Broadcast(GunIcon2);
	}
	//UE_LOG(LogTemp, Warning, TEXT("Ammo Is:  %d"), AmmoCounter);
}


void APc::FireWeapon()
{// this fires bullets from the fire, well its binding it to an action as its calling a method from gunbase
	if (CurrentWeaponEquipped)
	{
		CurrentWeaponEquipped->Fire();
		if (CurrentWeaponEquipped == PrimaryWeaponInstance)
		{
			//PrimaryWeaponInstance->Reload();
			updateAmmoUi();
			//PlayerHud ->SetScore(PrimaryWeaponInstance ->GetCurrentAmmo());
		}
		if (CurrentWeaponEquipped == SecondaryWeaponInstance)
		{
			updateAmmoUi();
			//PlayerHud ->SetScore(SecondaryWeaponInstance ->GetCurrentAmmo());
		}
		
	}
	
}

void APc::AttachWeaponToHand(AGunBase* Weapon, FName HandSocketName)
{// this is the logic behind attaching the weapon
		Weapon->AttachToComponent(Playercharacter->GetArmsMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, HandSocketName);// this is finding the arm mesh and then finding the socket by the name we gave it

		if (Playercharacter->CameraComponent)
		{// this here is to make sure the gun snaps properly and follows the camera, just like the arms
			FRotator CameraRotation = Playercharacter->CameraComponent->GetComponentRotation();
			Weapon->SetActorRotation(CameraRotation);
		}

}

void APc::SetHealth()
{
	UE_LOG(LogTemp, Warning, TEXT("for shits and giggles"));
	//PlayerHud->SetHealth(Health);// setting health, for next project when we eventually take damage
}



void APc::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	Playercharacter = Cast<Acharacterbase>(aPawn);
	checkf(Playercharacter, TEXT("im gonna jump of  a brigde, PLAYER CHARACTERBASE DERIVED CLASSES SHOULD ONLY POSSESS ACHARACTERBASE DERIVED PAWNS"))

	EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	checkf(EnhancedInputComponent, TEXT("unable to get reference"));

	checkf(InputMappingContext , TEXT("Unable to get reference"))
    // linking up our mapping context possessed player controller
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer:: GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	checkf(InputSubsystem, TEXT("Unable to get reference to UenhancedInputLocalPlayerSubSystem"))

	//wipe any existing mapping and add our own mapping
	checkf(InputMappingContext, TEXT("inputmapping context was not specified"));
	InputSubsystem -> ClearAllMappings();
	InputSubsystem-> AddMappingContext(InputMappingContext, 0);

	if(ActionMove)
	{
		EnhancedInputComponent->BindAction(
			ActionMove, ETriggerEvent::Triggered, this, &APc::HandleMove);
	}
	if(ActionLook)
	{
		EnhancedInputComponent->BindAction(
			ActionLook, ETriggerEvent::Triggered, this, &APc::HandeLook);
	}
	if(ActionJump)
	{
		EnhancedInputComponent->BindAction(
			ActionJump, ETriggerEvent::Triggered, this, &APc::HandeJump);
	}
	if(ActionSneak)
	{
		EnhancedInputComponent -> BindAction(ActionSneak, ETriggerEvent::Triggered, this, &APc::HandleSneak);
	}

	if(ActionUnSneak)
	{
		EnhancedInputComponent -> BindAction(ActionUnSneak, ETriggerEvent::Triggered, this, &APc::HandleUnsneak);
	}

	if(ActionSprint)
	{
		EnhancedInputComponent -> BindAction(ActionSprint, ETriggerEvent::Triggered, this, &APc::HandleSprint);
	}
	if(ActionUnSprint)
	{
		EnhancedInputComponent -> BindAction(ActionUnSprint, ETriggerEvent::Triggered, this, &APc::HandleUnsprint);
	}

	if(ActionPrimaryWeapon)
	{
		EnhancedInputComponent -> BindAction(ActionPrimaryWeapon, ETriggerEvent::Triggered, this, &APc::EquipPrimaryWeapon);
	}

	if(ActionSecondayWeapon)
	{
		EnhancedInputComponent -> BindAction(ActionSecondayWeapon, ETriggerEvent::Triggered, this, &APc::EquipSecondaryWeapon);
	}

	if(ActionFire)
	{
		EnhancedInputComponent -> BindAction(ActionFire, ETriggerEvent::Triggered, this, &APc::FireWeapon);
	}
	
}

void APc::OnUnPossess()
{
	Super::OnUnPossess();
}

void APc::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	/*if (Playercharacter && CurrentWeaponEquipped)
	{
		// Name of the socket you're checking, for example "Hand_Socket_Right"
		FName HandSocketName = "GripPoint";

		// Check if the socket exists on the character mesh
		if (Playercharacter->GetArmsMesh()->DoesSocketExist(HandSocketName))
		{
			// Get the world location of the socket
			FVector SocketLocation = Playercharacter->GetArmsMesh()->GetSocketLocation(HandSocketName);

			// Draw a debug sphere at the socket location
			DrawDebugSphere(GetWorld(), SocketLocation, 10.0f, 12, FColor::Red, false, -1.0f, 0, 1.0f);

			// Log the socket location to the output log (optional)
			UE_LOG(LogTemp, Warning, TEXT("Socket: %s, Location: %s"), *HandSocketName.ToString(), *SocketLocation.ToString());

			// Optionally print the location on the screen (optional)
			GEngine->AddOnScreenDebugMessage(-1, DeltaSeconds, FColor::Green, FString::Printf(TEXT("Socket: %s, Location: %s"), *HandSocketName.ToString(), *SocketLocation.ToString()));
		}
		else
		{
			// Log an error if the socket doesn't exist
			UE_LOG(LogTemp, Error, TEXT("Socket %s does not exist!"), *HandSocketName.ToString());
		}
	}*/ // ignore this, this is for debugging purposes

	
}

void APc::OnPickupCollectedHandler(APickUpBase* pickup)
{
	
	if (!IsSecondaryWeaponUnlocked)
	{
		IsSecondaryWeaponUnlocked = true;
		EquipSecondaryWeapon();
	}
	else if (SecondaryWeaponInstance)
	{
		SecondaryWeaponInstance->Reload();
		updateAmmoUi();
		if (CurrentWeaponEquipped == SecondaryWeaponInstance)
		{
			//PlayerHud ->SetScore(SecondaryWeaponInstance ->GetCurrentAmmo());
			// Have an event that broadcasts the  score
		}// everytime the player picks up, the second gun restores back to full ammo
	}
	// setscore has an int parameter, we are sending this through to the hud base
	// add a bool for " if second gun obtained, set it to true on first pickup, then every time its picked up replenish the ammo
}


