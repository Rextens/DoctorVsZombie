// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FItemStack
{
	GENERATED_BODY()

	UPROPERTY()
	FName ItemId;

	UPROPERTY()
	int32 Stack = 0;
};

USTRUCT(BlueprintType)
struct FTestItemStack : public FItemStack
{
	GENERATED_BODY()

	UPROPERTY()
		int32 testval = 10;
};

UCLASS()
class DOCTORVSZOMBIE_API UItem : public UObject
{
	GENERATED_BODY()
public:
	UItem();

	virtual void Pickup(const int32 &Index, class AItemDropsManager* ItemDropsManagerReference);

	virtual void Use(class ADoctorCharacter* Caller, FItemStack& ItemStackReference, const int32& Index);

	static bool AddToStack(UPARAM(ref) TArray<FItemStack>& ItemList, const int32& Index, const int32& Amount);

//VARIABLES
public:
	class UPaperSprite* ItemIcon;
};
