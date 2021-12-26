// Fill out your copyright notice in the Description page of Project Settings.


#include "MedicineDamageType.h"

#include "Pixel2DComponent.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "../../../Enemies/EnemyBase.h"

#include "Sound/SoundCue.h"

UMedicineDamageType::UMedicineDamageType()
{

}

void UMedicineDamageType::DealDamage(ABaseCharacter* Enemy) const
{
	if (AZombieBase* Zombie = Cast<AZombieBase>(Enemy))
	{
		if (Zombie->ZombieColor == MedicineType)
		{
			Zombie->CharacterAnimation->SetSpriteColor(FLinearColor::Red);
			--Zombie->HealthPoints;
		}
	}
}