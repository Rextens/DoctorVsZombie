// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RoomBase.h"
#include "StartRoom.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class DOCTORVSZOMBIE_API AStartRoom : public ARoomBase
{
	GENERATED_BODY()
public:

	AStartRoom();

	virtual void BeginPlay() override;

//VARIABLES
	FVector2D StartTile;
};
