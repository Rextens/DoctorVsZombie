// Fill out your copyright notice in the Description page of Project Settings.


#include "Room1.h"

ARoom1::ARoom1()
{
	LoadTileMap("/Game/Textures/Labo_TileMap");
	
	AddDoorLocation(FVector2D(22.0f, 22.0f), EDoorDirection::Top);
	AddDoorLocation(FVector2D(54.0f, 87.0f), EDoorDirection::Top);

	AddSpawnLocation(FVector2D(88, 21));
	AddSpawnLocation(FVector2D(88, 23));
	AddSpawnLocation(FVector2D(88, 25));
}
