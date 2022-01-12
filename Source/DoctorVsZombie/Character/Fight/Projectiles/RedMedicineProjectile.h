// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Projectile.h"
#include "RedMedicineProjectile.generated.h"

/**
 * 
 */
UCLASS()
class DOCTORVSZOMBIE_API ARedMedicineProjectile : public AProjectile
{
	GENERATED_BODY()
public:
	ARedMedicineProjectile();

	virtual void Tick(float DeltaSeconds) override;
	
	virtual void OnHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UPROPERTY()
	class USoundCue* BreakingBottleSound;
};
