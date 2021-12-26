// Fill out your copyright notice in the Description page of Project Settings.


#include "UniversalWidget.h"
#include "../DoctorVsZombiePlayerController.h"
#include "Kismet/GameplayStatics.h"

void UUniversalWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerControllerReference = Cast<ADoctorVsZombiePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void UUniversalWidget::Close()
{
	this->RemoveFromParent();
}

void UUniversalWidget::Open()
{
	this->AddToViewport();
	PlayerControllerReference->OpenWidgets.Add(this);
}
