// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "DamageInterface.h"
#include "SyringeDamageType.generated.h"

/**
 * 
 */
UCLASS()
class DOCTORVSZOMBIE_API USyringeDamageType : public UDamageType, public IDamageInterface
{
	GENERATED_BODY()
public:
	void DealDamage(AEnemyBase* Enemy);
};
