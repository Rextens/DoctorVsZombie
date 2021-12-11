// Fill out your copyright notice in the Description page of Project Settings.


#include "UniversalWidget.h"
#include "../Character/DoctorCharacter.h"
#include "Kismet/GameplayStatics.h"

void UUniversalWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerCharacterReference = Cast<ADoctorCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void UUniversalWidget::close()
{
	this->RemoveFromParent();
}

void UUniversalWidget::open()
{
	this->AddToViewport();
	PlayerCharacterReference->OpenWidgets.Add(this);
}
