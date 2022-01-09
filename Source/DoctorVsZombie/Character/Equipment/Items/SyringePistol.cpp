// Fill out your copyright notice in the Description page of Project Settings.


#include "SyringePistol.h"

#include "../../DoctorCharacter.h"
#include "../../../DoctorState.h"
#include "../../Fight/DamageTypes/SyringeDamageType.h"
#include "../../../DoctorVsZombiePlayerController.h"
#include "../../Fight/Projectiles/Syringe.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "Sound/SoundCue.h"

#include "Pixel2DComponent.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"

USyringePistol::USyringePistol()
{
	static ConstructorHelpers::FObjectFinder<USoundCue> DartGunSoundFinder(TEXT("SoundCue'/Game/Sounds/Weapons/DartGun/Dart_Gun_01_Cue.Dart_Gun_01_Cue'"));

	if (DartGunSoundFinder.Object)
	{
		DartGunSound = DartGunSoundFinder.Object;
	}
}

void USyringePistol::Use(class ADoctorCharacter* Caller, FItemStack& ItemStackReference, const int32& Index)
{
	if (ItemStackReference.Stack > 0)
	{
		FHitResult HitResult;
		Cast<APlayerController>(Caller->GetController())->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, HitResult);

		if (Caller->GetActorLocation().Y - HitResult.Location.Y > 0)
		{
			Caller->CharacterAnimation->SetWorldRotation(FRotator(180.0f, 90.0f, 270.0f));
		}
		else
		{
			Caller->CharacterAnimation->SetWorldRotation(FRotator(0.0f, 90.0f, 270.0f));
		}

		TempLocation = HitResult.Location;
		
		Cast<ADoctorVsZombiePlayerController>(Caller->GetController())->CanMove = false;

		Caller->IsShooting = true;
		Caller->ThrowAnimation(this);

		FTimerHandle UnusedHandle;
		FTimerDelegate TimerDeletage;
		TimerDeletage.BindUFunction(this, FName("Shoot"), Caller);
		GetWorld()->GetTimerManager().SetTimer(UnusedHandle, TimerDeletage, 0.3f, false);

		FTimerHandle StopAnimationHandle;
		FTimerDelegate StopAnimationTimerDeletage;
		StopAnimationTimerDeletage.BindUFunction(this, FName("AfterAnimation"), Caller);

		GetWorld()->GetTimerManager().SetTimer(StopAnimationHandle, StopAnimationTimerDeletage, 4.0f / 10.0f, false);
	}
}

void USyringePistol::AfterAnimation(ADoctorCharacter* Caller)
{
	Caller->IsShooting = false;
	Cast<ADoctorVsZombiePlayerController>(Caller->GetController())->CanMove = true;
}

void USyringePistol::Shoot(ADoctorCharacter* Caller)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Caller;
	SpawnParams.Instigator = Caller->GetInstigator();

	FVector Direction = UKismetMathLibrary::GetDirectionUnitVector(Caller->GetActorLocation(), TempLocation);

	UWorld* World = GetWorld();
	AProjectile* Projectile = World->SpawnActor<AProjectile>(ASyringe::StaticClass(), Caller->GetActorLocation(), FRotator(0.0f, Direction.Rotation().Yaw, 0.0f), SpawnParams);
	if(Projectile)
	{
		Projectile->TypeOfDamage = USyringeDamageType::StaticClass();
		Projectile->AfterDamageTypeSet();
		
		UGameplayStatics::PlaySound2D(GetWorld(), DartGunSound);

		Projectile->FireInDirection(FVector(Direction.X, Direction.Y, 0.0f));
		
	}
}
