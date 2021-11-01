// Fill out your copyright notice in the Description page of Project Settings.


#include "Syringe.h"
#include "Kismet/GameplayStatics.h"
#include "../DamageTypes/SyringeDamageType.h"
#include "../../../Enemies/EnemyBase.h"

void ASyringe::OnHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AEnemyBase* HitEnemy = Cast<AEnemyBase>(OtherActor))
	{
		UGameplayStatics::ApplyDamage(HitEnemy, 1, UGameplayStatics::GetPlayerController(GetWorld(), 0), this, TypeOfDamage);
	}
}