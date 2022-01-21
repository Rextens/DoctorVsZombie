// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomBase.h"

#include "PaperTileMap.h"
#include "PaperTileMapComponent.h"
#include "DoctorVsZombie/DoctorState.h"
#include "DoctorVsZombie/Character/DoctorCharacter.h"
#include "DoctorVsZombie/Enemies/Zombies/BlueZombie.h"
#include "DoctorVsZombie/Enemies/Zombies/GreenZombie.h"
#include "DoctorVsZombie/Enemies/Zombies/RedZombie.h"
#include "DoctorVsZombie/Enemies/Zombies/ZombieBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ARoomBase::ARoomBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bCanAffectNavigationGeneration = true;

	TileMapComponent = CreateDefaultSubobject<UPaperTileMapComponent>(TEXT("TileMapComponent"));

	static ConstructorHelpers::FObjectFinder<UPaperTileMap> LoadedTileMap(TEXT("/Game/Textures/Labo_TileMap"));

	if (LoadedTileMap.Object)
	{
		TileMapComponent->SetWorldRotation(FRotator(0.0f, 90.0f, 270.0f));
		TileMapComponent->SetTileMap(LoadedTileMap.Object);
		TileMapComponent->OnComponentHit.AddDynamic(this, &ARoomBase::OnHit);

		int32 X, Y, TempLayers;
		TileMapComponent->GetMapSize(X, Y, TempLayers);
		
		TileMapComponent->SetRelativeLocation(FVector(Y * TileSize , 0.0f, 0.0f));
	}

	AddDoorLocation(FVector2D(68.0f, 2.0f), EDoorDirection::Top);
}

// Called when the game starts or when spawned
void ARoomBase::BeginPlay()
{
	Super::BeginPlay();
	
	CharacterReference = Cast<ADoctorCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	//SpawnZombies();
	//SpawnZombies();
}

// Called every frame
void ARoomBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector2D RelativeLocation;
	RelativeLocation.X = FMath::Floor((CharacterReference->GetActorLocation().X + 16.0f) / TileSize);
	RelativeLocation.Y = FMath::Floor((CharacterReference->GetActorLocation().Y + 16.0f) / TileSize);

	if(RoomState == ERoomState::Clear)
	{
		for(int32 i = 0; i < Doors.Num(); ++i)
		{
			if(Doors[i].Tile == RelativeLocation)
			{
				if(Doors[i].Room == nullptr)
				{
					Doors[i].Room = GetWorld()->SpawnActor<ARoomBase>(FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));
				
					for(int32 j = 0; j < Doors[i].Room->Doors.Num(); ++j)
					{
						if(Doors[i].Room->Doors[j].Room == nullptr)
						{
							Doors[i].DestinationTile = Doors[i].Room->Doors[j].Tile;
							Doors[i].Room->Doors[j].DestinationTile = Doors[i].Tile;
							Doors[i].Room->Doors[j].Room = this;
						}
					}
				}

				DisableActor(true);

				Doors[i].Room->DisableActor(false);

				if(Doors[i].Direction == EDoorDirection::Top)
				{
					CharacterReference->SetActorLocation(FVector(Doors[i].DestinationTile * TileSize, CharacterReference->GetActorLocation().Z) - FVector(TileSize, 0.0f, 0.0f));
				}
				else if(Doors[i].Direction == EDoorDirection::Right)
				{
					CharacterReference->SetActorLocation(FVector(Doors[i].DestinationTile * TileSize, CharacterReference->GetActorLocation().Z) - FVector(0.0f, TileSize, 0.0f));
				}
				else if(Doors[i].Direction == EDoorDirection::Bottom)
				{
					CharacterReference->SetActorLocation(FVector(Doors[i].DestinationTile * TileSize, CharacterReference->GetActorLocation().Z) + FVector(TileSize, 0.0f, 0.0f));
				}
				else if(Doors[i].Direction == EDoorDirection::Left)
				{
					CharacterReference->SetActorLocation(FVector(Doors[i].DestinationTile * TileSize, CharacterReference->GetActorLocation().Z) + FVector(0.0f, TileSize, 0.0f));
				}
			}
		}
	}
}

void ARoomBase::AddDoorLocation(FVector2D Tile, EDoorDirection Direction)
{
	FDoor TempDoor;
	TempDoor.Tile = Tile;
	TempDoor.Direction = Direction;
	//ConnectedRooms.Add(TempDoor);

	//DoorLocations.Add(Tile);
	//RoomsReferences.Add(nullptr);
	
	Doors.Add(TempDoor);
}

void ARoomBase::DisableActor(const bool& Disable)
{
	SetActorHiddenInGame(Disable);
	SetActorEnableCollision(!Disable);
	SetActorTickEnabled(!Disable);

	if(!Disable)
	{
		Cast<UDVZGameInstance>(GetGameInstance())->CurrentlyActiveRoom = this;
	}
	SpawnZombies();
}

void ARoomBase::SpawnZombies()
{
	if(RoomState == ERoomState::Infected)
	{
		int32 RedMedicine = 0;
		int32 GreenMedicine = 0;
		int32 BlueMedicine = 0;

		ADoctorState* DoctorStateReference = Cast<ADoctorState>(CharacterReference->GetPlayerState());
	
		for(int32 i = 0; i < DoctorStateReference->Equipment.Num(); ++i)
		{
			if(DoctorStateReference->Equipment[i].ItemId == "DVZ.RedMedicine")
			{
				++RedMedicine;
			}
			else if(DoctorStateReference->Equipment[i].ItemId == "DVZ.GreenMedicine")
			{
				++GreenMedicine;
			}
			else if(DoctorStateReference->Equipment[i].ItemId == "DVZ.BlueMedicine")
			{
				++BlueMedicine;
			}
		}

		if(RedMedicine > 0)
		{
		
		}
		if(GreenMedicine > 0)
		{
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			GetWorld()->SpawnActor<AZombieBase>(AGreenZombie::StaticClass(), FVector(64, 64, 60), FRotator(0.0f, 0.0f, 0.0f), SpawnParameters);	
			GetWorld()->SpawnActor<AZombieBase>(ABlueZombie::StaticClass(), FVector(64, 128, 60), FRotator(0.0f, 0.0f, 0.0f), SpawnParameters);
		}
		if(BlueMedicine > 0)
		{
		
		}
	}
}

void ARoomBase::IsClearFromZombies()
{
	if(Zombies.Num() == 0)
	{
		RoomState = ERoomState::Clear;
	}
}

void ARoomBase::OnHit(UPrimitiveComponent* PrimitiveComponent, AActor* Actor, UPrimitiveComponent* PrimitiveComponent1, FVector Vector, const FHitResult& HitResult)
{
	/*
	if(ADoctorCharacter* CharacterReference = Cast<ADoctorCharacter>(Actor))
	{
		FVector RelativeLocation = CharacterReference->GetActorLocation() - GetActorLocation();

		RelativeLocation.X = FMath::Floor(RelativeLocation.X / TileSize);
		RelativeLocation.Y = FMath::Floor(RelativeLocation.Y / TileSize);
		RelativeLocation.Z = FMath::Floor(RelativeLocation.Z / TileSize);
		
		UKismetSystemLibrary::PrintString(GetWorld(), RelativeLocation.ToString());
	}
	*/
}

