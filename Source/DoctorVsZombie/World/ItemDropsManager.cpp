// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemDropsManager.h"
#include "../Character/Equipment/Item.h"
#include "../Character/Equipment/Items/BlueMedicine.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../Character/DoctorCharacter.h"
#include "PaperGroupedSpriteComponent.h"

// Sets default values
AItemDropsManager::AItemDropsManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Items = CreateDefaultSubobject<UPaperGroupedSpriteComponent>(TEXT("Sprites"));
	Items->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	Items->OnComponentBeginOverlap.AddDynamic(this, &AItemDropsManager::OnBeginOverlap);
}

// Called when the game starts or when spawned
void AItemDropsManager::BeginPlay()
{
	Super::BeginPlay();

	if (UDVZGameInstance* GameInstanceReference = Cast<UDVZGameInstance>(GetGameInstance()))
	{
		GameInstanceReference->ItemDropManagerReference = this;
	}
}

// Called every frame
void AItemDropsManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemDropsManager::DropItem(FVector Location, FName ItemId)
{
	if (UDVZGameInstance* GameInstanceReference = Cast<UDVZGameInstance>(GetGameInstance()))
	{
		FTransform TempTransform;
		TempTransform.SetLocation(Location);
		TempTransform.SetRotation(FRotator(0.0f, 90.0f, 270.0f).Quaternion());

		if (GameInstanceReference->RegisteredItems.Contains(ItemId))
		{
			Items->AddInstance(TempTransform, GameInstanceReference->RegisteredItems[ItemId].RegisteredItem->ItemIcon);
			FItemStack TempStack;
			TempStack.ItemId = ItemId;
			TempStack.Stack = 1;
			ItemsStacks.Add(TempStack);
		}
	}
}

void AItemDropsManager::RemoveItem(const int32& Index)
{
	if (Items->GetInstanceCount() > Index && ItemsStacks.Num() > Index)
	{
		Items->RemoveInstance(Index);
		ItemsStacks.RemoveAt(Index);
	}
}

void AItemDropsManager::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ADoctorCharacter>(OtherActor))
	{
		if (UDVZGameInstance* GameInstanceReference = Cast<UDVZGameInstance>(GetGameInstance()))
		{
			if (ItemsStacks.Num() > SweepResult.Item && GameInstanceReference->RegisteredItems.Contains(ItemsStacks[SweepResult.Item].ItemId))
			{
				GameInstanceReference->RegisteredItems[ItemsStacks[SweepResult.Item].ItemId].RegisteredItem->Pickup(SweepResult.Item, this);
			}
		}
	}
}

