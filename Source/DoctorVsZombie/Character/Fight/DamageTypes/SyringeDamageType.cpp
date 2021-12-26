// Fill out your copyright notice in the Description page of Project Settings.


#include "SyringeDamageType.h"
#include "../../../Enemies/EnemyBase.h"
#include "Kismet/KismetSystemLibrary.h"

void USyringeDamageType::DealDamage(ABaseCharacter* Enemy) const
{
	if (AEnemyBase* EnemyReference = Cast<AEnemyBase>(Enemy))
	{
		EnemyReference->IsSleeping = true;
		EnemyReference->SleepingTimer = 0.0f;

		UKismetSystemLibrary::PrintString(GetWorld(), "Go to sleep already!");
	}
}