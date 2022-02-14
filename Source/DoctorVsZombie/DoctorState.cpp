// Fill out your copyright notice in the Description page of Project Settings.


#include "DoctorState.h"
#include "Kismet/KismetSystemLibrary.h"

ADoctorState::ADoctorState()
{

}

void ADoctorState::BeginPlay()
{
	Super::BeginPlay();

	FItemStack Item;
	Item.ItemId = "DVZ.SyringePistol";
	Item.Stack = 1;
	Equipment.Add(Item);

	FItemStack Item3;
	Item3.ItemId = "DVZ.GreenMedicine";
	Item3.Stack = 3;
	Equipment.Add(Item3);
}