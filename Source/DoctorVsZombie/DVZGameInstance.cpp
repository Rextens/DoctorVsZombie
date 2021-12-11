// Fill out your copyright notice in the Description page of Project Settings.


#include "DVZGameInstance.h"

#include "DoctorState.h"

#include "Saves/Character/CharacterSave.h"

#include "Humans/HumanBase.h"
#include "Enemies/EnemyBase.h"

#include "Character/DoctorCharacter.h"

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

#include "Kismet/GameplayStatics.h"


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

	test = NewObject<UWeapon>();
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

void UDVZGameInstance::SaveGame(const FString& InstanceName)
{
	ADoctorCharacter* CharacterReference = Cast<ADoctorCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (CharacterReference)
	{
		if (ADoctorState* PlayerStateReference = Cast<ADoctorState>(CharacterReference->GetPlayerState()))
		{
			if (UCharacterSave* CharacterSave = Cast<UCharacterSave>(UGameplayStatics::CreateSaveGameObject(UCharacterSave::StaticClass())))
			{
				CharacterSave->Equipment = PlayerStateReference->Equipment;
				CharacterSave->Position = CharacterReference->GetActorLocation();
				CharacterSave->HealthPoints = PlayerStateReference->HealthPoints;

				UGameplayStatics::AsyncSaveGameToSlot(CharacterSave, "DVZ/" + InstanceName + "/Character/Character", 0);
			}
		}
	}
}

void UDVZGameInstance::LoadGame(const FString& InstanceName)
{
	ADoctorCharacter* CharacterReference = Cast<ADoctorCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (CharacterReference)
	{
		if (ADoctorState* PlayerStateReference = Cast<ADoctorState>(CharacterReference->GetPlayerState()))
		{
			if (UCharacterSave* CharacterSave = Cast<UCharacterSave>(UGameplayStatics::LoadGameFromSlot("DVZ/" + InstanceName + "/Character/Character", 0)))
			{
				PlayerStateReference->Equipment = CharacterSave->Equipment;
				PlayerStateReference->HealthPoints = CharacterSave->HealthPoints;
				CharacterReference->SetActorLocation(CharacterSave->Position);
			}
		}
	}
}
