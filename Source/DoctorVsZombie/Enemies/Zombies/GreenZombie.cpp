// Fill out your copyright notice in the Description page of Project Settings.


#include "GreenZombie.h"
#include "Pixel2DComponent.h"
#include "PaperFlipbook.h"

#include "BlueZombie.h"

#include "../../Humans/HumanBase.h"
#include "../../DVZGameInstance.h"
#include "../../World/ItemDropsManager.h"
#include "DoctorVsZombie/DoctorState.h"
#include "DoctorVsZombie/Character/DoctorCharacter.h"
#include "DoctorVsZombie/Enemies/Fight/DamageTypes/ZombieAttack.h"
#include "Kismet/GameplayStatics.h"

#include "Kismet/KismetSystemLibrary.h"

AGreenZombie::AGreenZombie()
{
	static ConstructorHelpers::FClassFinder<AController> AiController(TEXT("Blueprint'/Game/NPC/Controllers/GreenZombieController'"));
	AIControllerClass = AiController.Class;

	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> GreenZombieFlipbook(TEXT("/Game/TopDownCPP/Animation/Spirtes/Zombie/Zombie1"));
	CharacterAnimation->SetFlipbook(GreenZombieFlipbook.Object);
	
	ZombieColor = ZombieType::GREEN;
	HealthPoints = 1;
}

void AGreenZombie::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	Super::TakeDamage(DamagedActor, Damage, DamageType, InstigatedBy, DamageCauser);
}

void AGreenZombie::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	if (UDVZGameInstance* GameInstanceReference = Cast<UDVZGameInstance>(GetGameInstance()))
	{
		int32 index = 0;
		if (GameInstanceReference->Enemies.Find(this, index))
		{
			GameInstanceReference->Enemies.RemoveAt(index);
		}

		if (GameInstanceReference->ItemDropManagerReference)
		{
			GameInstanceReference->ItemDropManagerReference->DropItem(GetActorLocation(), "DVZ.RedMedicine");
		}
	}
}

void AGreenZombie::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (AHumanBase* HumanReference = Cast<AHumanBase>(OtherActor))
	{
		if (UDVZGameInstance* GameInstanceReference = Cast<UDVZGameInstance>(GetGameInstance()))
		{
			FActorSpawnParameters SpawnInfo;
			if (GetWorld()->SpawnActor<ABlueZombie>(HumanReference->GetActorLocation(), FRotator(0.0f, 0.0f, 0.0f), SpawnInfo))
			{
				HumanReference->Destroy();

				int32 index = 0;
				GameInstanceReference->Humans.Find(HumanReference, index);
				GameInstanceReference->Humans.RemoveAt(index);
			}
		}
	}
	else if(ADoctorCharacter* DoctorReference = Cast<ADoctorCharacter>(OtherActor))
	{
	//	UGameplayStatics::ApplyDamage(DoctorReference, 1, GetController(), this, UZombieAttack::StaticClass());
	}
}