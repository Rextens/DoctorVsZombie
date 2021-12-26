// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../DVZGameInstance.h"
#include "ItemDropsManager.generated.h"

UCLASS()
class DOCTORVSZOMBIE_API AItemDropsManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemDropsManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//friend void UItem::Pickup(const int32& Index, AItemDropsManager* ItemDropsManagerReference);
	friend class UItem;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DropItem(FVector Location, FName ItemId);

	void RemoveItem(const int32 &Index);

private:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

//VARIABLES
protected:
	UPROPERTY()
	TArray<FItemStack> ItemsStacks;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UPaperGroupedSpriteComponent* Items;

};
