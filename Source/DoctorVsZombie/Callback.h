// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Character/Equipment/Item.h"
#include "Callback.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UCallback : public UInterface
{
    GENERATED_BODY()
};

class ICallback
{
    GENERATED_BODY()

public:
    UFUNCTION()
        virtual void AfterAnimation(class ADoctorCharacter* Caller) {};

    /** Add interface function declarations here */
};