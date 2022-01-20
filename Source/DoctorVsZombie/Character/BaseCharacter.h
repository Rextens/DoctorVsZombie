// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "DoctorVsZombie/Characte/Movement/MyPawnMovementComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "BaseCharacter.generated.h"

UCLASS()
class DOCTORVSZOMBIE_API ABaseCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void StopThrowing();

	UFUNCTION()
	virtual void TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

//VARIABLES
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UPixel2DComponent* CharacterAnimation;

	UPROPERTY()
	//UFloatingPawnMovement* MovementComponent;
	UMyPawnMovementComponent* MovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCapsuleComponent* CapsuleComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* MainCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* AdditionalCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCapsuleComponent* AdditionalCollision2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCapsuleComponent* AdditionalCollision3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAudioComponent* Audio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsMovingForwards = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsMovingRight = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsThrowing = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsShooting = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 HealthPoints = 0;
};
