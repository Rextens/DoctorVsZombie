// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "DoctorState.generated.h"

/**
 * 
 */
UCLASS()
class DOCTORVSZOMBIE_API ADoctorState : public APlayerState
{
	GENERATED_BODY()
public:
	int32 ChosenWeapon = 0;
	int32 ChosenDamageType = 0;
};
