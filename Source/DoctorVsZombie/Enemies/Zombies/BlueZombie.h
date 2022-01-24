// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ZombieBase.h"
#include "BlueZombie.generated.h"

/**
 * 
 */
UCLASS()
class DOCTORVSZOMBIE_API ABlueZombie : public AZombieBase
{
	GENERATED_BODY()

public:
	ABlueZombie();

protected:

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) override;
};
