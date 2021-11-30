// Fill out your copyright notice in the Description page of Project Settings.


#include "SyringeWeapon.h"
#include "../Projectiles/Syringe.h"

USyringeWeapon::USyringeWeapon()
{
	ProjectileClass = ASyringe::StaticClass();
}