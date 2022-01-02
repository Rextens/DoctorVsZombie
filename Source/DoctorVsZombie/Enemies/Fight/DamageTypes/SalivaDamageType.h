// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "../../../Character/Fight/DamageTypes/DamageInterface.h"
#include "SalivaDamageType.generated.h"

/**
 * 
 */
UCLASS()
class DOCTORVSZOMBIE_API USalivaDamageType : public UDamageType, public IDamageInterface
{
	GENERATED_BODY()
public:
	virtual void DealDamage(ABaseCharacter* Enemy) const override;
};
