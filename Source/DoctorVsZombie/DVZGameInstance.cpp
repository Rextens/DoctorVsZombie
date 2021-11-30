// Fill out your copyright notice in the Description page of Project Settings.


#include "DVZGameInstance.h"
#include "Humans/HumanBase.h"
#include "Enemies/EnemyBase.h"

#include "Character/Fight/Weapons/SyringeWeapon.h"
#include "Character/Fight/Weapons/Bottle.h"

#include "Character/Fight/Weapons/SyringeWeapon.h"
#include "Character/Fight/Weapons/Bottle.h"

#include "Character/Fight/DamageTypes/RedMedicineDamageType.h"
#include "Character/Fight/DamageTypes/GreenMedicineDamageType.h"
#include "Character/Fight/DamageTypes/BlueMedicineDamageType.h"
#include "Character/Fight/DamageTypes/SyringeDamageType.h"

#include "Character/Equipment/Items/RedMedicine.h"
#include "Character/Equipment/Items/GreenMedicine.h"
#include "Character/Equipment/Items/BlueMedicine.h"
#include "Character/Equipment/Items/SyringePistol.h"

#include "World/ItemDropsManager.h"


void UDVZGameInstance::Init()
{
	RegisterWeapon("Syringe", USyringeWeapon::StaticClass());
	RegisterWeapon("Bottle", UBottle::StaticClass());

	RegisterDamageType("SyringeDamageType", USyringeDamageType::StaticClass());
	RegisterDamageType("BlueMedicine", UBlueMedicineDamageType::StaticClass());
	RegisterDamageType("GreenMedicine", UGreenMedicineDamageType::StaticClass());
	RegisterDamageType("RedMedicine", URedMedicineDamageType::StaticClass());


	RegisterItem("RedMedicine", URedMedicine::StaticClass());
	RegisterItem("GreenMedicine", UGreenMedicine::StaticClass());
	RegisterItem("BlueMedicine", UBlueMedicine::StaticClass());
	RegisterItem("SyringePistol", USyringePistol::StaticClass());
}

void UDVZGameInstance::RegisterItem(FName ItemId, TSubclassOf<class UItem> ItemClass)
{
	FItemRegistry ItemRegistry;
	ItemRegistry.RegisteredItem = NewObject<UItem>(this, ItemClass);
	RegisteredItems.Add(FName(*(GameParish.ToString() + "." + ItemId.ToString())), ItemRegistry);
}

void UDVZGameInstance::RegisterDamageType(const FName& DamageTypeId, TSubclassOf<class UDamageType> ItemClass)
{
	FDamage DamageType;
	DamageType.ChoosenDamage = ItemClass;
	DamageTypes.Add(FName(*(GameParish.ToString() + "." + DamageTypeId.ToString())), DamageType);
}

void UDVZGameInstance::RegisterWeapon(const FName& WeaponId, TSubclassOf<UWeapon> ChoosenWeapon)
{
	FWeaponRegistry Weapon;
	Weapon.Weapon = NewObject<UWeapon>(this, ChoosenWeapon);
	Weapons.Add(FName(*(GameParish.ToString() + "." + WeaponId.ToString())), Weapon);
}