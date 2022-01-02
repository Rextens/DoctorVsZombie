// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieSaliva.h"

#include "Kismet/GameplayStatics.h"

#include "../DamageTypes/SalivaDamageType.h"
#include "../../EnemyBase.h"
#include "../../../Character/DoctorCharacter.h"


// Sets default values
AZombieSaliva::AZombieSaliva()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AZombieSaliva::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AZombieSaliva::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AZombieSaliva::OnHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ADoctorCharacter* HitEnemy = Cast<ADoctorCharacter>(OtherActor))
	{
		UGameplayStatics::ApplyDamage(HitEnemy, 1, UGameplayStatics::GetPlayerController(GetWorld(), 0), this, USalivaDamageType::StaticClass());
	}

	if (!(Cast<AEnemyBase>(OtherActor)))
	{
		Destroy();
	}
}

