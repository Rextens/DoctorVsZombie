// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Kismet/GameplayStatics.h"
#include "../../../DVZGameInstance.h"
#include "../../../DoctorState.h"
#include "../../DoctorCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "../Projectile.h"

void UWeapon::Shoot(UDVZGameInstance* GameInstanceReference, ADoctorState* DoctorState, const FVector& DestinationLocation)
{
	if (GameInstanceReference)
	{
		if (DoctorState)
		{
			if (ProjectileClass)
			{
				ADoctorCharacter* DoctorCharacterReference = Cast<ADoctorCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

				FVector Direction = UKismetMathLibrary::GetDirectionUnitVector(DoctorCharacterReference->GetActorLocation(), DestinationLocation);

				UWorld* World = GetWorld();
				if (World)
				{
					FActorSpawnParameters SpawnParams;
					SpawnParams.Owner = DoctorCharacterReference;
					SpawnParams.Instigator = DoctorCharacterReference->GetInstigator();

					// Spawn the projectile at the muzzle.
					AProjectile* Projectile = World->SpawnActor<AProjectile>(ProjectileClass, DoctorCharacterReference->GetActorLocation(), FRotator(0.0f, Direction.Rotation().Yaw, 0.0f), SpawnParams);
				//	Projectile->TypeOfDamage = GameInstanceReference->DamageTypes[DoctorState->ChosenDamageType].ChoosenDamage;
					Projectile->AfterDamageTypeSet();

					if (Projectile)
					{
						// Set the projectile's initial trajectory.
						Projectile->FireInDirection(FVector(Direction.X, Direction.Y, 0.0f));
					}
				}
			}
		}
	}
}