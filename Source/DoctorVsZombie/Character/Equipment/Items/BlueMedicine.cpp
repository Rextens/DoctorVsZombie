// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueMedicine.h"
#include "PaperSpriteComponent.h"
#include "../../DoctorCharacter.h"
#include "../../../DoctorState.h"
#include "../../Fight/DamageTypes/BlueMedicineDamageType.h"
#include "../../../DoctorVsZombiePlayerController.h"
#include "../../Fight/Projectiles/Medicine.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Pixel2DComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "PaperSprite.h"
#include "DoctorVsZombie/Character/Fight/Projectiles/BlueMedicineProjectile.h"


UBlueMedicine::UBlueMedicine()
{
	static ConstructorHelpers::FObjectFinder<UPaperSprite> ItemIconObject(TEXT("/Game/TopDownCPP/Animation/Spirtes/Arsenal/BluePotion_Sprite"));

	if (ItemIconObject.Object)
	{
		ItemIcon = ItemIconObject.Object;
	}
}

void UBlueMedicine::Use(class ADoctorCharacter* Caller, FItemStack& ItemStackReference, const int32& Index)
{
	if (ItemStackReference.Stack > 0)
	{
		FHitResult HitResult;
		Cast<APlayerController>(Caller->GetController())->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, HitResult);

		if (ADoctorState* DoctorState = Cast<ADoctorState>(Caller->GetPlayerState()))
		{
			TempLocation = HitResult.Location;

			if (Caller->GetActorLocation().Y - HitResult.Location.Y > 0)
			{
				Caller->CharacterAnimation->SetWorldRotation(FRotator(180.0f, 90.0f, 270.0f));
			}
			else
			{
				Caller->CharacterAnimation->SetWorldRotation(FRotator(0.0f, 90.0f, 270.0f));
			}

			Caller->IsThrowing = true;
			Caller->ThrowAnimation(this);

			Cast<ADoctorVsZombiePlayerController>(Caller->GetController())->CanMove = false;

			UItem::AddToStack(DoctorState->Equipment, Index, -1);

			FTimerHandle UnusedHandle;
			FTimerDelegate TimerDeletage;
			TimerDeletage.BindUFunction(this, FName("Throw"), Caller);
			GetWorld()->GetTimerManager().SetTimer(UnusedHandle, TimerDeletage, 0.3f, false);

			FTimerHandle StopAnimationHandle;
			FTimerDelegate StopAnimationTimerDeletage;
			StopAnimationTimerDeletage.BindUFunction(this, FName("AfterAnimation"), Caller);

			GetWorld()->GetTimerManager().SetTimer(StopAnimationHandle, StopAnimationTimerDeletage, 4.0f / 10.0f, false);
		}
	}
}

void UBlueMedicine::AfterAnimation(ADoctorCharacter* Caller)
{
	Caller->IsThrowing = false;
	Cast<ADoctorVsZombiePlayerController>(Caller->GetController())->CanMove = true;
}

void UBlueMedicine::Throw(ADoctorCharacter* Caller)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Caller;
	SpawnParams.Instigator = Caller->GetInstigator();

	FVector Direction = UKismetMathLibrary::GetDirectionUnitVector(Caller->GetActorLocation(), TempLocation);

	UWorld* World = GetWorld();
	AProjectile* Projectile = World->SpawnActor<AProjectile>(ABlueMedicineProjectile::StaticClass(), Caller->GetActorLocation(), FRotator(0.0f, Direction.Rotation().Yaw, 0.0f), SpawnParams);

	if (Projectile)
	{
		Projectile->FireInDirection(FVector(Direction.X, Direction.Y, 0.0f));
	}
}
