// Fill out your copyright notice in the Description page of Project Settings.


#include "GreenZombie.h"
#include "Kismet/KismetSystemLibrary.h"

AGreenZombie::AGreenZombie()
{
	ZombieColor = ZombieType::GREEN;
	HealthPoints = 2;
}

void AGreenZombie::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	Super::TakeDamage(DamagedActor, Damage, DamageType, InstigatedBy, DamageCauser);
}