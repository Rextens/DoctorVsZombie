// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "DVZGameInstance.h"
#include "DoctorState.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FWeaponStack
{
	GENERATED_BODY()

	UPROPERTY()
	FName WeaponId;

	int32 Stack = 0;
};

USTRUCT(BlueprintType)
struct FMedicineStack
{
	GENERATED_BODY()

	UPROPERTY()
	FName MedicineId;

	int32 Stack = 0;
};

UCLASS()
class DOCTORVSZOMBIE_API ADoctorState : public APlayerState
{
	GENERATED_BODY()
public:
	ADoctorState();

	virtual void BeginPlay() override;

	int32 ChosenWeapon = 0;
	int32 ChosenDamageType = 0;
	int32 ChosenItem = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FItemStack> Equipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FWeaponStack> Weapons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FMedicineStack> Medicines;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TArray<FItemStack> Equipment;
};
