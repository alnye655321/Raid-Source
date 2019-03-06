// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Json.h"
#include "JsonUtilities.h"
#include "GameStats.generated.h"

USTRUCT()
struct FRequest_Logout {
	GENERATED_BODY()
	UPROPERTY() int32 sessionId;
	UPROPERTY() int32 worldHits;
	UPROPERTY() int32 worldShotsFired;
	UPROPERTY() int32 worldKills;
	UPROPERTY() float gameTime;
	UPROPERTY() int32 enemyHits;

	FRequest_Logout() {}
};

USTRUCT()
struct FResponse_Logout {
	GENERATED_BODY()
	UPROPERTY() int id;
	UPROPERTY() FString name;
	UPROPERTY() FString hash;

	FResponse_Logout() {}
};

UCLASS()
class RAID_API AGameStats : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameStats();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	class AHttpService* GetHttpService() const;

	UFUNCTION(BlueprintCallable, Category = "WorldStats")
		void SendWorldStatsHttp();

private:
	template <typename StructType>
	void GetJsonStringFromStruct(StructType FilledStruct, FString& StringOutput);
	template <typename StructType>
	void GetStructFromJsonString(FHttpResponsePtr Response, StructType& StructOutput);

	
	
};
