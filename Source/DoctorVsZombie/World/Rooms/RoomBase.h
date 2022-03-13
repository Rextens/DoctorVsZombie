// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoomBase.generated.h"

UENUM()
enum EDoorDirection
{
	Top,
	Right,
	Bottom,
	Left
};

UENUM()
enum ERoomState
{
	Infected,
	Clear
};

class ARoomBase;

USTRUCT()
struct FDoor
{
	GENERATED_BODY()

	FVector2D Tile;

	FVector2D DestinationTile;

	EDoorDirection Direction;

	UPROPERTY()
	ARoomBase* Room = nullptr;
};

USTRUCT()
struct FZombieSpawn
{
	GENERATED_BODY()

	FVector2D SpawnLocation;

	bool IsUsed = false;
};

UCLASS()
class DOCTORVSZOMBIE_API ARoomBase : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ARoomBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void LoadTileMap(const FName& Path);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddDoorLocation(FVector2D Tile, EDoorDirection Direction);

	void DisableActor(const bool& Disable);

	void SpawnZombies();
	void AddSpawnLocation(const FVector2D& Tile);

	void IsClearFromZombies();
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* PrimitiveComponent, AActor* Actor, UPrimitiveComponent* PrimitiveComponent1, FVector Vector, const FHitResult& HitResult);

	UFUNCTION()
	FVector GetActualLocation();
	
//VARIABLES
	UPROPERTY()
	class UPaperTileMapComponent* TileMapComponent;

	UPROPERTY(EditAnywhere)
	TArray<class AZombieBase*> Zombies;

	TArray<FDoor> Doors;

	TArray<FZombieSpawn> PossibleSpawns;
	
	int32 TileSize = 32;

	UPROPERTY()
	class ADoctorCharacter* CharacterReference;

	FVector2D Spawn = FVector2D(41.0f, 40.0f);

	int32 Hardness = 0;

	FVector2D TilesNumber;
	
	ERoomState RoomState = ERoomState::Infected;
};
