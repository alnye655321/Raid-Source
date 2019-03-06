// Fill out your copyright notice in the Description page of Project Settings.

#include "VrGuy.h"


// Sets default values
AVrGuy::AVrGuy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AVrGuy::BeginPlay()
{
	Super::BeginPlay();

	WorldHits = 0; //destruction mesh based
	WorldShotsFired = 0;
	WorldKills = 0;
	EnemyHits = 0;
	
}

// Called every frame
void AVrGuy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVrGuy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

int32 AVrGuy::GetWorldHits()
{
	return WorldHits;
}

void AVrGuy::SetWorldHits()
{
	WorldHits = WorldHits++;
}

int32 AVrGuy::GetWorldShotsFired()
{
	return WorldShotsFired;
}

void AVrGuy::SetWorldShotsFired()
{
	WorldShotsFired = WorldShotsFired++;
}

int32 AVrGuy::GetWorldKills()
{
	return WorldKills;
}

void AVrGuy::SetWorldKills(int32 NewWorldKills)
{
	WorldKills = NewWorldKills;
}

int32 AVrGuy::GetEnemyHits()
{
	return EnemyHits;
}

void AVrGuy::SetEnemyHits()
{
	EnemyHits = EnemyHits++;
}

