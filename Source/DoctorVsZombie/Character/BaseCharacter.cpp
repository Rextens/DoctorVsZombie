// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Pixel2DComponent.h"

#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/AudioComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	GetCapsuleComponent()->SetWorldRotation(FRotator(270.0f, 0.0f, 0.0f));

	CharacterAnimation = CreateDefaultSubobject<UPixel2DComponent>(TEXT("CharacterLook"));
	CharacterAnimation->SetWorldRotation(FRotator(0.0f, 90.0f, 0.0f));
	CharacterAnimation->SetupAttachment(RootComponent);

	Audio = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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
