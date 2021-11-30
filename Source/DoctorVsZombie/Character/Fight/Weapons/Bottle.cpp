// Fill out your copyright notice in the Description page of Project Settings.


#include "Bottle.h"
#include "../Projectiles/Medicine.h"

UBottle::UBottle()
{
	ProjectileClass = AMedicine::StaticClass();
}