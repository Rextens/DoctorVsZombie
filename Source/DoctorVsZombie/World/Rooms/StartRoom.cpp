// Fill out your copyright notice in the Description page of Project Settings.


#include "StartRoom.h"
#include "DoctorVsZombie/Character/DoctorCharacter.h"

AStartRoom::AStartRoom()
{
	RoomState = ERoomState::Clear;

	//LoadTileMap("/Game/Textures/Labo_TileMap");
	LoadTileMap("/Game/Textures/Lab_Asset_TileMap2");
	
	//AddDoorLocation(FVector2D(22.0f, 22.0f), EDoorDirection::Top);
	AddDoorLocation(FVector2D(40.0f, 41.0f), EDoorDirection::Top);
}

void AStartRoom::BeginPlay()
{
	Super::BeginPlay();
	
	CharacterReference->SetActorLocation(FVector(Spawn.X * TileSize, Spawn.Y * TileSize, 60.0f));
}
