// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DoctorVsZombie/Character/BaseCharacter.h"
#include "DoctorVsZombie/Character/Fight/DamageTypes/DamageInterface.h"
#include "GameFramework/DamageType.h"
#include "ZombieAttack.generated.h"

/**
 * 
 */
UCLASS()
class DOCTORVSZOMBIE_API UZombieAttack : public UDamageType, public IDamageInterface
{
	GENERATED_BODY()
	
public:
	virtual void DealDamage(ABaseCharacter* Enemy) const override;
};
