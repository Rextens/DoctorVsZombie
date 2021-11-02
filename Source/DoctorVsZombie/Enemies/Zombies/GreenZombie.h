// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ZombieBase.h"
#include "GreenZombie.generated.h"

/**
 * 
 */
UCLASS()
class DOCTORVSZOMBIE_API AGreenZombie : public AZombieBase
{
	GENERATED_BODY()

public:
	AGreenZombie();

	virtual void TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser) override;
};
