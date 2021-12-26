// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieBase.h"
#include "GameFramework/PawnMovementComponent.h"
#include "../../Humans/HumanBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Pixel2DComponent.h"

AZombieBase::AZombieBase()
{
	static ConstructorHelpers::FClassFinder<AController> AiController(TEXT("Blueprint'/Game/NPC/Controllers/ZombieController'"));

	AIControllerClass = AiController.Class;
	bUseControllerRotationYaw = false;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	FNavAvoidanceMask test;
	test.bGroup1 = false;

	GetCharacterMovement()->GroupsToIgnore = test;
}

void AZombieBase::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	Super::TakeDamage(DamagedActor, Damage, DamageType, InstigatedBy, DamageCauser);

	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &AZombieBase::Delay, 0.1, false);
	//CharacterAnimation->AddImpulse(FVector(1000.0f, 1000.0f, 0.0f));
	//GetCharacterMovement()->AddImpulse(FVector(1000.0f, 0.0f, 0.0f), true);
}

void AZombieBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HealthPoints <= 0)
	{
		FRotator Rotation(0.0f, 0.0f, 0.0f);
		FActorSpawnParameters SpawnInfo;
		GetWorld()->SpawnActor<AHumanBase>(GetActorLocation(), Rotation, SpawnInfo);
	}
}

void AZombieBase::Delay()
{
	CharacterAnimation->SetSpriteColor(FLinearColor::White);
}


