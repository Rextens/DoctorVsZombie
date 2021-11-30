// Fill out your copyright notice in the Description page of Project Settings.


#include "DoctorState.h"

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

	FItemStack Item2;
	Item2.ItemId = "DVZ.BlueMedicine";
	Item2.Stack = 10;
	Equipment.Add(Item2);

	FItemStack Item3;
	Item3.ItemId = "DVZ.GreenMedicine";
	Item3.Stack = 10;
	Equipment.Add(Item3);
}