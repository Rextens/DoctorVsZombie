// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanBase.h"
#include "PaperFlipbook.h"
#include "Pixel2DComponent.h"

AHumanBase::AHumanBase()
{
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook> HumanAnimation(TEXT("/Game/Humans/Sprites/Human"));

	if (HumanAnimation.Object)
	{
		CharacterAnimation->SetFlipbook(HumanAnimation.Object);
		CharacterAnimation->SetWorldScale3D(FVector(0.285f, 0.285f, 0.285f));
	}
}