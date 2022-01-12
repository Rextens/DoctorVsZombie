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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddDoorLocation(FVector2D Tile, EDoorDirection Direction);

	void DisableActor(const bool& Disable);

	void SpawnZombies();
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* PrimitiveComponent, AActor* Actor, UPrimitiveComponent* PrimitiveComponent1, FVector Vector, const FHitResult& HitResult);

	
//VARIABLES
	UPROPERTY()
	class UPaperTileMapComponent* TileMapComponent;
	
	TArray<class AZombieBase*> Zombies;

	TArray<FDoor> Doors;
	
	int32 TileSize = 32;

	UPROPERTY()
	class ADoctorCharacter* CharacterReference;

	FVector2D Spawn = FVector2D(18.0f, 46.0f);

	int32 Hardness = 0;
};
