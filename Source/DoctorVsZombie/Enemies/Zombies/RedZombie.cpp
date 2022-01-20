// Fill out your copyright notice in the Description page of Project Settings.


#include "RedZombie.h"
#include "Pixel2DComponent.h"
#include "PaperFlipbook.h"

#include "GreenZombie.h"

#include "../../Humans/HumanBase.h"

#include "../../DVZGameInstance.h"
#include "../../World/ItemDropsManager.h"

ARedZombie::ARedZombie()
{
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> GreenZombieFlipbook(TEXT("/Game/TopDownCPP/Animation/Spirtes/Zombie/Zombie1"));
	CharacterAnimation->SetFlipbook(GreenZombieFlipbook.Object);

	CharacterAnimation->SetSpriteColor(FLinearColor::Red);

	ZombieColor = ZombieType::RED;
	HealthPoints = 1;
}

void ARedZombie::EndPlay(const EEndPlayReason::Type EndPlayReason)
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
			GameInstanceReference->ItemDropManagerReference->DropItem(GetActorLocation(), "DVZ.BlueMedicine");
		}
	}
}

void ARedZombie::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (AHumanBase* HumanReference = Cast<AHumanBase>(OtherActor))
	{
		if (UDVZGameInstance* GameInstanceReference = Cast<UDVZGameInstance>(GetGameInstance()))
		{
			FActorSpawnParameters SpawnInfo;
			if (GetWorld()->SpawnActor<AGreenZombie>(HumanReference->GetActorLocation(), FRotator(0.0f, 0.0f, 0.0f), SpawnInfo))
			{
				HumanReference->Destroy();

				int32 index = 0;
				GameInstanceReference->Humans.Find(HumanReference, index);
				GameInstanceReference->Humans.RemoveAt(index);
			}
		}
	}
}