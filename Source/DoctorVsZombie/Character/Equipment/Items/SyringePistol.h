// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Item.h"
#include "SyringePistol.generated.h"

/**
 * 
 */
UCLASS()
class DOCTORVSZOMBIE_API USyringePistol : public UItem
{
	GENERATED_BODY()

public:
	USyringePistol();

	virtual void Use(class ADoctorCharacter* Caller, FItemStack& ItemStackReference, const int32& Index) override;

private:
	UFUNCTION()
		void AfterAnimation(class ADoctorCharacter* Caller);

	UFUNCTION()
		void Shoot(class ADoctorCharacter* Caller);

	//VARIABLES
private:
	FVector TempLocation;

	class USoundCue* DartGunSound;
};
