// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "DamageInterface.h"
#include "MedicineDamageType.generated.h"

/**
 * 
 */
UCLASS()
class DOCTORVSZOMBIE_API UMedicineDamageType : public UDamageType, public IDamageInterface
{
	GENERATED_BODY()
public:
	void DealDamage(AEnemyBase* Enemy);
};
