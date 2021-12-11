// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Item.h"
#include "../../../Callback.h"
#include "BlueMedicine.generated.h"

/**
 * 
 */
UCLASS()
class DOCTORVSZOMBIE_API UBlueMedicine : public UItem
{
	GENERATED_BODY()
public:
	UBlueMedicine();

public:
	virtual void Use(class ADoctorCharacter* Caller, FItemStack& ItemStackReference, const int32& Index) override;

private:
	UFUNCTION()
	void AfterAnimation(class ADoctorCharacter* Caller);

	UFUNCTION()
		void Throw(class ADoctorCharacter* Caller);
//VARIABLES
private:
	FVector TempLocation;
};
