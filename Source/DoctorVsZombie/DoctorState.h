// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Character/Fight/Weapons/Weapon.h"
#include "DVZGameInstance.h"
#include "DoctorState.generated.h"

/**
 * 
 */

UCLASS()
class DOCTORVSZOMBIE_API ADoctorState : public APlayerState
{
	GENERATED_BODY()
public:
	ADoctorState();

	virtual void BeginPlay() override;

	int32 ChosenItem = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 HealthPoints = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FItemStack> Equipment;
};
