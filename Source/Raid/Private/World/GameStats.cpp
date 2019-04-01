// Fill out your copyright notice in the Description page of Project Settings.

#include "GameStats.h"
#include "Raid.h"
#include "Utilities/HttpService.h"
#include "Player/VrGuy.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AGameStats::AGameStats()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

}

// Called when the game starts or when spawned
void AGameStats::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameStats::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

template <typename StructType>
void AGameStats::GetJsonStringFromStruct(StructType FilledStruct, FString& StringOutput) {
	FJsonObjectConverter::UStructToJsonObjectString(StructType::StaticStruct(), &FilledStruct, StringOutput, 0, 0);
}

template <typename StructType>
void AGameStats::GetStructFromJsonString(FHttpResponsePtr Response, StructType& StructOutput) {
	StructType StructData;
	FString JsonString = Response->GetContentAsString();
	FJsonObjectConverter::JsonObjectStringToUStruct<StructType>(JsonString, &StructOutput, 0, 0);
}

void AGameStats::SendWorldStatsHttp()
{
	APawn* VrPawn = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn();
	AVrGuy* VrGuy = Cast<AVrGuy>(VrPawn);

	int32 WorldHits = 0;
	int32 WorldShotsFired = 0;
	int32 WorldKills = 0;
	int32 EnemyHits = 0;
	int32 WorldDamage = 0;

	if (VrGuy != NULL)
	{
		WorldHits = VrGuy->GetWorldHits();
		WorldShotsFired = VrGuy->GetWorldShotsFired();
		WorldKills = VrGuy->GetWorldKills();
		EnemyHits = VrGuy->GetEnemyHits();
		WorldDamage = VrGuy->GetWorldDamge();
	}


	TArray<AActor*> FoundHttpSerrvices;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHttpService::StaticClass(), FoundHttpSerrvices);

	if (FoundHttpSerrvices.Num() > 0)
	{
		FString ContentJsonString;
		AActor* Actor = FoundHttpSerrvices[0];
		AHttpService* HttpService = Cast<AHttpService>(Actor);

		FRequest_Logout LogoutCredentials;
		LogoutCredentials.sessionId = HttpService->getSession();
		LogoutCredentials.worldHits = WorldHits;
		LogoutCredentials.worldShotsFired = WorldShotsFired;
		LogoutCredentials.worldKills = WorldKills;
		LogoutCredentials.gameTime = GetWorld()->GetTimeSeconds();
		LogoutCredentials.enemyHits = EnemyHits;
		LogoutCredentials.worldDamage = WorldDamage;

		GetJsonStringFromStruct<FRequest_Logout>(LogoutCredentials, ContentJsonString);

		HttpService->Logout(ContentJsonString);
	}
}






