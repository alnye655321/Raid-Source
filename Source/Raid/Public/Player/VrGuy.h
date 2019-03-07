// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "VrGuy.generated.h"

UCLASS()
class RAID_API AVrGuy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVrGuy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
		int32 WorldHits;

	UFUNCTION(BlueprintCallable, Category = "PlayerStats")
		int32 GetWorldHits();

	UFUNCTION(BlueprintCallable, Category = "PlayerStats")
		void SetWorldHits();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
		int32 WorldShotsFired;

	UFUNCTION(BlueprintCallable, Category = "PlayerStats")
		int32 GetWorldShotsFired();

	UFUNCTION(BlueprintCallable, Category = "PlayerStats")
		void SetWorldShotsFired();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
		int32 WorldKills;

	UFUNCTION(BlueprintCallable, Category = "PlayerStats")
		int32 GetWorldKills();

	UFUNCTION(BlueprintCallable, Category = "PlayerStats")
		void SetWorldKills(int32 NewWorldKills);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
		int32 EnemyHits;

	UFUNCTION(BlueprintCallable, Category = "PlayerStats")
		int32 GetEnemyHits();

	UFUNCTION(BlueprintCallable, Category = "PlayerStats")
		void SetEnemyHits();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStats")
		int32 WorldDamage;

	UFUNCTION(BlueprintCallable, Category = "PlayerStats")
		int32 GetWorldDamge();

	UFUNCTION(BlueprintCallable, Category = "PlayerStats")
		void SetWorldDamge(int32 MoreWorldDamage);
	   		
};
