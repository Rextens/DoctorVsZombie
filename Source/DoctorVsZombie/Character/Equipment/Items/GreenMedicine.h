// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Item.h"
#include "GreenMedicine.generated.h"

/**
 * 
 */
UCLASS()
class DOCTORVSZOMBIE_API UGreenMedicine : public UItem
{
	GENERATED_BODY()
public:
	virtual void Use(class ADoctorCharacter* Caller, FItemStack& ItemStackReference, const int32& Index) override;
};
