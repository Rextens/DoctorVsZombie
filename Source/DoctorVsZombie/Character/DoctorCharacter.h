// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Fight/Weapons/Weapon.h"
#include "../Widgets/UniversalWidget.h"
#include "DoctorCharacter.generated.h"

/**
 * 
 */
UCLASS()
class DOCTORVSZOMBIE_API ADoctorCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	ADoctorCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//VARIABLES
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	UFUNCTION()
	void Fire(const FVector& DestinationLocation);

	UFUNCTION()
	void ThrowAnimation(UObject* Caller);

	//virtual void OnAnimHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) override;

	virtual void OnDamageZoneHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	void TakeDamageDelay();
	
//VARIABLES
};
