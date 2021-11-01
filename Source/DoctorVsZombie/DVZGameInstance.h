// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Character/Fight/Projectile.h"
#include "DVZGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FWeapon
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSubclassOf<AProjectile> ChoosenWeapon;
};

USTRUCT(BlueprintType)
struct FDamage
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSubclassOf<UDamageType> ChoosenDamage;
};
/**
 * 
 */
UCLASS()
class DOCTORVSZOMBIE_API UDVZGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

	TArray<FWeapon> Weapons;
	TArray<FDamage> DamageTypes;
};
