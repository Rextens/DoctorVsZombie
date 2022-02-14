// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Projectile.h"
//#include "Commandlets/AnalyzeReferencedContentStat.h"
#include "GreenMedicineProjectile.generated.h"

/**
 * 
 */
UCLASS()
class DOCTORVSZOMBIE_API AGreenMedicineProjectile : public AProjectile
{
	GENERATED_BODY()
public:
	AGreenMedicineProjectile();

	virtual void Tick(float DeltaSeconds) override;

	virtual void OnHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UPROPERTY()
	class USoundCue* BreakingBottleSound;
};
