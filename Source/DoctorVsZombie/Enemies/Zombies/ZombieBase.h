// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../EnemyBase.h"
#include "ZombieBase.generated.h"

UENUM(BlueprintType)
enum class ZombieType : uint8 {
    NONE = 0,
    RED = 1,
    GREEN = 2,
    BLUE = 3
};

/**
 * 
 */
UCLASS()
class DOCTORVSZOMBIE_API AZombieBase : public AEnemyBase
{
	GENERATED_BODY()

public:
    AZombieBase();
    virtual void BeginPlay() override;

    virtual void TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

    virtual void Tick(float DeltaTime) override;
    virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

    void Delay();
//VARIABLES
    ZombieType ZombieColor;
};
