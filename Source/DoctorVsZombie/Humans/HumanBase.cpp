// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanBase.h"
#include "PaperFlipbook.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../DVZGameInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Pixel2DComponent.h"

AHumanBase::AHumanBase()
{
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> HumanAnimation(TEXT("/Game/Humans/Sprites/Human"));

	if (HumanAnimation.Object)
	{
		CharacterAnimation->SetFlipbook(HumanAnimation.Object);
		CharacterAnimation->SetWorldScale3D(FVector(0.285f, 0.285f, 0.285f));
	}

	static ConstructorHelpers::FClassFinder<AController> AiController(TEXT("Blueprint'/Game/NPC/Humans/HumanController'"));

	AIControllerClass = AiController.Class;
	bUseControllerRotationYaw = false;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	FNavAvoidanceMask test;
	test.bGroup0 = false;

	FNavAvoidanceMask test1;
	test1.bGroup1 = false;

//	GetCharacterMovement()->GroupsToIgnore = test;

//	GetCharacterMovement()->AvoidanceGroup = test1;
}

void AHumanBase::BeginPlay()
{
	Super::BeginPlay();

	if (UDVZGameInstance* GameInstanceReference = Cast<UDVZGameInstance>(GetGameInstance()))
	{
		GameInstanceReference->Humans.Add(this);
	}
}

