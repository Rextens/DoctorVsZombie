// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueMedicine.h"
#include "PaperSpriteComponent.h"
#include "../../DoctorCharacter.h"
#include "../../../DoctorState.h"
#include "../../Fight/DamageTypes/BlueMedicineDamageType.h"
#include "../../Fight/Projectiles/Medicine.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "PaperSprite.h"



UBlueMedicine::UBlueMedicine()
{
	static ConstructorHelpers::FObjectFinder<UPaperSprite> ItemIconObject(TEXT("PaperSprite'/Game/TopDownCPP/Animation/Spirtes/Arsenal/BluePotion_Sprite.BluePotion_Sprite'"));

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

		if (UDVZGameInstance* GameInstanceReference = Cast<UDVZGameInstance>(Caller->GetGameInstance()))
		{
			if (ADoctorState* DoctorState = Cast<ADoctorState>(Caller->GetPlayerState()))
			{
				FVector Direction = UKismetMathLibrary::GetDirectionUnitVector(Caller->GetActorLocation(), HitResult.Location);

				UWorld* World = GetWorld();
				if (World)
				{
					FActorSpawnParameters SpawnParams;
					SpawnParams.Owner = Caller;
					SpawnParams.Instigator = Caller->GetInstigator();

					// Spawn the projectile at the muzzle.
					AProjectile* Projectile = World->SpawnActor<AProjectile>(AMedicine::StaticClass(), Caller->GetActorLocation(), FRotator(0.0f, Direction.Rotation().Yaw, 0.0f), SpawnParams);
					Projectile->TypeOfDamage = UBlueMedicineDamageType::StaticClass();
					Projectile->AfterDamageTypeSet();

					if (Projectile)
					{
						// Set the projectile's initial trajectory.
						Projectile->FireInDirection(FVector(Direction.X, Direction.Y, 0.0f));

						UItem::AddToStack(DoctorState->Equipment, Index, -1);
					}
				}
			}
		}
	}
}
