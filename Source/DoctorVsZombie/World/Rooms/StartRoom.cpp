// Fill out your copyright notice in the Description page of Project Settings.


#include "StartRoom.h"
#include "DoctorVsZombie/Character/DoctorCharacter.h"

AStartRoom::AStartRoom()
{
	RoomState = ERoomState::Clear;
}

void AStartRoom::BeginPlay()
{
	Super::BeginPlay();
	
	CharacterReference->SetActorLocation(FVector(Spawn.X * TileSize, Spawn.Y * TileSize, CharacterReference->GetActorLocation().Z));
}
