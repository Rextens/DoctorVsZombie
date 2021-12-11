// Fill out your copyright notice in the Description page of Project Settings.


#include "RedZombie.h"

#include "../../DVZGameInstance.h"
#include "../../World/ItemDropsManager.h"

void ARedZombie::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (UDVZGameInstance* GameInstanceReference = Cast<UDVZGameInstance>(GetGameInstance()))
	{
		int32 index = 0;
		if (GameInstanceReference->Enemies.Find(this, index))
		{
			GameInstanceReference->Enemies.RemoveAt(index);
		}

		if (GameInstanceReference->ItemDropManagerReference)
		{
			GameInstanceReference->ItemDropManagerReference->DropItem(GetActorLocation(), "DVZ.GreenMedicine");
		}
	}
}