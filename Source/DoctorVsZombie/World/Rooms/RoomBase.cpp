// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomBase.h"

#include "PaperTileMap.h"
#include "PaperTileMapComponent.h"

// Sets default values
ARoomBase::ARoomBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TileMapComponent = CreateDefaultSubobject<UPaperTileMapComponent>(TEXT("TileMapComponent"));

	static ConstructorHelpers::FObjectFinder<UPaperTileMap> LoadedTileMap(TEXT("/Game/Textures/Labo_TileMap"));

	if (LoadedTileMap.Object)
	{
		TileMapComponent->SetWorldRotation(FRotator(0.0f, 90.0f, 270.0f));
		TileMapComponent->SetTileMap(LoadedTileMap.Object);
	}
}

// Called when the game starts or when spawned
void ARoomBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARoomBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

