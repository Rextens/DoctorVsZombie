// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/SphereComponent.h"
#include "Pixel2DComponent.h"
#include "../DoctorCharacter.h"
#include "../../DoctorState.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "PaperFlipbook.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!CollisionComponent)
	{
		// Use a sphere as a simple collision representation.
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		// Set the sphere's collision radius.
		CollisionComponent->InitSphereRadius(15.0f);
		CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnHit);
		// Set the root component to be the collision component.
		RootComponent = CollisionComponent;
	}

	if (!ProjectileMovementComponent)
	{
		// Use this component to drive this projectile's movement.
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
		ProjectileMovementComponent->InitialSpeed = 1500.0f;
		ProjectileMovementComponent->MaxSpeed = 1500.0f;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = true;
		ProjectileMovementComponent->Bounciness = 0.3f;
		ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	}

	ProjectileLook = CreateDefaultSubobject<UPixel2DComponent>(TEXT("ProjectileLook"));
	
	if (ProjectileLook)
	{
		ProjectileLook->SetupAttachment(RootComponent);
		ProjectileLook->SetWorldRotation(FRotator(0.0f, 90.0f, 270.0f));
		static ConstructorHelpers::FObjectFinder<UPaperFlipbook> ProjectileLookObject(TEXT("/Game/TopDownCPP/Animation/Flipbooks/Doctor_Idle"));
		ProjectileLook->SetFlipbook(ProjectileLookObject.Object);
	}
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}
/*
void AProjectile::Shot(class ADoctorCharacter* caller)
{
	FHitResult HitResult;
	Cast<APlayerController>(Caller->GetController())->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, HitResult);

	if (UDVZGameInstance* GameInstanceReference = Cast<UDVZGameInstance>(Caller->GetGameInstance()))
	{
		if (ADoctorState* DoctorState = Cast<ADoctorState>(Caller->GetPlayerState()))
		{
			FVector Direction = UKismetMathLibrary::GetDirectionUnitVector(Caller->GetActorLocation(), HitResult.Location);

			UWorld* World = GetWorld();
			if (World)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = Caller;
				SpawnParams.Instigator = Caller->GetInstigator();

				// Spawn the projectile at the muzzle.
				AProjectile* Projectile = World->SpawnActor<AProjectile>(StaticClass(), Caller->GetActorLocation(), FRotator(0.0f, Direction.Rotation().Yaw, 0.0f), SpawnParams);
				Projectile->TypeOfDamage = UBlueMedicineDamageType::StaticClass();
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
