// Fill out your copyright notice in the Description page of Project Settings.


#include "SalivaDamageType.h"

#include "Pixel2DComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../../../Character/DoctorCharacter.h"
#include "DoctorVsZombie/DoctorState.h"


void USalivaDamageType::DealDamage(ABaseCharacter* Enemy) const
{
	if (ADoctorCharacter* EnemyReference = Cast<ADoctorCharacter>(Enemy))
	{
		//EnemyReference->IsSleeping = true;
		//EnemyReference->SleepingTimer = 0.0f;

		EnemyReference->CharacterAnimation->SetSpriteColor(FLinearColor::Red);

		FTimerHandle UnusedHandle;
		EnemyReference->GetWorldTimerManager().SetTimer(UnusedHandle, EnemyReference, &ADoctorCharacter::TakeDamageDelay, 0.3f, false);

		--Cast<ADoctorState>(EnemyReference->GetPlayerState())->HealthPoints;

		UKismetSystemLibrary::PrintString(GetWorld(), "HP: " + FString::FromInt(Cast<ADoctorState>(EnemyReference->GetPlayerState())->HealthPoints));
	}
}
