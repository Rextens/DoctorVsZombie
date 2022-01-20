// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Pixel2DComponent.h"

#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/AudioComponent.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Fight/DamageTypes/DamageInterface.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MainCollisions"));
	if(CapsuleComponent)
	{
		RootComponent = CapsuleComponent;
		CapsuleComponent->SetWorldScale3D(FVector(0.35f, 0.35f, 0.35f));
		CapsuleComponent->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
		CapsuleComponent->SetCollisionProfileName(TEXT("BlockAll"));
		CapsuleComponent->SetWorldRotation(FRotator(0.0f, 90.0f, 270.0f));
		CapsuleComponent->SetCapsuleHalfHeight(75);
		CapsuleComponent->SetCapsuleRadius(28);
		CapsuleComponent->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	}
	
	
/*
	MainCollision = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainCollision"));
	RootComponent = MainCollision;
	//MainCollision->SetRelativeLocation(FVector(0.0f, 0.0f, -75.0f));
	MainCollision->SetWorldScale3D(FVector(3.0175f * 0.35, 1.0f * 0.35, 1.515f * 0.35));
	MainCollision->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);

	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_NarrowCapsule_2.Shape_NarrowCapsule_2'"));

	if(MeshObj.Object)
	{
		
		MainCollision->SetStaticMesh(MeshObj.Object);
	}
	*/
	
	CharacterAnimation = CreateDefaultSubobject<UPixel2DComponent>(TEXT("CharacterLook"));
	if(CharacterAnimation)
	{
	//	CharacterAnimation->SetAbsolute(false, true, true);
		CharacterAnimation->SetRelativeLocation(FVector(0.0f, 0.0f, 6.0f));
	//	CharacterAnimation->SetWorldRotation(FRotator(0.0f, 90.0f, 270.0f));
		CharacterAnimation->SetRelativeScale3D(FVector(1.5f, 1.5f, 1.5f));
		CharacterAnimation->SetCollisionProfileName(TEXT("NoCollision"));
		CharacterAnimation->SetupAttachment(RootComponent);
	}

	
//	CharacterAnimation->SetWorldRotation(FRotator(0.0f, 90.0f, 270.0f));
//	GetCapsuleComponent()->SetWorldScale3D(FVector(0.35f, 0.35f, 0.35f));

	MovementComponent = CreateDefaultSubobject<UMyPawnMovementComponent>(TEXT("MovementComponent"));

	if(MovementComponent)
	{
		MovementComponent->SetUpdatedComponent(RootComponent);
		MovementComponent->MaxSpeed = 400;
		MovementComponent->bSnapToPlaneAtStart = true;
		MovementComponent->bConstrainToPlane = true;
		MovementComponent->ConstrainLocationToPlane(FVector(10.0f, 10.0f, 60.0f));
	}
	
	Audio = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));

	OnTakeAnyDamage.AddDynamic(this, &ABaseCharacter::TakeDamage);

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(MainCollision)
	{
		MainCollision->SetCollisionProfileName(TEXT("BlockAll"));
	}
	
	/*
	if (GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Falling)
	{
		UKismetSystemLibrary::PrintString(GetWorld(), "Ddddddddddddddddddddddddddddddd");
		
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	//	GetCapsuleComponent()->SetWorldRotation(FRotator(270.0f, 0.0f, 0.0f));
	}
	*/
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABaseCharacter::StopThrowing()
{
	IsThrowing = false;
}


void ABaseCharacter::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	//UKismetSystemLibrary::PrintString(GetWorld(), "Go to sleep already!");

	const IDamageInterface* ImplementedInterface = Cast<const IDamageInterface>(DamageType);
	if (ImplementedInterface)
	{
		ImplementedInterface->DealDamage(this);
	}
}
