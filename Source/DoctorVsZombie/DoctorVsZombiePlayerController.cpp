// Copyright Epic Games, Inc. All Rights Reserved.

#include "DoctorVsZombiePlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "DoctorVsZombieCharacter.h"
#include "Character/BaseCharacter.h"
#include "Pixel2DComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"

ADoctorVsZombiePlayerController::ADoctorVsZombiePlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ADoctorVsZombiePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}

void ADoctorVsZombiePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ADoctorVsZombiePlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ADoctorVsZombiePlayerController::MoveRight);
}

void ADoctorVsZombiePlayerController::MoveForward(float Value)
{
	if (ABaseCharacter* CharacterReference = Cast<ABaseCharacter>(GetPawn()))
	{
		if (Value != 0.0f)
		{
			// find out which way is forward
			const FRotator Rotation = GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			CharacterReference->IsMovingForwards = true;

			// get forward vector
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			GetPawn()->AddMovementInput(Direction, Value);
		}
		else
		{
			CharacterReference->IsMovingForwards = false;
		}
	}
}

void ADoctorVsZombiePlayerController::MoveRight(float Value)
{
	if (ABaseCharacter* CharacterReference = Cast<ABaseCharacter>(GetPawn()))
	{
		if (Value != 0.0f)
		{
			// find out which way is right
			const FRotator Rotation = GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			CharacterReference->IsMovingRight = true;

				// get right vector 
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
				// add movement in that direction
			GetPawn()->AddMovementInput(Direction, Value);

			if (Value > 0.0f)
			{
				CharacterReference->CharacterAnimation->SetWorldRotation(FRotator(0.0f, 90.0f, 270.0f));
			}
			else if(Value < 0.0f)
			{
				CharacterReference->CharacterAnimation->SetWorldRotation(FRotator(180.0f, 90.0f, 270.0f));
			}
		}
		else
		{
			CharacterReference->IsMovingRight = false;
		}
	}
}

void ADoctorVsZombiePlayerController::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ADoctorVsZombiePlayerController::MoveToMouseCursor()
{
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		if (ADoctorVsZombieCharacter* MyPawn = Cast<ADoctorVsZombieCharacter>(GetPawn()))
		{
			if (MyPawn->GetCursorToWorld())
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MyPawn->GetCursorToWorld()->GetComponentLocation());
			}
		}
	}
	else
	{
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{
			// We hit something, move there
			SetNewMoveDestination(Hit.ImpactPoint);
		}
	}
}

void ADoctorVsZombiePlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void ADoctorVsZombiePlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void ADoctorVsZombiePlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void ADoctorVsZombiePlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}
