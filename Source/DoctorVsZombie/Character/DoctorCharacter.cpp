// Fill out your copyright notice in the Description page of Project Settings.


#include "DoctorCharacter.h"

#include "Pixel2DComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "../DVZGameInstance.h"
#include "../DoctorState.h"
#include "../Callback.h"
#include "../Saves/Character/CharacterSave.h"

#include "Fight/Projectile.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "Camera/CameraComponent.h"

ADoctorCharacter::ADoctorCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false;

	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false;

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ADoctorCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ADoctorCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADoctorCharacter::Fire(const FVector& DestinationLocation)
{
	if (UDVZGameInstance* GameInstanceReference = Cast<UDVZGameInstance>(GetGameInstance()))
	{
		if (ADoctorState* DoctorState = Cast<ADoctorState>(GetPlayerState()))
		{
		//	GameInstanceReference->Weapons[DoctorState->ChosenWeapon].Weapon->Shoot(GameInstanceReference, DoctorState, DestinationLocation);
		}
	}
	/*
	if (UDVZGameInstance* GameInstanceReference = Cast<UDVZGameInstance>(GetGameInstance()))
	{
		if (ADoctorState* DoctorState = Cast<ADoctorState>(GetPlayerState()))
		{
			if (ProjectileClass)
			{
				FVector Direction = UKismetMathLibrary::GetDirectionUnitVector(GetActorLocation(), DestinationLocation);

				UWorld* World = GetWorld();
				if (World)
				{
					FActorSpawnParameters SpawnParams;
					SpawnParams.Owner = this;
					SpawnParams.Instigator = GetInstigator();

					// Spawn the projectile at the muzzle.
					AProjectile* Projectile = World->SpawnActor<AProjectile>(GameInstanceReference->Weapons[DoctorState->ChosenWeapon].Weapon->ProjectileClass, GetActorLocation(), FRotator(0.0f, Direction.Rotation().Yaw, 0.0f), SpawnParams);
					Projectile->TypeOfDamage = GameInstanceReference->DamageTypes[DoctorState->ChosenDamageType].ChoosenDamage;
					Projectile->AfterDamageTypeSet();

					if (Projectile)
					{
						// Set the projectile's initial trajectory.
						Projectile->FireInDirection(FVector(Direction.X, Direction.Y, 0.0f));
					}
				}
			}
		}
	}
	*/
}

void ADoctorCharacter::ThrowAnimation(UObject* Caller)
{
	if (Cast<ICallback>(Caller))
	{
		
	}
}

void ADoctorCharacter::OnDamageZoneHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
//	Super::OnDamageZoneHit(HitComponent, OtherActor, OtherComponent, NormalImpulse, Hit);

	
}

void ADoctorCharacter::TakeDamageDelay()
{
	CharacterAnimation->SetSpriteColor(FLinearColor::White);
}

