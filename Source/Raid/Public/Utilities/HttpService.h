// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Json.h"
#include "JsonUtilities.h"
#include "HttpService.generated.h"

//!!!
//USTRUCT(s) should be moved to a different class
USTRUCT()
struct FRequest_Login {
	GENERATED_BODY()
	UPROPERTY() FString title;
	UPROPERTY() FString description;
	//UPROPERTY() FString email;
//UPROPERTY() FString password;

	FRequest_Login() {}
};

USTRUCT()
struct FResponse_Login {
	GENERATED_BODY()
	UPROPERTY() int id;
	UPROPERTY() FString name;
	UPROPERTY() FString hash;

	FResponse_Login() {}
};

UCLASS(Blueprintable, hideCategories = (Rendering, Replication, Input, Actor, "Actor Tick"))
class RAID_API AHttpService : public AActor
{
	GENERATED_BODY()
private:
	FHttpModule* Http;
	FString ApiBaseUrl = "http://138.68.16.123:8080/";

	FString AuthorizationHeader = TEXT("Authorization");
	void SetAuthorizationHash(FString Hash, TSharedRef<IHttpRequest>& Request);

	TSharedRef<IHttpRequest> RequestWithRoute(FString Subroute);
	void SetRequestHeaders(TSharedRef<IHttpRequest>& Request);

	TSharedRef<IHttpRequest> GetRequest(FString Subroute);
	TSharedRef<IHttpRequest> PostRequest(FString Subroute, FString ContentJsonString);
	void Send(TSharedRef<IHttpRequest>& Request);

	bool ResponseIsValid(FHttpResponsePtr Response, bool bWasSuccessful);

	template <typename StructType>
	void GetJsonStringFromStruct(StructType FilledStruct, FString& StringOutput);
	template <typename StructType>
	void GetStructFromJsonString(FHttpResponsePtr Response, StructType& StructOutput);



public:
	AHttpService();
	virtual void BeginPlay() override;

	void Tick(float DeltaTime);

	void Login(FRequest_Login LoginCredentials);
	void LoginResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
