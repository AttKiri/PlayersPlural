// Fill out your copyright notice in the Description page of Project Settings.


#include "MGPickup.h"

#include "MGCharacter.h"

// Sets default values
AMGPickup::AMGPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//leave this till last, you can turn this off
	PrimaryActorTick.bCanEverTick = true;

	// need to close editor to do this
	//needed to show on server AND clients
	SetReplicates(true);

	//create the component 
	PickupTrigger = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	
	// set component to be root of the class
	SetRootComponent(PickupTrigger);

	//set default size of the trigger
	PickupTrigger->SetCapsuleRadius(100.0f);
	PickupTrigger->SetCapsuleHalfHeight(100.0f);

	// creating the static mesh component
	//without this the component won't exist or appear in the blueprint
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	// attach it to the actor by attaching ti to a component
	Mesh->SetupAttachment(RootComponent);

	//move the mesh up by default
	Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));

	// turn the collision off on mesh
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//default allowed pickup class at actor
	PickupActorClass = AActor::StaticClass();

	//set default for the rest set timer to 10 seconds
	ResetTime = 10.0f;

	MeshRotateSpeed = 50.0f;
	
}

void AMGPickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (!HasAuthority())
		return;

	if (OtherActor->GetClass()->IsChildOf(PickupActorClass))
		ActivatePickup(OtherActor);
}

void AMGPickup::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//spinning the mesh based on rotation speed
	Mesh->AddLocalRotation(FRotator(0.0f, MeshRotateSpeed * DeltaSeconds, 0.0f));
}


void AMGPickup::ActivatePickup(AActor* pickupActor)
{
	BP_OnActivePickup(pickupActor);

	DeactivatePickup();

	//checking if the reste time is greater than 0
	if (ResetTime > 0.0f)
	{
		//if so set timer to reactive the pickop
		GetWorld()->GetTimerManager().SetTimer(TH_ReactivateTimer, this, &AMGPickup::ReactivatePickup, ResetTime);
	}
}

void AMGPickup::ReactivatePickup_Implementation()
{
	// server version
	if (HasAuthority())
	{
		PickupTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}

	//regardless of server of client reveal mesh
	Mesh->SetVisibility(true,true);
}

void AMGPickup::DeactivatePickup_Implementation()
{
	// is this teh server version 
	if (HasAuthority())
	{
		//if so disable the collision so it can'e be collected
		PickupTrigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	// regardless of server or client hide the mesh
	Mesh->SetVisibility(false, true);
}

