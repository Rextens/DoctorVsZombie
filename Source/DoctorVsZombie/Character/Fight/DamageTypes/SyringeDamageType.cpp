// Fill out your copyright notice in the Description page of Project Settings.


#include "SyringeDamageType.h"
#include "Kismet/KismetSystemLibrary.h"

void USyringeDamageType::DealDamage(AEnemyBase* Enemy) const
{
	Enemy->IsSleeping = true;
	Enemy->SleepingTimer = 0.0f;

	UKismetSystemLibrary::PrintString(GetWorld(), "Go to sleep already!");
}