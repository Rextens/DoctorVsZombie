// Fill out your copyright notice in the Description page of Project Settings.


#include "Street.h"

AStreet::AStreet() {
	LoadTileMap("/Game/Textures/Street_asset_TileMap1");
	AddDoorLocation(FVector2D(45.0f, 26.0f), EDoorDirection::Top);
	AddDoorLocation(FVector2D(46.0f, 47.0f), EDoorDirection::Top);

	AddSpawnLocation(FVector2D(34, 21));
	AddSpawnLocation(FVector2D(31, 36));
	AddSpawnLocation(FVector2D(48, 44));
}
