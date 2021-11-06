// Fill out your copyright notice in the Description page of Project Settings.


#include "Syringe.h"
#include "Kismet/GameplayStatics.h"
#include "PaperFlipbook.h"
#include "Pixel2DComponent.h"
#include "../DamageTypes/SyringeDamageType.h"
#include "../../../Enemies/EnemyBase.h"


ASyringe::ASyringe()
{
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> ProjectileAnimation(TEXT("/Game/TopDownCPP/Animation/Flipbooks/Arsenal/Dart_Flipbook"));

	ProjectileLook->SetFlipbook(ProjectileAnimation.Object);
	ProjectileLook->SetWorldScale3D(FVector(4.0f, 4.0f, 4.0f));
	ProjectileLook->SetWorldRotation(FRotator(0.0f, 0.0f, 270.0f));
}

void ASyringe::OnHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AEnemyBase* HitEnemy = Cast<AEnemyBase>(OtherActor))
	{
		UGameplayStatics::ApplyDamage(HitEnemy, 1, UGameplayStatics::GetPlayerController(GetWorld(), 0), this, TypeOfDamage);
	}
}