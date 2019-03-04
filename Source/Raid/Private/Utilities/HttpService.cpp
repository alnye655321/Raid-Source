// Fill out your copyright notice in the Description page of Project Settings.

#include "Raid.h"
#include "HttpService.h"
#include <random>
#include "World/GameStats.h"
#include "../../Public/Utilities/HttpService.h"

std::random_device rd;     // only used once to initialise (seed) engine
std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
std::uniform_int_distribution<int> uni(1,999999999); // guaranteed unbiased


// Sets default values
AHttpService::AHttpService()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AHttpService::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("This a test HTTP call. Blueprint class is in level!"));


	Http = &FHttpModule::Get();

	FString testTitle = "unreal";
	FString testDescription = "test unreal";
	FString userName = "wiggles";

	auto random_integer = uni(rng);
	setSession(random_integer);
	

	FRequest_Login LoginCredentials;
	LoginCredentials.title = testTitle;
	LoginCredentials.description = testDescription;
	LoginCredentials.userName = userName;
	LoginCredentials.sessionId = random_integer;

	Login(LoginCredentials);

	//FString ContentJsonString;
	//GetJsonStringFromStruct<FRequest_Login>(LoginCredentials, ContentJsonString);

	//TSharedRef<IHttpRequest> Request = PostRequest("user/login", ContentJsonString);
	//Request->OnProcessRequestComplete().BindUObject(this, &AHttpService::LoginResponse);
	//Send(Request);

	//TSharedRef<IHttpRequest> Request = GetRequest("user/" + id + "/inventory");

	// You can uncomment this out for testing.
	//FRequest_Login LoginCredentials;
	//LoginCredentials.email = TEXT("asdf@asdf.com");
	//LoginCredentials.password = TEXT("asdfasdf");
	//Login(LoginCredentials);
	
}

/**************************************************************************************************************************/

TSharedRef<IHttpRequest> AHttpService::RequestWithRoute(FString Subroute) {
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->SetURL(ApiBaseUrl + Subroute);
	SetRequestHeaders(Request);
	return Request;
}

void AHttpService::SetRequestHeaders(TSharedRef<IHttpRequest>& Request) {
	Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("Accepts"), TEXT("application/json"));
}

TSharedRef<IHttpRequest> AHttpService::GetRequest(FString Subroute) {
	TSharedRef<IHttpRequest> Request = RequestWithRoute(Subroute);
	Request->SetVerb("GET");
	return Request;
}

TSharedRef<IHttpRequest> AHttpService::PostRequest(FString Subroute, FString ContentJsonString) {
	TSharedRef<IHttpRequest> Request = RequestWithRoute(Subroute);
	Request->SetVerb("POST");
	Request->SetContentAsString(ContentJsonString);
	return Request;
}

void AHttpService::Send(TSharedRef<IHttpRequest>& Request) {
	Request->ProcessRequest();
}

bool AHttpService::ResponseIsValid(FHttpResponsePtr Response, bool bWasSuccessful) {
	if (!bWasSuccessful || !Response.IsValid()) return false;
	if (EHttpResponseCodes::IsOk(Response->GetResponseCode())) return true;
	else {
		UE_LOG(LogTemp, Warning, TEXT("Http Response returned error code: %d"), Response->GetResponseCode());
		return false;
	}
}

void AHttpService::SetAuthorizationHash(FString Hash, TSharedRef<IHttpRequest>& Request) {
	Request->SetHeader(AuthorizationHeader, Hash);
}



/**************************************************************************************************************************/



template <typename StructType>
void AHttpService::GetJsonStringFromStruct(StructType FilledStruct, FString& StringOutput) {
	FJsonObjectConverter::UStructToJsonObjectString(StructType::StaticStruct(), &FilledStruct, StringOutput, 0, 0);
}

template <typename StructType>
void AHttpService::GetStructFromJsonString(FHttpResponsePtr Response, StructType& StructOutput) {
	StructType StructData;
	FString JsonString = Response->GetContentAsString();
	FJsonObjectConverter::JsonObjectStringToUStruct<StructType>(JsonString, &StructOutput, 0, 0);
}



/**************************************************************************************************************************/
//Login - Starting Game


//void AHttpService::Login(FRequest_Login LoginCredentials) {
//	FString ContentJsonString;
//	GetJsonStringFromStruct<FRequest_Login>(LoginCredentials, ContentJsonString);
//
//	TSharedRef<IHttpRequest> Request = PostRequest("user/login", ContentJsonString);
//	Request->OnProcessRequestComplete().BindUObject(this, &AHttpService::LoginResponse);
//	Send(Request);
//}

void AHttpService::Login(FRequest_Login LoginCredentials) {
	FString ContentJsonString;
	GetJsonStringFromStruct<FRequest_Login>(LoginCredentials, ContentJsonString);

	TSharedRef<IHttpRequest> Request = PostRequest("questions", ContentJsonString);
	Request->OnProcessRequestComplete().BindUObject(this, &AHttpService::LoginResponse);
	Send(Request);
}

void AHttpService::LoginResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
	if (!ResponseIsValid(Response, bWasSuccessful)) return;

	FResponse_Login LoginResponse;
	GetStructFromJsonString<FResponse_Login>(Response, LoginResponse);

	UE_LOG(LogTemp, Warning, TEXT("Id is: %d"), LoginResponse.id);
	UE_LOG(LogTemp, Warning, TEXT("Name is: %s"), *LoginResponse.name);
}

/**************************************************************************************************************************/
//Logout - Leaving game via "Q" key press

void AHttpService::Logout(FString ContentJsonString) {
	Http = &FHttpModule::Get();

	TSharedRef<IHttpRequest> Request = PostRequest("worlds", ContentJsonString);
	Request->OnProcessRequestComplete().BindUObject(this, &AHttpService::LoginResponse); //make another response if needed
	Send(Request);
}


/**************************************************************************************************************************/

int32 AHttpService::getSession()
{
	return session;
}

void AHttpService::setSession(int32 thisSession)
{
	session = thisSession;
}

// Called every frame
void AHttpService::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

