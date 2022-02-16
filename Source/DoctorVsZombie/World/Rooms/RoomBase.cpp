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
	//bCanAffectNavigationGeneration = true;
	
	

	TileMapComponent = CreateDefaultSubobject<UPaperTileMapComponent>(TEXT("TileMapComponent"));

	static ConstructorHelpers::FObjectFinder<UPaperTileMap> LoadedTileMap(TEXT("/Game/Textures/Labo_TileMap"));

	if (LoadedTileMap.Object)
	{
		TileMapComponent->SetWorldRotation(FRotator(0.0f, 90.0f, 270.0f));
		TileMapComponent->SetTileMap(LoadedTileMap.Object);
		TileMapComponent->OnComponentHit.AddDynamic(this, &ARoomBase::OnHit);

		int32 X, Y, TempLayers;
		TileMapComponent->GetMapSize(X, Y, TempLayers);

		TilesNumber.X = X;
		TilesNumber.Y = Y;
		
		
		TileMapComponent->SetRelativeLocation(FVector(Y * TileSize , 0.0f, 0.0f));
	}

	AddDoorLocation(FVector2D(2.0f, 2.0f), EDoorDirection::Top);
	AddDoorLocation(FVector2D(34.0f, 67.0f), EDoorDirection::Top);
}

// Called when the game starts or when spawned
void ARoomBase::BeginPlay()
{
	Super::BeginPlay();
	
	CharacterReference = Cast<ADoctorCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));


	if(UDVZGameInstance* GameInstanceReference = Cast<UDVZGameInstance>(GetGameInstance()))
	{
		GameInstanceReference->ExistingRooms.Add(this);
	}
	//SpawnZombies();
	//SpawnZombies();
}

// Called every frame
void ARoomBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector2D RelativeLocation;
	RelativeLocation.X = FMath::Floor((CharacterReference->GetActorLocation().X + 16.0f - GetActualLocation().X) / TileSize);
	RelativeLocation.Y = FMath::Floor((CharacterReference->GetActorLocation().Y + 16.0f) / TileSize);
	
	if(RoomState == ERoomState::Clear)
	{
		for(int32 i = 0; i < Doors.Num(); ++i)
		{
			if(Doors[i].Tile == RelativeLocation)
			{
				if(Doors[i].Room == nullptr)
				{
					if(UDVZGameInstance* GameInstanceReference = Cast<UDVZGameInstance>(GetGameInstance()))
					{
						//GameInstanceReference->RegisteredRooms.GenerateKeyArray()

						int32 Iterator = 0;

						int32 ChoosenRoom = FMath::RandRange(1, GameInstanceReference->RegisteredRooms.Num() - 1);

						TSubclassOf<ARoomBase> RandomRoom;
						
						for(auto& Pair : GameInstanceReference->RegisteredRooms)
						{
							if(Iterator == ChoosenRoom)
							{
								RandomRoom = Pair.Value.RegisteredItem;

								UKismetSystemLibrary::PrintString(GetWorld(), FString::FromInt(Iterator) + " " + Pair.Key.ToString());
								
								break;
							}
							
							++Iterator;
						}
						
						Doors[i].Room = GetWorld()->SpawnActor<ARoomBase>(RandomRoom, FVector(GameInstanceReference->ExistingRooms.Num() * 5000.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));

						for(int32 j = 0; j < Doors[i].Room->Doors.Num(); ++j)
						{
							if(Doors[i].Room->Doors[j].Room == nullptr)
							{
								Doors[i].DestinationTile = Doors[i].Room->Doors[j].Tile;
								Doors[i].Room->Doors[j].DestinationTile = Doors[i].Tile;
								Doors[i].Room->Doors[j].Room = this;

								break;	
							}
						}
					}
				}

				DisableActor(true);

				Doors[i].Room->DisableActor(false);
				
				FVector2D Destination = FVector2D(Doors[i].DestinationTile.X * TileSize + Doors[i].Room->GetActorLocation().X - TilesNumber.Y * TileSize, Doors[i].DestinationTile.Y * TileSize);

				if(Doors[i].Direction == EDoorDirection::Top)
				{
					CharacterReference->SetActorLocation(FVector(Destination, CharacterReference->GetActorLocation().Z) - FVector(TileSize, 0.0f, 0.0f));

					break;
				}
				else if(Doors[i].Direction == EDoorDirection::Right)
				{
					CharacterReference->SetActorLocation(FVector(Destination, CharacterReference->GetActorLocation().Z) - FVector(0.0f, TileSize, 0.0f));

					break;
				}
				else if(Doors[i].Direction == EDoorDirection::Bottom)
				{
					CharacterReference->SetActorLocation(FVector(Destination, CharacterReference->GetActorLocation().Z) + FVector(TileSize, 0.0f, 0.0f));

					break;
				}
				else if(Doors[i].Direction == EDoorDirection::Left)
				{
					CharacterReference->SetActorLocation(FVector(Destination, CharacterReference->GetActorLocation().Z) + FVector(0.0f, TileSize, 0.0f));

					break;
				}
			}
		}
	}
}

void ARoomBase::AddDoorLocation(FVector2D Tile, EDoorDirection Direction)
{
	int32 X, Y, TempLayers;
	TileMapComponent->GetMapSize(X, Y, TempLayers);

	FDoor TempDoor;
	TempDoor.Tile = FVector2D(X - Tile.X, Tile.Y);
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
				RedMedicine += DoctorStateReference->Equipment[i].Stack;
			}
			else if(DoctorStateReference->Equipment[i].ItemId == "DVZ.GreenMedicine")
			{
				GreenMedicine += DoctorStateReference->Equipment[i].Stack;
			}
			else if(DoctorStateReference->Equipment[i].ItemId == "DVZ.BlueMedicine")
			{
				BlueMedicine += DoctorStateReference->Equipment[i].Stack;
			}
		}

		TArray<int32> AllowedScenarios;

		if(RedMedicine > 0)
		{
			AllowedScenarios.Add(0);
			/*
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			AZombieBase* SpawnedZombie1 = GetWorld()->SpawnActor<AZombieBase>(ARedZombie::StaticClass(), FVector(GetActualLocation().X + 64, 64, 60), FRotator(0.0f, 0.0f, 0.0f), SpawnParameters);	
			SpawnedZombie1->HealthPoints = GreenMedicine - 1;
			
			GetWorld()->SpawnActor<AZombieBase>(AGreenZombie::StaticClass(), FVector( GetActualLocation().X + 64, 128, 60), FRotator(0.0f, 0.0f, 0.0f), SpawnParameters);
			*/
		}
		if(GreenMedicine > 0)
		{
			AllowedScenarios.Add(1);
			/*
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			AZombieBase* SpawnedZombie1 = GetWorld()->SpawnActor<AZombieBase>(AGreenZombie::StaticClass(), FVector(GetActualLocation().X + 64, 64, 60), FRotator(0.0f, 0.0f, 0.0f), SpawnParameters);	
			SpawnedZombie1->HealthPoints = GreenMedicine - 1;
			
			GetWorld()->SpawnActor<AZombieBase>(ABlueZombie::StaticClass(), FVector( GetActualLocation().X + 64, 128, 60), FRotator(0.0f, 0.0f, 0.0f), SpawnParameters);
			*/
		}
		if(BlueMedicine > 0)
		{
			AllowedScenarios.Add(2);
			/*
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			AZombieBase* SpawnedZombie1 = GetWorld()->SpawnActor<AZombieBase>(ABlueZombie::StaticClass(), FVector(GetActualLocation().X + 64, 64, 60), FRotator(0.0f, 0.0f, 0.0f), SpawnParameters);	
			SpawnedZombie1->HealthPoints = GreenMedicine - 1;
			
			GetWorld()->SpawnActor<AZombieBase>(ARedZombie::StaticClass(), FVector( GetActualLocation().X + 64, 128, 60), FRotator(0.0f, 0.0f, 0.0f), SpawnParameters);
			*/
		}

		if(AllowedScenarios.Num() > 0)
		{
			int32 ChoosenScenario = FMath::RandRange(0, AllowedScenarios.Num() - 1);

			if(AllowedScenarios[ChoosenScenario] == 0)
			{
				FActorSpawnParameters SpawnParameters;
				SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				for(int32 i = 0; i < RedMedicine; ++i)
				{
					AZombieBase* SpawnedZombie1 = GetWorld()->SpawnActor<AZombieBase>(ARedZombie::StaticClass(), FVector(GetActualLocation().X + 64, Cast<UDVZGameInstance>(GetGameInstance())->Enemies.Num() * 64, 60), FRotator(0.0f, 0.0f, 0.0f), SpawnParameters);
				}
			
				GetWorld()->SpawnActor<AZombieBase>(AGreenZombie::StaticClass(), FVector( GetActualLocation().X + 64, Cast<UDVZGameInstance>(GetGameInstance())->Enemies.Num() * 64, 60), FRotator(0.0f, 0.0f, 0.0f), SpawnParameters);
			}
			else if(AllowedScenarios[ChoosenScenario] == 1)
			{
				FActorSpawnParameters SpawnParameters;
				SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				for(int32 i = 0; i < GreenMedicine; ++i)
				{
					UKismetSystemLibrary::PrintString(GetWorld(), "dddddddddddddddd");
					AZombieBase* SpawnedZombie1 = GetWorld()->SpawnActor<AZombieBase>(AGreenZombie::StaticClass(), FVector(GetActualLocation().X + 64, Cast<UDVZGameInstance>(GetGameInstance())->Enemies.Num() * 64, 60), FRotator(0.0f, 0.0f, 0.0f), SpawnParameters);
				}
			
				GetWorld()->SpawnActor<AZombieBase>(ABlueZombie::StaticClass(), FVector( GetActualLocation().X + 64, Cast<UDVZGameInstance>(GetGameInstance())->Enemies.Num() * 64, 60), FRotator(0.0f, 0.0f, 0.0f), SpawnParameters);
	
			}
			else if(AllowedScenarios[ChoosenScenario] == 2)
			{
				FActorSpawnParameters SpawnParameters;
				SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				for(int32 i = 0; i < BlueMedicine; ++i)
				{
					AZombieBase* SpawnedZombie1 = GetWorld()->SpawnActor<AZombieBase>(ABlueZombie::StaticClass(), FVector(GetActualLocation().X + 64, Cast<UDVZGameInstance>(GetGameInstance())->Enemies.Num() * 64, 60), FRotator(0.0f, 0.0f, 0.0f), SpawnParameters);
				}
			
				GetWorld()->SpawnActor<AZombieBase>(ARedZombie::StaticClass(), FVector( GetActualLocation().X + 64, Cast<UDVZGameInstance>(GetGameInstance())->Enemies.Num() * 64, 60), FRotator(0.0f, 0.0f, 0.0f), SpawnParameters);
	
			}
		}
		else
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

FVector ARoomBase::GetActualLocation()
{
	return FVector(GetActorLocation().X - TilesNumber.Y * TileSize, GetActorLocation().Y, GetActorLocation().Z);
}

