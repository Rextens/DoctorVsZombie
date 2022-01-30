// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieBase.h"
#include "GameFramework/PawnMovementComponent.h"
#include "../../Humans/HumanBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Pixel2DComponent.h"
#include "DoctorVsZombie/DVZGameInstance.h"
#include "DoctorVsZombie/Character/DoctorCharacter.h"
#include "DoctorVsZombie/Enemies/Fight/DamageTypes/ZombieAttack.h"
#include "Kismet/GameplayStatics.h"

AZombieBase::AZombieBase()
{
	static ConstructorHelpers::FClassFinder<AController> AiController(TEXT("Blueprint'/Game/NPC/Controllers/ZombieController'"));

	AIControllerClass = AiController.Class;
	bUseControllerRotationYaw = false;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	CharacterAnimation->SetWorldScale3D(FVector(0.285f, 0.285f, 0.285f));
	
 //   GetCharacterMovement()->GroupsToIgnore = test;
}

void AZombieBase::BeginPlay()
{
	Super::BeginPlay();
	
	if(UDVZGameInstance* GameInstanceReference = Cast<UDVZGameInstance>(GetGameInstance()))
	{
		GameInstanceReference->CurrentlyActiveRoom->Zombies.Add(this);
	}
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

	if(IsWithinAttackZone && IsReadyToAttack)
	{
		//UKismetSystemLibrary::PrintString(GetWorld(), "Attack!");
		UGameplayStatics::ApplyDamage(UGameplayStatics::GetPlayerPawn(GetWorld(), 0), 1.0f, GetController(), this, UZombieAttack::StaticClass());

		FTimerHandle UnusedHandle;
		GetWorld()->GetTimerManager().SetTimer(UnusedHandle, this, &AZombieBase::AttackCooldown, 3.0f, false);
		
		IsReadyToAttack = false;
	}
}

void AZombieBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if(UDVZGameInstance* GameInstanceReference = Cast<UDVZGameInstance>(GetGameInstance()))
	{
		GameInstanceReference->CurrentlyActiveRoom->Zombies.Remove(this);
		GameInstanceReference->CurrentlyActiveRoom->IsClearFromZombies();
	}
}

void AZombieBase::Delay()
{
	CharacterAnimation->SetSpriteColor(FLinearColor::White);
}

void AZombieBase::OnDamageZoneHit(UPrimitiveComponent* PrimitiveComponent, AActor* Actor, UPrimitiveComponent* PrimitiveComponent1, int I, bool bArg, const FHitResult& HitResult)
{
	Super::OnDamageZoneHit(PrimitiveComponent, Actor, PrimitiveComponent1, I, bArg, HitResult);

	if(ADoctorCharacter* DoctorReference = Cast<ADoctorCharacter>(Actor))
	{
		IsWithinAttackZone = true;
	}
}

void AZombieBase::OnDamageZoneExit(UPrimitiveComponent* PrimitiveComponent, AActor* Actor,
	UPrimitiveComponent* PrimitiveComponent1, int I)
{
	Super::OnDamageZoneExit(PrimitiveComponent, Actor, PrimitiveComponent1, I);

	if(ADoctorCharacter* DoctorReference = Cast<ADoctorCharacter>(Actor))
	{
		IsWithinAttackZone = false;
	}
}

void AZombieBase::AttackCooldown()
{
	UKismetSystemLibrary::PrintString(GetWorld(), "CD");

	IsReadyToAttack = true;
}


