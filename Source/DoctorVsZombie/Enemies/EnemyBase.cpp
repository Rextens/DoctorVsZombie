// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Pixel2DComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Character/Fight/DamageTypes/DamageInterface.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OnTakeAnyDamage.AddDynamic(this, &AEnemyBase::TakeDamage);
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsSleeping)
	{
		SleepingTimer += DeltaTime;
	}

	if (HealthPoints <= 0)
	{
		Destroy();
	}
}

// Called to bind functionality to input
void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyBase::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	const IDamageInterface* ImplementedInterface = Cast<const IDamageInterface>(DamageType);
	if (ImplementedInterface)
	{
		ImplementedInterface->DealDamage(this);
	}
}