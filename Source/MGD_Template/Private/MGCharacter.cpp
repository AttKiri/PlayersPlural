// Fill out your copyright notice in the Description page of Project Settings.


#include "MGCharacter.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
AMGCharacter::AMGCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AMGCharacter::PMoveCharacter(FVector2D axis)
{
	// CREATE LOCAL ROTATION VARIABLE
	FRotator controlRot;

	// SET YAW TO SAME AS CONTROLLERS YAW
	controlRot.Yaw = GetControlRotation().Yaw;
	
	//move character forward and back
	AddMovementInput(UKismetMathLibrary:: GetForwardVector(controlRot), axis.Y);

	//MOVE CHARACTER RIGHT AND LEFT
	AddMovementInput(UKismetMathLibrary:: GetRightVector(controlRot), axis.X);
}

