// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DoctorVsZombiePlayerController.generated.h"

DECLARE_DELEGATE_OneParam(FChooseWeaponDelegate, const int32);

UCLASS()
class ADoctorVsZombiePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ADoctorVsZombiePlayerController();

	virtual void BeginPlay() override;

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();

	/** Navigate player to the current touch location. */
	void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);
	
	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Scroll(float Value);

	void ChooseItem(const int32 ChoosenNumber);

	void Shot();

	void OpenCloseEquipment();

//Variables
public:
	bool CanMove = true;

	TArray<class UUniversalWidget*> OpenWidgets;

	class UEquipment* EquipmentWidget;

private:
	TSubclassOf<class UEquipment> EquipmentClass;
};


