// Fill out your copyright notice in the Description page of Project Settings.


#include "DVZGameInstance.h"
#include "Character/Fight/Projectiles/Syringe.h"
#include "Character/Fight/Projectiles/Medicine.h"

#include "Character/Fight/DamageTypes/RedMedicineDamageType.h"
#include "Character/Fight/DamageTypes/GreenMedicineDamageType.h"
#include "Character/Fight/DamageTypes/BlueMedicineDamageType.h"
#include "Character/Fight/DamageTypes/SyringeDamageType.h"



void UDVZGameInstance::Init()
{
	FWeapon Syringe;
	Syringe.ChoosenWeapon = ASyringe::StaticClass();
	FWeapon Medicine;
	Medicine.ChoosenWeapon = AMedicine::StaticClass();

	Weapons.Add(Syringe);
	Weapons.Add(Medicine);

	FDamage SyringeDamage;
	SyringeDamage.ChoosenDamage = USyringeDamageType::StaticClass();

	FDamage RedMedicine;
	RedMedicine.ChoosenDamage = URedMedicineDamageType::StaticClass();
	FDamage GreenMedicine;
	GreenMedicine.ChoosenDamage = UGreenMedicineDamageType::StaticClass();
	FDamage BlueMedicine;
	BlueMedicine.ChoosenDamage = UBlueMedicineDamageType::StaticClass();

	DamageTypes.Add(SyringeDamage);
	DamageTypes.Add(RedMedicine);
	DamageTypes.Add(GreenMedicine);
	DamageTypes.Add(BlueMedicine);
}