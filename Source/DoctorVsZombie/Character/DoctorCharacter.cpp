// Fill out your copyright notice in the Description page of Project Settings.


#include "DoctorCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Fight/Projectile.h"
#include "../DVZGameInstance.h"
#include "../DoctorState.h"
#include "Kismet/KismetMathLibrary.h"
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
			if (ProjectileClass)
			{
				// Set MuzzleOffset to spawn projectiles slightly in front of the camera.
				//MuzzleOffset.Set(100.0f, 0.0f, 0.0f);

				// Transform MuzzleOffset from camera space to world space.

				FVector Direction = UKismetMathLibrary::GetDirectionUnitVector(GetActorLocation(), DestinationLocation);

				//FVector MuzzleLocation = GetActorLocation() + FTransform(Direction).TransformVector( * 10.0f);

				// Skew the aim to be slightly upwards.

				UWorld* World = GetWorld();
				if (World)
				{
					FActorSpawnParameters SpawnParams;
					SpawnParams.Owner = this;
					SpawnParams.Instigator = GetInstigator();

					// Spawn the projectile at the muzzle.
					AProjectile* Projectile = World->SpawnActor<AProjectile>(GameInstanceReference->Weapons[DoctorState->ChosenWeapon].ChoosenWeapon, GetActorLocation(), Direction.Rotation(), SpawnParams);
					if (Projectile)
					{
						// Set the projectile's initial trajectory.
						Projectile->FireInDirection(FVector(Direction.X, Direction.Y, 0.0f));
					}
				}
			}
		}
	}
}
