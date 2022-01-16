// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Character/Fight/Weapons/Weapon.h"
#include "Character/Equipment/Item.h"
#include "World/Rooms/RoomBase.h"
#include "DVZGameInstance.generated.h"


USTRUCT(BlueprintType)
struct FWeaponRegistry
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//TSubclassOf<UWeapon> ChoosenWeapon;
	UWeapon* Weapon;
};

USTRUCT(BlueprintType)
struct FDamage
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSubclassOf<UDamageType> ChoosenDamage;
};

USTRUCT(BlueprintType)
struct FItemRegistry
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UItem* RegisteredItem;
};

USTRUCT(BlueprintType)
struct FRoomRegistry
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSubclassOf<ARoomBase> RegisteredItem;
};

/**
 * 
 */
UCLASS()
class DOCTORVSZOMBIE_API UDVZGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	virtual void Init() override;

	void RegisterItem(FName ItemId, TSubclassOf<class UItem> ItemClass);
	void RegisterDamageType(const FName& DamageTypeId, TSubclassOf<class UDamageType> ItemClass);
	void RegisterWeapon(const FName& WeaponId, TSubclassOf<class UWeapon> ChoosenWeapon);
	void RegisterRoom(const FName& WeaponId, TSubclassOf<class ARoomBase> ChoosenWeapon);

	
	UFUNCTION()
	void SaveGame(const FString& InstanceName);

	UFUNCTION()
	void LoadGame(const FString& InstanceName);


//VARAIBLES

	FName GameParish = "DVZ";

	FString abc = "ddd";

	//TArray<FWeaponRegistry> Weapons;
	//TArray<FDamage> DamageTypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class AHumanBase*> Humans;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class AEnemyBase*> Enemies;

	//TMap<FName, UItem*> RegisteredItems;

	UPROPERTY()
	TMap<FName, FItemRegistry> RegisteredItems;
	UPROPERTY()
	TMap<FName, FDamage> DamageTypes;
	UPROPERTY()
	TMap<FName, FWeaponRegistry> Weapons;
	UPROPERTY()
	TMap<FName, FRoomRegistry> RegisteredRooms;

//	UPROPERTY()
//	ARoomBase* CurrentRoom;
	
	UPROPERTY()
	UWeapon *test;

	UPROPERTY()
	class AItemDropsManager* ItemDropManagerReference;

	UPROPERTY()
	ARoomBase* CurrentlyActiveRoom;
};
