// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Projectile.h"
#include "Syringe.generated.h"

/**
 * 
 */
UCLASS()
class DOCTORVSZOMBIE_API ASyringe : public AProjectile
{
	GENERATED_BODY()
public:
	ASyringe();

	virtual void OnHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
