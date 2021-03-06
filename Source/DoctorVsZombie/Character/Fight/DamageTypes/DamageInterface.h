// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../BaseCharacter.h"
#include "DamageInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UDamageInterface : public UInterface
{
    GENERATED_BODY()
};

class IDamageInterface
{
    GENERATED_BODY()

public:
    virtual void DealDamage(ABaseCharacter* Enemy) const {};
};