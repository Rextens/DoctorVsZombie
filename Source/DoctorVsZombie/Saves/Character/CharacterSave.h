// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "../../Character/Equipment/Item.h"
#include "CharacterSave.generated.h"

/**
 * 
 */
UCLASS()
class DOCTORVSZOMBIE_API UCharacterSave : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	int32 HealthPoints = 10;

	UPROPERTY()
	FVector Position;

	UPROPERTY()
	TArray<FItemStack> Equipment;
};
