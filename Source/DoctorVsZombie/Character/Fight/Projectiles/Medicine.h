// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Projectile.h"
#include "Medicine.generated.h"

/**
 * 
 */
UCLASS()
class DOCTORVSZOMBIE_API AMedicine : public AProjectile
{
	GENERATED_BODY()
public:
	AMedicine();

	virtual void Tick(float DeltaTime) override;

	virtual void OnHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void AfterDamageTypeSet() override;

//VARIABLES
private:
	class UPaperFlipbook* RedPotion;
	class UPaperFlipbook* GreenPotion;
	class UPaperFlipbook* BluePotion;
};
