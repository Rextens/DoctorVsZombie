// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Character/Fight/Weapons/Weapon.h"
#include "Character/Fight/Projectile.h"
#include "Character/Equipment/Item.h"
#include "DoctorInstance.generated.h"

/**
 * 
 */
UCLASS()
class DOCTORVSZOMBIE_API UDoctorInstance : public UGameInstance
{
	GENERATED_BODY()
public:

	UDoctorInstance();

	virtual void Init() override;

	UWeapon* test;
};
