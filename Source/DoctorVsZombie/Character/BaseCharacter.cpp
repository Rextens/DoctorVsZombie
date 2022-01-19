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
	}
	
	CharacterAnimation = CreateDefaultSubobject<UPixel2DComponent>(TEXT("CharacterLook"));
	CharacterAnimation->SetWorldRotation(FRotator(0.0f, 90.0f, 270.0f));
	CharacterAnimation->SetupAttachment(RootComponent);
	GetCapsuleComponent()->SetWorldScale3D(FVector(0.35f, 0.35f, 0.35f));

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));

	if(MovementComponent)
	{
		MovementComponent->SetUpdatedComponent(RootComponent);
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

	if (GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Falling)
	{
		UKismetSystemLibrary::PrintString(GetWorld(), "Ddddddddddddddddddddddddddddddd");
		
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	//	GetCapsuleComponent()->SetWorldRotation(FRotator(270.0f, 0.0f, 0.0f));
	}
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
