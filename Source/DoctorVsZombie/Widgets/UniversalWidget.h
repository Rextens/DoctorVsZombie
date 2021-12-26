// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UniversalWidget.generated.h"

/**
 * 
 */
UCLASS()
class DOCTORVSZOMBIE_API UUniversalWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class ADoctorVsZombiePlayerController* PlayerControllerReference;;

	virtual void Close();
	virtual void Open();
};
