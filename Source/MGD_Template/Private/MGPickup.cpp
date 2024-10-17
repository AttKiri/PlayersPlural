// Fill out your copyright notice in the Description page of Project Settings.


#include "MGPickup.h"

// Sets default values
AMGPickup::AMGPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//create the component 
	PickupTrigger = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	
	// set component to be root of the class
	SetRootComponent(PickupTrigger);

	//set default size of the trigger
	PickupTrigger->SetCapsuleRadius(100.0f);
	PickupTrigger->SetCapsuleHalfHeight(100.0f);


	
}


