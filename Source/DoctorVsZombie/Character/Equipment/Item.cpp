// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "PaperSpriteComponent.h"
#include "../../World/ItemDropsManager.h"
#include "../../DoctorState.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "../../DVZGameInstance.h"
#include "PaperSprite.h"

UItem::UItem()
{

}

void UItem::Pickup(const int32& Index, class AItemDropsManager* ItemDropsManagerReference)
{
	if (ADoctorState* PlayerStateReference = Cast<ADoctorState>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetPlayerState()))
	{
		PlayerStateReference->Equipment.Add(ItemDropsManagerReference->ItemsStacks[Index]);
	}
	ItemDropsManagerReference->RemoveItem(Index);
}

void UItem::Use(class ADoctorCharacter* Caller, FItemStack& ItemStackReference, const int32& index)
{

}

bool UItem::AddToStack(UPARAM(ref) TArray<FItemStack>& ItemList, const int32& Index, const int32& Amount)
{
	if (ItemList.Num() > Index)
	{
		if (ItemList[Index].Stack - Amount < 0)
		{
			return false;
		}
		else
		{
			ItemList[Index].Stack += Amount;

			if (ItemList[Index].Stack == 0)
			{
				ItemList.RemoveAt(Index);
			}
			return true;
		}
	}
	return false;
}
