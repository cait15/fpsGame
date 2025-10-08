// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystemInterface.h"
#include "GunBase.h"
#include "InputActionValue.h"
#include "PickUpBase.h"
#include "GameFramework/PlayerController.h"

#include "Pc.generated.h"// this must be last
class AHudBase;
// foward decl
class Acharacterbase;
class UInputAction;

class UEnhancedInputComponent;
/**
 * 
 */
DECLARE_MULTICAST_DELEGATE_OneParam(FOnScoreUpdate, int32)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnIconUpdate, FSlateBrush)
UCLASS(Abstract)

class BUILDINGBLOCKS_API APc : public APlayerController
{


public:
	void updateAmmoUi();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Info")
	FString PlayerName;

	int32 AmmoCounter;
	static FOnScoreUpdate onScoreUpdateDelegate;
	static FOnIconUpdate onIconUpdateDelegate;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "PlayerInput/CharacterMovement")
	UInputAction* ActionMove = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "PlayerInput/CharacterMovement")
	UInputAction* ActionLook = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "PlayerInput/CharacterMovement")
	UInputAction* ActionJump = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "PlayerInput/CharacterMovement")
	UInputAction* ActionSneak = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "PlayerInput/CharacterMovement")
	UInputAction* ActionUnSneak = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "PlayerInput/CharacterMovement")
	UInputAction* ActionSprint = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "PlayerInput/CharacterMovement")
	UInputAction* ActionUnSprint = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "PlayerInput/CharacterMovement")
	UInputAction* ActionPrimaryWeapon = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "PlayerInput/CharacterMovement")
	UInputAction* ActionSecondayWeapon = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "PlayerInput/CharacterMovement")
	UInputAction* ActionFire = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "PlayerInput/CharacterMovement")
	UInputMappingContext* InputMappingContext = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
	TSubclassOf<AGunBase> PrimaryWeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
	TSubclassOf<AGunBase> SecondaryWeaponClass;

	UPROPERTY(EditAnywhere, Category="0_Setup")
	FSlateBrush GunIconone;

	UPROPERTY(EditAnywhere, Category="0_Setup")
	FSlateBrush GunIcon2;

	void FireWeapon();
protected:
	void HandleMove(const FInputActionValue& InputActionValue);
	
	void HandeJump();
	
	void HandleSneak();

	void HandleUnsneak();
	
	void HandleUnsprint();
	
	void HandeLook(const FInputActionValue& InputActionValue);

	void HandleSprint();

	virtual void OnPossess(APawn* aPawn) override;
	
	virtual void OnUnPossess() override;
	
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;
	
	void EquipPrimaryWeapon();
	
	void EquipSecondaryWeapon();

	//int ammoCounter(int32 counter) const;
	
private:
	UPROPERTY()
	
	 AGunBase* CurrentWeaponEquipped;// Method to fire the currently equipped weapon
	
	void AttachWeaponToHand(AGunBase* Weapon, FName HandSocketName);
	
	UEnhancedInputComponent * EnhancedInputComponent = nullptr;// getting a reference to an object
	
	UPROPERTY()
	Acharacterbase* Playercharacter = nullptr;
	
	bool IsCrouching = false;
	
	bool IsSprinting = false;
	
	float SprintSpeed = 1000.0f;
	
	float WalkSpeed = 600.0f;

	FTimerHandle EquipWeaponTimerHandle;// timers
	FTimerHandle SetHealthTimer;

	UPROPERTY(BlueprintReadOnly, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
	bool IsSecondaryWeaponUnlocked;
	
	//UPROPERTY()
	//AHudBase* PlayerHud = nullptr; // reference to the hud

	UPROPERTY()
	int32 FragmentsCollected = 0;

	UPROPERTY()
	int32 Health = 100;
	
	UFUNCTION()
	void SetHealth();
	
	
	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
	AGunBase* PrimaryWeaponInstance;
	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
	AGunBase* SecondaryWeaponInstance;

	UFUNCTION()
	void OnPickupCollectedHandler(APickUpBase* pickup); // referencing pickup base
	
	GENERATED_BODY()
};
