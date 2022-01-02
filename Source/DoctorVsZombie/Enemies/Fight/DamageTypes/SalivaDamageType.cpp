// Fill out your copyright notice in the Description page of Project Settings.


#include "SalivaDamageType.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../../../Character/DoctorCharacter.h"


void USalivaDamageType::DealDamage(ABaseCharacter* Enemy) const
{
	if (ADoctorCharacter* EnemyReference = Cast<ADoctorCharacter>(Enemy))
	{
		//EnemyReference->IsSleeping = true;
		//EnemyReference->SleepingTimer = 0.0f;

		UKismetSystemLibrary::PrintString(GetWorld(), "Go to sleep already!");
	}
}