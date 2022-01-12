// Fill out your copyright notice in the Description page of Project Settings.


#include "RedMedicineProjectile.h"

#include "PaperFlipbook.h"
#include "Pixel2DComponent.h"
#include "Sound/SoundCue.h"
#include "DoctorVsZombie/Character/DoctorCharacter.h"
#include "DoctorVsZombie/Character/Fight/DamageTypes/RedMedicineDamageType.h"
#include "Kismet/GameplayStatics.h"

ARedMedicineProjectile::ARedMedicineProjectile()
{
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> ProjectileAnimation(TEXT("/Game/TopDownCPP/Animation/Flipbooks/Arsenal/RedPotion_Flipbook"));

	static ConstructorHelpers::FObjectFinder<USoundCue> BreakingBottleSoundFinder(TEXT("SoundCue'/Game/Sounds/Weapons/Bottle/Glass_shatter_debris_08_Cue.Glass_shatter_debris_08_Cue'"));

	if (BreakingBottleSoundFinder.Object)
	{
		BreakingBottleSound = BreakingBottleSoundFinder.Object;
	}
	
	ProjectileLook->SetFlipbook(ProjectileAnimation.Object);
	ProjectileLook->SetWorldScale3D(FVector(2.0f, 2.0f, 2.0f));
	ProjectileLook->SetWorldRotation(FRotator(0.0f, 0.0f, 270.0f));

	TypeOfDamage = URedMedicineDamageType::StaticClass();
}

void ARedMedicineProjectile::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	ProjectileLook->AddWorldRotation(FRotator(0.0f, DeltaSeconds * 500.0f, 0.0f));
}

void ARedMedicineProjectile::OnHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnHit(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (AEnemyBase* HitEnemy = Cast<AEnemyBase>(OtherActor))
	{
		UGameplayStatics::ApplyDamage(HitEnemy, 1, UGameplayStatics::GetPlayerController(GetWorld(), 0), this, TypeOfDamage);
	}

	if (!(Cast<ADoctorCharacter>(OtherActor)))
	{
		UGameplayStatics::PlaySound2D(GetWorld(), BreakingBottleSound, 10.0f);
		Destroy();
	}
}
