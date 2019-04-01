// Fill out your copyright notice in the Description page of Project Settings.

#include "PoliceAI.h"
#include "Raid.h"
#include "NPCs/Characters/PoliceChar.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"


APoliceAI::APoliceAI(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	BlackboardComp = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackBoardComp"));

	BrainComponent = BehaviorComp = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));

	bWantsPlayerState = true;

}

void APoliceAI::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);

	APoliceChar *Bot = Cast<APoliceChar>(InPawn);

	ControlledNpc = Bot;

	// start behavior
	if (Bot && Bot->BotBehavior)
	{
		if (Bot->BotBehavior->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*Bot->BotBehavior->BlackboardAsset);
		}

		// Define blackboard keys
		SelfActor = BlackboardComp->GetKeyID("SelfActor");
		Enemy = BlackboardComp->GetKeyID("Enemy");
		CanSeePlayer = BlackboardComp->GetKeyID("CanSeePlayer");
		LastSeenLocation = BlackboardComp->GetKeyID("LastSeenLocation");
		SearchLocation = BlackboardComp->GetKeyID("SearchLocation");

		BehaviorComp->StartTree(*(Bot->BotBehavior));

		if (BlackboardComp)
		{
			BlackboardComp->SetValue<UBlackboardKeyType_Object>(SelfActor, Bot); // add SelfObject ref in Blackboard to this NPC Bot
		}
	}
}


UObject* APoliceAI::GetSelf()
{
	//UObject* test = nullptr;
	if (BlackboardComp)
	{
		UObject *FoundObject = BlackboardComp->GetValue<UBlackboardKeyType_Object>(SelfActor); //get blackboard value as object
		return FoundObject;
	}
	else
		return NULL;

}