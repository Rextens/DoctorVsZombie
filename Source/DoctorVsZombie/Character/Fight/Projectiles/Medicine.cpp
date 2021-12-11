// Fill out your copyright notice in the Description page of Project Settings.


#include "Medicine.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "Sound/SoundCue.h"

#include "../../../Enemies/EnemyBase.h"
#include "../../DoctorCharacter.h"
#include "../DamageTypes/RedMedicineDamageType.h"
#include "../DamageTypes/GreenMedicineDamageType.h"
#include "../DamageTypes/BlueMedicineDamageType.h"

#include "Pixel2DComponent.h"
#include "PaperFlipbook.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

AMedicine::AMedicine()
{
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> RedPotionAnimation(TEXT("/Game/TopDownCPP/Animation/Flipbooks/Arsenal/RedPotion_Flipbook"));
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> GreenPotionAnimation(TEXT("/Game/TopDownCPP/Animation/Flipbooks/Arsenal/GreenPotion_Flipbook"));
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> BluePotionAnimation(TEXT("/Game/TopDownCPP/Animation/Flipbooks/Arsenal/BluePotion_Flipbook"));
	
	static ConstructorHelpers::FObjectFinder<USoundCue> BreakingBottleSoundFinder(TEXT("SoundCue'/Game/Sounds/Weapons/Bottle/Glass_shatter_debris_08_Cue.Glass_shatter_debris_08_Cue'"));

	if (BreakingBottleSoundFinder.Object)
	{
		BreakingBottleSound = BreakingBottleSoundFinder.Object;
	}


	RedPotion = RedPotionAnimation.Object;
	GreenPotion = GreenPotionAnimation.Object;
	BluePotion = BluePotionAnimation.Object;

	ProjectileLook->SetWorldScale3D(FVector(2.0f, 2.0f, 2.0f));
}

void AMedicine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ProjectileLook->AddWorldRotation(FRotator(0.0f, DeltaTime * 500.0f, 0.0f));
}

void AMedicine::OnHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
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


void AMedicine::AfterDamageTypeSet()
{
	if (UKismetMathLibrary::ClassIsChildOf(TypeOfDamage, URedMedicineDamageType::StaticClass()))
	{
		ProjectileLook->SetFlipbook(RedPotion);
	}
	if (UKismetMathLibrary::ClassIsChildOf(TypeOfDamage, UGreenMedicineDamageType::StaticClass()))
	{
		ProjectileLook->SetFlipbook(GreenPotion);
	}
	if (UKismetMathLibrary::ClassIsChildOf(TypeOfDamage, UBlueMedicineDamageType::StaticClass()))
	{
		ProjectileLook->SetFlipbook(BluePotion);
	}
}