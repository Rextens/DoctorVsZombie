// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ZombieBase.h"
#include "RedZombie.generated.h"

/**
 * 
 */
UCLASS()
class DOCTORVSZOMBIE_API ARedZombie : public AZombieBase
{
	GENERATED_BODY()

public:
	ARedZombie();

protected:

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) override;
};
