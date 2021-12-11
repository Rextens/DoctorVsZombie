// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Weapon.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class DOCTORVSZOMBIE_API UWeapon : public UObject
{
	GENERATED_BODY()

public:
	virtual void Shoot(class UDVZGameInstance* GameInstanceReference, class ADoctorState* DoctorState, const FVector& DestinationLocation);

//VARIABLES
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString abc = "ddddddddddddd";
};
