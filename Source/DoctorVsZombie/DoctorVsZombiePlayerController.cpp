// Copyright Epic Games, Inc. All Rights Reserved.

#include "DoctorVsZombiePlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "Character/Fight/DamageTypes/BlueMedicineDamageType.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "DoctorVsZombieCharacter.h"
#include "Character/Equipment/Item.h"
#include "Character/DoctorCharacter.h"
#include "Pixel2DComponent.h"
#include "DVZGameInstance.h"
#include "DoctorInstance.h"
#include "DoctorState.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Widgets/UniversalWidget.h"
#include "Widgets/Equipment/Equipment.h"

#include "Engine/World.h"

ADoctorVsZombiePlayerController::ADoctorVsZombiePlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;

	ConstructorHelpers::FClassFinder<UUserWidget> EquipmentWidgetReference(TEXT("/Game/Widgets/Equipment/Equipment"));

	if (EquipmentWidgetReference.Class)
	{
		EquipmentClass = EquipmentWidgetReference.Class;
	}
}

void ADoctorVsZombiePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (EquipmentClass)
	{
		EquipmentWidget = CreateWidget<UEquipment>(this, EquipmentClass);
	}
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
	InputComponent->BindAxis("Scroll", this, &ADoctorVsZombiePlayerController::Scroll);

	InputComponent->BindAction<FChooseWeaponDelegate>("ChooseItem1", IE_Pressed, this, &ADoctorVsZombiePlayerController::ChooseDamage, 0);
	InputComponent->BindAction<FChooseWeaponDelegate>("ChooseItem2", IE_Pressed, this, &ADoctorVsZombiePlayerController::ChooseDamage, 1);
	InputComponent->BindAction<FChooseWeaponDelegate>("ChooseItem3", IE_Pressed, this, &ADoctorVsZombiePlayerController::ChooseDamage, 2);
	InputComponent->BindAction<FChooseWeaponDelegate>("ChooseItem4", IE_Pressed, this, &ADoctorVsZombiePlayerController::ChooseDamage, 3);
	InputComponent->BindAction<FChooseWeaponDelegate>("ChooseItem5", IE_Pressed, this, &ADoctorVsZombiePlayerController::ChooseDamage, 4);
	InputComponent->BindAction<FChooseWeaponDelegate>("ChooseItem6", IE_Pressed, this, &ADoctorVsZombiePlayerController::ChooseDamage, 5);
	InputComponent->BindAction<FChooseWeaponDelegate>("ChooseItem7", IE_Pressed, this, &ADoctorVsZombiePlayerController::ChooseDamage, 6);
	InputComponent->BindAction<FChooseWeaponDelegate>("ChooseItem8", IE_Pressed, this, &ADoctorVsZombiePlayerController::ChooseDamage, 7);
	InputComponent->BindAction<FChooseWeaponDelegate>("ChooseItem9", IE_Pressed, this, &ADoctorVsZombiePlayerController::ChooseDamage, 8);

	InputComponent->BindAction("OpenEquipment/CloseGui", IE_Pressed, this, &ADoctorVsZombiePlayerController::OpenCloseEquipment);

	InputComponent->BindAction("Shot", IE_Pressed, this, &ADoctorVsZombiePlayerController::Shot);
}

void ADoctorVsZombiePlayerController::MoveForward(float Value)
{
	if (CanMove)
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
}

void ADoctorVsZombiePlayerController::MoveRight(float Value)
{
	if (CanMove)
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
				else if (Value < 0.0f)
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
}

void ADoctorVsZombiePlayerController::Scroll(float Value)
{
	if (UDVZGameInstance* GameInstanceReference = Cast<UDVZGameInstance>(GetGameInstance()))
	{
		if (ADoctorState* DoctorState = Cast<ADoctorState>(PlayerState))
		{
			if (Value > 0)
			{
				++DoctorState->ChosenItem;
			}
			else if (Value < 0)
			{
				--DoctorState->ChosenItem;
			}

			if (DoctorState->ChosenItem < 0)
			{
				DoctorState->ChosenItem = 8;
			}
			else if (DoctorState->ChosenItem > 8)
			{
				DoctorState->ChosenItem = 0;
			}
		}
	}
}

void ADoctorVsZombiePlayerController::ChooseDamage(const int32 ChoosenNumber)
{
	if (UDVZGameInstance* GameInstanceReference = Cast<UDVZGameInstance>(GetGameInstance()))
	{
		if (ADoctorState* DoctorState = Cast<ADoctorState>(PlayerState))
		{
			DoctorState->ChosenItem = ChoosenNumber;

			/*
			if (ChoosenNumber == 0)
			{
				DoctorState->ChosenWeapon = 0;
			//	DoctorState->ChosenDamageType = 0;
			}
			else if(ChoosenNumber = 1)
			{
				DoctorState->ChosenWeapon = 1;
			//	DoctorState->ChosenDamageType = ChoosenNumber;
			}
			*/
		}
	}
}

void ADoctorVsZombiePlayerController::Shot()
{
	if (UDVZGameInstance* GameInstanceReference = Cast<UDVZGameInstance>(GetGameInstance()))
	{
		if (ADoctorState* DoctorState = Cast<ADoctorState>(PlayerState))
		{
			if (DoctorState->Equipment.Num() > DoctorState->ChosenItem)
			{
				if (GameInstanceReference->RegisteredItems.Contains(DoctorState->Equipment[DoctorState->ChosenItem].ItemId))
				{
					GameInstanceReference->RegisteredItems[DoctorState->Equipment[DoctorState->ChosenItem].ItemId].RegisteredItem->Use(Cast<ADoctorCharacter>(GetPawn()), DoctorState->Equipment[DoctorState->ChosenItem], DoctorState->ChosenItem);
					//UKismetSystemLibrary::PrintString(GetWorld(), GameInstanceReference->test->abc);
				}
			}
		}
		/*
		FHitResult HitResult;
		GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, HitResult);
		CharacterReference->Fire(HitResult.Location);
		*/
	}
}

void ADoctorVsZombiePlayerController::OpenCloseEquipment()
{
	if (OpenWidgets.Num() == 0)
	{
		EquipmentWidget->Open();
	}
	else
	{
		for (int32 i = 0; i < OpenWidgets.Num(); ++i)
		{
			OpenWidgets[i]->Close();
		}

		OpenWidgets.Empty();
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
