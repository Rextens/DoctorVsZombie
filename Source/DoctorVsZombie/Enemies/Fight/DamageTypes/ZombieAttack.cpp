// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieAttack.h"

#include "Kismet/KismetSystemLibrary.h"

void UZombieAttack::DealDamage(ABaseCharacter* Enemy) const
{
	UKismetSystemLibrary::PrintString(GetWorld(), "Attacked!");
}
