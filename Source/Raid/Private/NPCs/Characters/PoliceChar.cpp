// Fill out your copyright notice in the Description page of Project Settings.

#include "PoliceChar.h"
#include "Raid.h"
#include "AI/Police/PoliceAI.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
APoliceChar::APoliceChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APoliceChar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APoliceChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APoliceChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

